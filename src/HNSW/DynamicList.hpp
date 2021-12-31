#pragma once
#include "FurthestHeap.hpp"
#include "NearestHeap.hpp"

namespace chm {
	class DynamicList {
		void clear();

	public:
		FurthestHeap furthestHeap;
		NearestHeap nearestHeap;

		void add(float distance, size_t nodeID);
		DynamicList(float distance, size_t entryID);
		NodeDistance furthest();
		void keepOnlyNearest();
		void removeFurthest();
		size_t size();
	};
}
