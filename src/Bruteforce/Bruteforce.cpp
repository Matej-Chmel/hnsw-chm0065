#include <algorithm>
#include "Bruteforce.hpp"
#include "Comparator.hpp"

namespace chm {
	float Bruteforce::getDistance(size_t nodeID, float* query) {
		float* nodeCoords = this->coords + nodeID * this->dim;
		float result = 0.f;

		for(size_t i = 0; i < this->dim; i++) {
			float diff = nodeCoords[i] - query[i];
			result += diff * diff;
		}

		return result;
	}

	Bruteforce::Bruteforce(float* coords, size_t dim, size_t count) : coords(coords), count(count), dim(dim) {}

	void Bruteforce::search(float* query, std::vector<BruteforceItem>& results, size_t K) {
		results.reserve(this->count);

		for(size_t i = 0; i < this->count; i++)
			results.emplace_back(this->getDistance(i, query), i);

		Comparator cmp;
		std::sort(results.begin(), results.end(), cmp);

		if(results.size() > K)
			results.erase(results.begin() + K, results.end());
	}

	void Bruteforce::search(
		float* queryCoords, size_t queryCount, std::vector<std::vector<BruteforceItem>>& results, size_t K
	) {
		results.resize(queryCount);

		for(size_t i = 0; i < queryCount; i++)
			this->search(queryCoords + i * this->dim, results[i], K);
	}
}
