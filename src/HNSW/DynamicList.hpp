#pragma once
#include "FurthestHeap.hpp"
#include "NearestHeap.hpp"

namespace chm {
	class DynamicList : public Unique {
		void clear();

	public:
		FurthestHeap furthestHeap;
		NearestHeap nearestHeap;

		void add(float distance, size_t nodeID);
		DynamicList(float distance, size_t entryID);
		void fillResults(size_t K, std::vector<size_t>& outIDs, std::vector<float>& outDistances);
		NodeDistance furthest();
		void keepOnlyNearest();
		void removeFurthest();
		size_t size();
	};
}
