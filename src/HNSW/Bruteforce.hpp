#pragma once
#include <vector>
#include "types.hpp"
#include "Unique.hpp"

namespace chm {
	class Bruteforce : public Unique {
		float* coords;
		size_t count;
		size_t dim;
		FloatVec distances;

		float getDistance(size_t nodeID, float* query);

		struct Comparator {
			Bruteforce* b;

			bool operator()(const size_t& aID, const size_t& bID);
		};

	public:
		Bruteforce(float* coords, size_t dim, size_t count);
		void search(float* query, size_t K, IDVec& outIDs, FloatVec& outDistances);
		void search(float* queryCoords, size_t queryCount, size_t K, IDVec2D& outIDs, FloatVec2D& outDistances);
	};
}
