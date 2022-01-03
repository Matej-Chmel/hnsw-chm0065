#include "AppError.hpp"
#include "forEachLayer.hpp"
#include "literals.hpp"
#include "TestLayerLength.hpp"

namespace chm {
	void TestLayerLength::run() {
		auto Mmax = this->s->hnsw->cfg.Mmax;
		auto Mmax0 = this->s->hnsw->cfg.Mmax0;

		forEachLayer(*this->s->hnsw, [&](chm::IDVec& layer, size_t layerID, size_t nodeID) {
			auto actualLen = layer.size();
			auto maxLen = layerID == 0 ? Mmax0 : Mmax;

			if(actualLen > maxLen)
				throw AppError(
					"Layer "_f << layerID << " of node " << nodeID << " is larger than maximum length.\nActual length: "
					<< actualLen << "\nMaximum length: " << maxLen
				);
		});
	}

	std::string TestLayerLength::text(long long elapsedMS) {
		return "Layer length";
	}
}
