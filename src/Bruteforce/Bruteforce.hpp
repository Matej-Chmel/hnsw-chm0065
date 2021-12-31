#pragma once
#include <vector>
#include "BruteforceItem.hpp"

namespace chm {
	class Bruteforce {
		float* coords;
		size_t count;
		size_t dim;

		float getDistance(size_t nodeID, float* query);

	public:
		Bruteforce(float* coords, size_t dim, size_t count);
		void search(float* query, std::vector<BruteforceItem>& results, size_t K);
		void search(float* queryCoords, size_t queryCount, std::vector< std::vector<BruteforceItem>>& results, size_t K);
	};
}
