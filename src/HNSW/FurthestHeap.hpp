#pragma once
#include "FurthestComparator.hpp"
#include "NodeDistance.hpp"

namespace chm {
	class FurthestHeap {
		FurthestComparator cmp;

	public:
		NodeDistanceVec nodes;

		void clear();
		FurthestHeap();
		FurthestHeap(NodeDistanceVec& ep);
		void push(float distance, size_t nodeID);
		NodeDistance pop();
		NodeDistance top();
	};
}
