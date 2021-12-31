#pragma once
#include "NearestComparator.hpp"
#include "NodeDistance.hpp"
#include <vector>

namespace chm {
	class NearestHeap {
		NearestComparator cmp;

	public:
		std::vector<NodeDistance> nodes;

		void clear();
		void copyFrom(NearestHeap& other);
		void fillLayer(std::vector<size_t>& layer);
		bool isCloserThanAny(NodeDistance& node);
		void keepNearest(size_t K);
		NearestHeap();
		NearestHeap(NearestHeap& other);
		NearestHeap(std::vector<NodeDistance>& ep);
		void push(float distance, size_t nodeID);
		NodeDistance pop();
		void remove(size_t nodeID);
		size_t size();
		NodeDistance& top();
	};
}
