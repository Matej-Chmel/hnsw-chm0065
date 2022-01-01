#pragma once
#include <vector>

namespace chm {
	void calcCorrect(std::vector<size_t>& foundIDs, std::vector<size_t>& trueIDs, size_t& outCorrect);
	float recall(std::vector<std::vector<size_t>>& foundIDs, std::vector<std::vector<size_t>>& trueIDs, size_t maxCorrect);
}
