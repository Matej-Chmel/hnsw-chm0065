#pragma once
#include <vector>
#include "Unique.hpp"

namespace chm {
	class Bruteforce : public Unique {
		float* coords;
		size_t count;
		size_t dim;
		std::vector<float> distances;

		float getDistance(size_t nodeID, float* query);

		struct Comparator {
			Bruteforce* b;

			bool operator()(const size_t& aID, const size_t& bID);
		};

	public:
		Bruteforce(float* coords, size_t dim, size_t count);
		void search(float* query, size_t K, std::vector<size_t>& outIDs, std::vector<float>& outDistances);
		void search(
			float* queryCoords, size_t queryCount, size_t K,
			std::vector<std::vector<size_t>>& outIDs, std::vector<std::vector<float>>& outDistances
		);
	};
}
