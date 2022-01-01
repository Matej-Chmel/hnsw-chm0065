#pragma once
#include "NearestComparator.hpp"
#include "NodeDistance.hpp"
#include "types.hpp"

namespace chm {
	class NearestHeap {
		NearestComparator cmp;

	public:
		NodeDistanceVec nodes;

		void clear();
		void copyFrom(NearestHeap& other);
		void fillLayer(IDVec& layer);
		bool isCloserThanAny(NodeDistance& node);
		void keepNearest(size_t K);
		NearestHeap();
		NearestHeap(NearestHeap& other);
		NearestHeap(NodeDistanceVec& ep);
		void push(float distance, size_t nodeID);
		NodeDistance pop();
		void remove(size_t nodeID);
		size_t size();
		NodeDistance& top();
	};
}
