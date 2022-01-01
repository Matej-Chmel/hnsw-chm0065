#include "DynamicList.hpp"

namespace chm {
	void DynamicList::clear() {
		this->furthestHeap.clear();
		this->nearestHeap.clear();
	}

	void DynamicList::add(float distance, size_t nodeID) {
		this->furthestHeap.push(distance, nodeID);
		this->nearestHeap.push(distance, nodeID);
	}

	DynamicList::DynamicList(float distance, size_t entryID) {
		this->add(distance, entryID);
	}

	void DynamicList::fillResults(size_t K, std::vector<size_t>& outIDs, std::vector<float>& outDistances) {
		size_t len = std::min(K, this->size());
		outIDs.reserve(len);
		outDistances.reserve(len);

		for (size_t i = 0; i < len; i++) {
			auto& item = this->nearestHeap.top();

			outIDs.push_back(item.nodeID);
			outDistances.push_back(item.distance);
			this->nearestHeap.pop();
		}
	}

	NodeDistance DynamicList::furthest() {
		return this->furthestHeap.top();
	}

	void DynamicList::keepOnlyNearest() {
		NodeDistance nearest = this->nearestHeap.top();

		this->clear();
		this->add(nearest.distance, nearest.nodeID);
	}

	void DynamicList::removeFurthest() {
		auto item = this->furthestHeap.pop();
		this->nearestHeap.remove(item.nodeID);
	}

	size_t DynamicList::size() {
		return this->nearestHeap.size();
	}
}
