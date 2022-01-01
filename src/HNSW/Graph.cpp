#include <algorithm>
#include <cmath>
#include <unordered_set>
#include "Graph.hpp"

namespace chm {
	float Graph::getDistance(size_t nodeID, size_t queryID, bool inserting) {
		auto iter = this->distances.find(nodeID);

		if(iter != this->distances.end())
			return iter->second;


		float* nodeCoords = this->coords + nodeID * this->dim;
		float* qCoords = (inserting ? this->coords : this->queryCoords) + queryID * this->dim;

		float distance = 0.f;

		for(size_t i = 0; i < this->dim; i++) {
			float diff = nodeCoords[i] - qCoords[i];
			distance += diff * diff;
		}

		this->distances[nodeID] = distance;
		return distance;
	}

	size_t Graph::getNewLevel() {
		return size_t(
			std::floorf(
				-std::logf(
					this->dist(this->gen) * this->mL
				)
			)
		);
	}

	void Graph::insert(size_t queryID) {
		DynamicList W(this->getDistance(this->entryID, queryID, true), this->entryID);
		auto L = this->entryLevel;
		auto l = this->getNewLevel();

		this->initLayers(queryID, l);

		for(size_t lc = L; lc > l; lc--) {
			this->searchLayer(queryID, W, 1, lc, true);
			W.keepOnlyNearest();
		}

		for(size_t lc = std::min(L, l);; lc--) {
			size_t layerMmax = (lc == 0) ? this->Mmax0 : this->Mmax;

			this->searchLayer(queryID, W, this->efConstruction, lc, true);

			NearestHeap neighbors;
			this->selectNeighbors(queryID, W, this->M, lc, neighbors);
			this->connect(queryID, neighbors, lc);

			for(auto& e : neighbors.nodes) {
				auto& eConn = this->layers[e.nodeID][lc];

				if(eConn.size() > layerMmax) {
					NearestHeap eNewConn;
					this->selectNeighbors(queryID, W, layerMmax, lc, eNewConn);
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

	void Graph::searchLayer(size_t queryID, DynamicList& W, size_t ef, size_t lc, bool inserting) {
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
					float eDistance = this->getDistance(eID, queryID, inserting);

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

	void Graph::selectNeighbors(size_t queryID, DynamicList& C, size_t M, size_t lc, NearestHeap& results) {
		if(this->useHeuristic)
			this->selectNeighborsHeuristic(queryID, C, M, lc, results);
		else
			this->selectNeighborsSimple(queryID, C, M, results);
	}

	void Graph::selectNeighborsHeuristic(size_t queryID, DynamicList& C, size_t M, size_t lc, NearestHeap& results) {
		NearestHeap W(C.nearestHeap);

		if(this->extendCandidates) {
			std::unordered_set<size_t> visited;

			for(auto& e : C.nearestHeap.nodes) {
				auto& neighbors = this->layers[e.nodeID][lc];

				for(auto& eAdjID : neighbors) {
					if(visited.find(eAdjID) == visited.end()) {
						visited.insert(eAdjID);
						W.push(this->getDistance(eAdjID, queryID, true), eAdjID);
					}
				}
			}
		}

		NearestHeap Wd;

		while(W.size() > 0 && results.size() < M) {
			auto e = W.pop();

			if(results.isCloserThanAny(e))
				results.push(e.distance, e.nodeID);
			else if(this->keepPrunedConnections)
				Wd.push(e.distance, e.nodeID);
		}

		if(this->keepPrunedConnections) {
			while(Wd.size() > 0 && results.size() < M) {
				auto discardedNearest = Wd.pop();
				results.push(discardedNearest.distance, discardedNearest.nodeID);
			}
		}
	}

	void Graph::selectNeighborsSimple(size_t queryID, DynamicList& C, size_t M, NearestHeap& results) {
		results.copyFrom(C.nearestHeap);
		results.keepNearest(M);
	}

	void Graph::knnSearch(size_t queryID, size_t K, size_t ef, IDVec& outIDs, FloatVec& outDistances) {
		DynamicList W(this->getDistance(this->entryID, queryID, false), this->entryID);
		auto L = this->entryLevel;

		for (size_t lc = L; lc > 0; lc--) {
			this->searchLayer(queryID, W, 1, lc, false);
			W.keepOnlyNearest();
		}

		this->searchLayer(queryID, W, ef, 0, false);
		W.fillResults(K, outIDs, outDistances);
	}

	void Graph::connect(size_t queryID, NearestHeap& neighbors, size_t lc) {
		auto& qLayer = this->layers[queryID][lc];

		for(auto& item : neighbors.nodes) {
			qLayer.push_back(item.nodeID);

			auto& itemLayer = this->layers[item.nodeID][lc];
			itemLayer.push_back(queryID);
		}
	}

	void Graph::initLayers(size_t queryID, size_t level) {
		size_t nLayers = level + 1;
		auto& qLayers = this->layers[queryID];
		qLayers.resize(nLayers);
	}

	void Graph::calcML() {
		this->mL = 1 / std::logf(float(this->M));
	}

	Graph::Graph(size_t seed, bool rndSeed) {
		this->efConstruction = 200;
		this->M = 16;
		this->Mmax = this->M;
		this->Mmax0 = this->M * 2;
		this->calcML();

		this->extendCandidates = false;
		this->keepPrunedConnections = false;
		this->useHeuristic = false;

		this->gen = std::default_random_engine(rndSeed ? std::random_device{}() : (unsigned int)(seed));
		this->dist = std::uniform_real_distribution<float>(0.f, 1.f);
	}

	void Graph::build(float* coords, size_t dim, size_t count) {
		this->coords = coords;
		this->dim = dim;

		this->entryID = 0;
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
}
