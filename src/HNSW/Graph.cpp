#include <algorithm>
#include <cmath>
#include <unordered_set>
#include "AppError.hpp"
#include "literals.hpp"
#include "Graph.hpp"

namespace chm {
	float Graph::getDistance(size_t nodeID, size_t queryID, State s) {
		if(s != State::SHRINKING) {
			auto iter = this->distances.find(nodeID);

			if(iter != this->distances.end())
				return iter->second;
		}

		float* nodeCoords = this->coords + nodeID * this->cfg.dim;
		float* qCoords = (s == State::SEARCHING ? this->queryCoords : this->coords) + queryID * this->cfg.dim;

		float distance = 0.f;

		for(size_t i = 0; i < this->cfg.dim; i++) {
			float diff = nodeCoords[i] - qCoords[i];
			distance += diff * diff;
		}

		if(s != State::SHRINKING)
			this->distances[nodeID] = distance;

		return distance;
	}

	size_t Graph::getNewLevel() {
		return size_t(
			std::floorf(
				-std::logf(
					this->dist(this->gen) * this->cfg.mL
				)
			)
		);
	}

	void Graph::insert(size_t queryID) {
		DynamicList W(this->getDistance(this->entryID, queryID), this->entryID);
		auto L = this->entryLevel;
		auto l = this->getNewLevel();

		this->initLayers(queryID, l);

		for(size_t lc = L; lc > l; lc--) {
			this->searchLayer(queryID, W, 1, lc);
			W.keepOnlyNearest();
		}

		for(size_t lc = std::min(L, l);; lc--) {
			size_t layerMmax = (lc == 0) ? this->cfg.Mmax0 : this->cfg.Mmax;

			this->searchLayer(queryID, W, this->cfg.efConstruction, lc);

			NearestHeap neighbors(W.nearestHeap);
			this->selectNeighbors(queryID, neighbors, this->cfg.M, lc);
			this->connect(queryID, neighbors, lc);

			for(auto& e : neighbors.nodes) {
				auto& eConn = this->layers[e.nodeID][lc];

				if(eConn.size() > layerMmax) {
					NearestHeap eNewConn;
					this->fillHeap(e.nodeID, eConn, eNewConn);

					this->selectNeighbors(e.nodeID, eNewConn, layerMmax, lc, State::SHRINKING);
					eNewConn.fillLayer(eConn);
				}
			}

			if(lc == 0)
				break;
		}

		if(l > L) {
			this->entryID = queryID;
			this->entryLevel = l;
		}
	}

	void Graph::searchLayer(size_t queryID, DynamicList& W, size_t ef, size_t lc, State s) {
		std::unordered_set<size_t> v;

		for(auto& item : W.nearestHeap.nodes)
			v.insert(item.nodeID);

		NearestHeap C(W.nearestHeap);

		while(C.size() > 0) {
			auto c = C.pop();
			auto f = W.furthest();

			if(c.distance > f.distance)
				break;

			auto& neighbors = this->layers[c.nodeID][lc];

			for(auto& eID : neighbors) {
				if(v.find(eID) == v.end()) {
					v.insert(eID);
					f = W.furthest();
					float eDistance = this->getDistance(eID, queryID, s);

					if(eDistance < f.distance || W.size() < ef) {
						C.push(eDistance, eID);
						W.add(eDistance, eID);

						if(W.size() > ef)
							W.removeFurthest();
					}
				}
			}
		}
	}

	void Graph::selectNeighbors(size_t queryID, NearestHeap& outC, size_t M, size_t lc, State s) {
		if(this->cfg.useHeuristic)
			this->selectNeighborsHeuristic(queryID, outC, M, lc, s);
		else
			this->selectNeighborsSimple(outC, M);
	}

	void Graph::selectNeighborsHeuristic(size_t queryID, NearestHeap& outC, size_t M, size_t lc, State s) {
		NearestHeap R;
		auto& W = outC;

		if(this->cfg.extendCandidates) {
			std::unordered_set<size_t> visited;

			for(auto& e : outC.nodes) {
				auto& neighbors = this->layers[e.nodeID][lc];

				for(auto& eAdjID : neighbors)
					if(visited.find(eAdjID) == visited.end())
						visited.insert(eAdjID);
			}

			for(const auto& ID : visited)
				W.push(this->getDistance(ID, queryID, s), ID);
		}

		NearestHeap Wd;

		while(W.size() > 0 && R.size() < M) {
			auto e = W.pop();

			if(R.isCloserThanAny(e))
				R.push(e.distance, e.nodeID);
			else if(this->cfg.keepPrunedConnections)
				Wd.push(e.distance, e.nodeID);
		}

		if(this->cfg.keepPrunedConnections) {
			while(Wd.size() > 0 && R.size() < M) {
				auto discardedNearest = Wd.pop();
				R.push(discardedNearest.distance, discardedNearest.nodeID);
			}
		}

		outC.swap(R);
	}

