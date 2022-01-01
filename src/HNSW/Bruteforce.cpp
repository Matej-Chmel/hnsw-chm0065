#include <algorithm>
#include "Bruteforce.hpp"

namespace chm {
	float Bruteforce::getDistance(size_t nodeID, float* query) {
		float* nodeCoords = this->coords + nodeID * this->dim;
		float result = 0.f;

		for (size_t i = 0; i < this->dim; i++) {
			float diff = nodeCoords[i] - query[i];
			result += diff * diff;
		}

		return result;
	}

	Bruteforce::Bruteforce(float* coords, size_t dim, size_t count) : coords(coords), count(count), dim(dim) {
		this->distances.resize(count);
	}

	void Bruteforce::search(float* query, size_t K, IDVec& outIDs, FloatVec& outDistances) {
		outIDs.resize(this->count);

		for(size_t i = 0; i < this->count; i++) {
			this->distances[i] = this->getDistance(i, query);
			outIDs[i] = i;
		}

		Comparator cmp{ this };
		std::sort(outIDs.begin(), outIDs.end(), cmp);

		if (this->count > K)
			outIDs.erase(outIDs.begin() + K, outIDs.end());

		outDistances.reserve(K);

		for (auto& id : outIDs)
			outDistances.push_back(this->distances[id]);
	}

	void Bruteforce::search(float* queryCoords, size_t queryCount, size_t K, IDVec2D& outIDs, FloatVec2D& outDistances) {
		outIDs.resize(queryCount);
		outDistances.resize(queryCount);

		for (size_t i = 0; i < queryCount; i++)
			this->search(queryCoords + i * this->dim, K, outIDs[i], outDistances[i]);
	}

	bool Bruteforce::Comparator::operator()(const size_t& aID, const size_t& bID) {
		return b->distances[aID] < b->distances[bID];
	}
}
