#include "AppError.hpp"
#include "forEachLayer.hpp"
#include "literals.hpp"
#include "TestConnectionWithItself.hpp"

namespace chm {
	void TestConnectionWithItself::run() {
		forEachLayer(*this->s->hnsw, [](chm::IDVec& layer, size_t layerID, size_t nodeID) {
			for(auto& neighbor : layer)
				if(neighbor == nodeID)
					throw chm::AppError(
						"Element "_f << nodeID << " is connected with itself at layer " << layerID << '.'
					);
		});
	}

	std::string TestConnectionWithItself::text(long long elapsedMS) {
		return "Connection with itself";
	}
}
