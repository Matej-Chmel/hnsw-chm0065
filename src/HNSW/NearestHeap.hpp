#pragma once
#include "NearestComparator.hpp"
#include "NodeDistance.hpp"
#include "types.hpp"
#include "Unique.hpp"

namespace chm {
	class NearestHeap : public Unique {
		NearestComparator cmp;

	public:
		NodeDistanceVec nodes;

		void clear();
		void fillLayer(IDVec& layer);
		bool isCloserThanAny(NodeDistance& node);
		void keepNearest(size_t K);
		NearestHeap();
		NearestHeap(NearestHeap& other);
		void push(float distance, size_t nodeID);
		NodeDistance pop();
		void remove(size_t nodeID);
		void reserve(size_t s);
		size_t size();
		void swap(NearestHeap& other);
		NodeDistance& top();
	};
}