	void Graph::selectNeighborsSimple(NearestHeap& outC, size_t M) {
		outC.keepNearest(M);
	}

	void Graph::knnSearch(size_t queryID, size_t K, size_t ef, IDVec& outIDs, FloatVec& outDistances) {
		DynamicList W(this->getDistance(this->entryID, queryID, State::SEARCHING), this->entryID);
		auto L = this->entryLevel;

		for(size_t lc = L; lc > 0; lc--) {
			this->searchLayer(queryID, W, 1, lc, State::SEARCHING);
			W.keepOnlyNearest();
		}

		this->searchLayer(queryID, W, ef, 0, State::SEARCHING);
		W.fillResults(K, outIDs, outDistances);
	}

	void Graph::connect(size_t queryID, NearestHeap& neighbors, size_t lc) {
		auto& qLayer = this->layers[queryID][lc];

		for(auto& item : neighbors.nodes) {
			if(queryID == item.nodeID)
				throw AppError("Tried to connect element "_f << queryID << " with itself at layer " << lc << '.');

			qLayer.push_back(item.nodeID);

			auto& itemLayer = this->layers[item.nodeID][lc];
			itemLayer.push_back(queryID);
		}
	}

	void Graph::fillHeap(size_t queryID, IDVec& eConn, NearestHeap& eNewConn) {
		eNewConn.reserve(eConn.size());

		for(auto& ID : eConn)
			eNewConn.push(this->getDistance(ID, queryID, State::SHRINKING), ID);
	}

	void Graph::initLayers(size_t queryID, size_t level) {
		size_t nLayers = level + 1;
		auto& qLayers = this->layers[queryID];
		qLayers.resize(nLayers);
	}

	Graph::Graph(const Config& cfg, size_t seed, bool rndSeed)
		: cfg(cfg), entryID(0), entryLevel(0), coords(nullptr), queryCoords(nullptr),
		gen(rndSeed ? std::random_device{}() : (unsigned int)(seed)),
		dist(0.f, 1.f) {}

	void Graph::build(float* coords, size_t count) {
		this->coords = coords;
		this->entryLevel = this->getNewLevel();
		this->layers.resize(count);
		this->initLayers(this->entryID, this->entryLevel);

		for(size_t i = 1; i < count; i++) {
			this->distances.clear();
			this->insert(i);
		}
	}

	void Graph::search(float* queryCoords, size_t queryCount, size_t K, size_t ef, IDVec2D& outIDs, FloatVec2D& outDistances) {
		outIDs.resize(queryCount);
		outDistances.resize(queryCount);
		this->queryCoords = queryCoords;

		for(size_t i = 0; i < queryCount; i++) {
			this->distances.clear();
			this->knnSearch(i, K, ef, outIDs[i], outDistances[i]);
		}
	}

	size_t Graph::getNodeCount() {
		return this->layers.size();
	}

	void Graph::printLayers(std::ostream& o) {
		auto count = this->getNodeCount();
		auto lastID = count - 1;

		for(size_t nodeID = 0; nodeID < count; nodeID++) {
			o << "Node " << nodeID << '\n';

			auto& nodeLayers = this->layers[nodeID];
			auto nodeLayersLen = nodeLayers.size();

			for(size_t layerID = 0; layerID < nodeLayersLen; layerID++) {
				o << "Layer " << layerID << ": ";

				auto& layer = nodeLayers[layerID];
				auto lastIdx = layer.size() - 1;

				IDVec sortedLayer(layer);
				std::sort(sortedLayer.begin(), sortedLayer.end());

				for(size_t i = 0; i < lastIdx; i++)
					o << sortedLayer[i] << ' ';

				o << sortedLayer[lastIdx] << '\n';
			}

			if(nodeID != lastID)
				o << '\n';
		}
	}
}
