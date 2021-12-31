#include <algorithm>
#include "NearestHeap.hpp"

namespace chm {
	void NearestHeap::clear() {
		this->nodes.clear();
	}

	void NearestHeap::copyFrom(NearestHeap& other) {
		this->nodes = other.nodes;
	}

	void NearestHeap::fillLayer(std::vector<size_t>& layer) {
		layer.clear();
		layer.reserve(this->nodes.size());

		for (auto& item : this->nodes)
			layer.push_back(item.nodeID);
	}

	bool NearestHeap::isCloserThanAny(NodeDistance& node) {
		auto& nearest = this->top();
		return nearest.distance > node.distance;
	}

	void NearestHeap::keepNearest(size_t K) {
		if(this->size() > K) {
			std::vector<NodeDistance> nearest;
			nearest.reserve(K);

			for(size_t i = 0; i < K; i++)
				nearest.push_back(this->pop());

			nearest.swap(this->nodes);
		}
	}

	NearestHeap::NearestHeap() {}

	NearestHeap::NearestHeap(NearestHeap& other) {
		this->copyFrom(other);
	}

	NearestHeap::NearestHeap(std::vector<NodeDistance>& ep) {
		this->nodes = ep;
		std::make_heap(this->nodes.begin(), this->nodes.end(), this->cmp);
	}

	void NearestHeap::push(float distance, size_t nodeID) {
		this->nodes.push_back({distance, nodeID});
		std::push_heap(this->nodes.begin(), this->nodes.end(), this->cmp);
	}

	NodeDistance NearestHeap::pop() {
		std::pop_heap(this->nodes.begin(), this->nodes.end(), this->cmp);
		NodeDistance item = this->nodes.back();
		this->nodes.pop_back();
		return item;
	}

	void NearestHeap::remove(size_t nodeID) {
		auto len = this->nodes.size();

		for (size_t i = 0; i < len; i++) {
			auto& item = this->nodes[i];

			if (item.nodeID == nodeID) {
				this->nodes.erase(this->nodes.begin() + i);
				std::make_heap(this->nodes.begin(), this->nodes.end(), this->cmp);
				break;
			}
		}
	}

	size_t NearestHeap::size() {
		return this->nodes.size();
	}

	NodeDistance& NearestHeap::top() {
		return this->nodes.front();
	}
}
