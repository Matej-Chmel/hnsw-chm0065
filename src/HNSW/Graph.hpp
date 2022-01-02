#pragma once
#include "Config.hpp"
#include "DynamicList.hpp"
#include "State.hpp"
#include <ostream>
#include <random>
#include <unordered_map>

namespace chm {
	class Graph : public Unique {
	public:
		Config cfg;

		size_t entryID;
		size_t entryLevel;

		std::unordered_map<size_t, float> distances;
		std::vector<IDVec2D> layers;

		float* coords;
		float* queryCoords;

		std::default_random_engine gen;
		std::uniform_real_distribution<float> dist;

		std::ostream* debugStream;
		size_t nodeCount;

		float getDistance(size_t nodeID, size_t queryID, State s = State::INSERTING);
		size_t getNewLevel();

		void insert(size_t queryID);
		void searchLayer(size_t queryID, DynamicList& W, size_t ef, size_t lc, State s = State::INSERTING);
		void selectNeighbors(size_t queryID, NearestHeap& outC, size_t M, size_t lc, State s = State::INSERTING);
		void selectNeighborsHeuristic(size_t queryID, NearestHeap& outC, size_t M, size_t lc, State s);
		void selectNeighborsSimple(NearestHeap& outC, size_t M);
		void knnSearch(size_t queryID, size_t K, size_t ef, IDVec& outIDs, FloatVec& outDistances);

		void connect(size_t queryID, NearestHeap& neighbors, size_t lc);
		void fillHeap(size_t queryID, IDVec& eConn, NearestHeap& eNewConn);
		void initLayers(size_t queryID, size_t level);

		Graph(const Config& cfg, size_t seed, bool rndSeed);

		void build(float* coords, size_t count);
		void search(float* queryCoords, size_t queryCount, size_t K, size_t ef, IDVec2D& outIDs, FloatVec2D& outDistances);

		size_t getNodeCount();
		void printLayers(std::ostream& s);
		void setDebugStream(std::ostream& s);
	};
}
