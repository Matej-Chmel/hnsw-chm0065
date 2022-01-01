#include <algorithm>
#include "FurthestHeap.hpp"

namespace chm {
	void FurthestHeap::clear() {
		this->nodes.clear();
	}

	FurthestHeap::FurthestHeap() {}

	FurthestHeap::FurthestHeap(NodeDistanceVec& ep) {
		this->nodes = ep;
		std::make_heap(this->nodes.begin(), this->nodes.end(), this->cmp);
	}

	void FurthestHeap::push(float distance, size_t nodeID) {
		this->nodes.push_back({distance, nodeID});
		std::push_heap(this->nodes.begin(), this->nodes.end(), this->cmp);
	}

	NodeDistance FurthestHeap::pop() {
		std::pop_heap(this->nodes.begin(), this->nodes.end(), this->cmp);
		NodeDistance item = this->nodes.back();
		this->nodes.pop_back();
		return item;
	}

	NodeDistance FurthestHeap::top() {
		return this->nodes.front();
	}
}
