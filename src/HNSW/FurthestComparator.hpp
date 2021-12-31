#pragma once
#include "NodeDistance.hpp"

namespace chm {
	struct FurthestComparator {
		bool operator()(const NodeDistance& a, const NodeDistance& b) {
			return a.distance < b.distance;
		}
	};
}
