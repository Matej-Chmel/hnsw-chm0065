#include <unordered_set>
#include "recall.hpp"

namespace chm {
	void calcCorrect(IDVec& foundIDs, IDVec& trueIDs, size_t& outCorrect) {
		std::unordered_set<size_t> foundSet(foundIDs.begin(), foundIDs.end());

		for(auto& ID : trueIDs)
			if(foundSet.find(ID) != foundSet.end())
				outCorrect++;
	}

	float recall(IDVec2D& foundIDs, IDVec2D& trueIDs, size_t maxCorrect) {
		size_t correct = 0;
		auto len = trueIDs.size();

		for(size_t i = 0; i < len; i++)
			calcCorrect(foundIDs[i], trueIDs[i], correct);

		return float(correct) / float(maxCorrect);
	}
}
