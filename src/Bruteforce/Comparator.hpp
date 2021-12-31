#pragma once
#include "BruteforceItem.hpp"

namespace chm {
	struct Comparator {
		bool operator()(const BruteforceItem& a, const BruteforceItem& b) {
			return a.distance < b.distance;
		}
	};
}
