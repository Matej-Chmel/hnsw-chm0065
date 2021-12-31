#pragma once
#include "FurthestComparator.hpp"
#include "NodeDistance.hpp"
#include <vector>

namespace chm {
	class FurthestHeap {
		FurthestComparator cmp;

	public:
		std::vector<NodeDistance> nodes;

		void clear();
		FurthestHeap();
		FurthestHeap(std::vector<NodeDistance>& ep);
		void push(float distance, size_t nodeID);
		NodeDistance pop();
		NodeDistance top();
	};
}
