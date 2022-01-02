#include <unordered_set>
#include "AppError.hpp"
#include "forEachLayer.hpp"
#include "literals.hpp"
#include "TestSingleLayerDuplicates.hpp"

namespace chm {
	void TestSingleLayerDuplicates::run(CommonState* s) {
		forEachLayer(*s->hnsw, [](chm::IDVec& layer, size_t layerID, size_t nodeID) {
			std::unordered_set<size_t> neighbors;
			neighbors.reserve(layer.size());

			for(auto& neighborID : layer)
				if(neighbors.find(neighborID) == neighbors.end())
					neighbors.insert(neighborID);
				else
					throw chm::AppError(
						"Element "_f << neighborID << " is duplicated in layer " << layerID <<
						" for element " << nodeID << '.'
					);
		});
	}

	std::string TestSingleLayerDuplicates::text(long long elapsedMS) {
		return "Single layer duplicates";
	}
}
