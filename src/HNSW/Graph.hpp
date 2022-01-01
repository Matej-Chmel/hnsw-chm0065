#pragma once
#include "DynamicList.hpp"
#include <random>
#include <unordered_map>

namespace chm {
	class Graph : public Unique {
	public:
		size_t efConstruction;
		size_t M;
		float mL;
		size_t Mmax;
		size_t Mmax0;

		bool extendCandidates;
		bool keepPrunedConnections;
		bool useHeuristic;

		size_t entryID;
		size_t entryLevel;

		std::unordered_map<size_t, float> distances;
		std::vector<IDVec2D> layers;

		float* coords;
		size_t dim;
		float* queryCoords;

		std::default_random_engine gen;
		std::uniform_real_distribution<float> dist;

		float getDistance(size_t nodeID, size_t queryID, bool inserting);
		size_t getNewLevel();

		void insert(size_t queryID);
		void searchLayer(size_t queryID, DynamicList& W, size_t ef, size_t lc, bool inserting);
		void selectNeighbors(size_t queryID, DynamicList& C, size_t M, size_t lc, NearestHeap& results);
		void selectNeighborsHeuristic(size_t queryID, DynamicList& C, size_t M, size_t lc, NearestHeap& results);
		void selectNeighborsSimple(size_t queryID, DynamicList& C, size_t M, NearestHeap& results);
		void knnSearch(size_t queryID, size_t K, size_t ef, IDVec& outIDs, FloatVec& outDistances);

		void connect(size_t queryID, NearestHeap& neighbors, size_t lc);
		void initLayers(size_t queryID, size_t level);

		void calcML();
		Graph(size_t seed, bool rndSeed);

		void build(float* coords, size_t dim, size_t count);
		void search(float* queryCoords, size_t queryCount, size_t K, size_t ef, IDVec2D& outIDs, FloatVec2D& outDistances);
	};
}
