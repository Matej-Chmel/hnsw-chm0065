#pragma once
#include "types.hpp"

namespace chm {
	void calcCorrect(IDVec& foundIDs, IDVec& trueIDs, size_t& outCorrect);
	float recall(IDVec2D& foundIDs, IDVec2D& trueIDs, size_t maxCorrect);
}
