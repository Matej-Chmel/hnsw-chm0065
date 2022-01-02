#include "forEachLayer.hpp"

namespace chm {
	void forEachLayer(chm::Graph& hnsw, LayerFunc f) {
		auto count = hnsw.getNodeCount();

		for(size_t nodeID = 0; nodeID < count; nodeID++) {
			auto& nodeLayers = hnsw.layers[nodeID];
			auto nodeLayersLen = nodeLayers.size();

			for(size_t layerID = 0; layerID < nodeLayersLen; layerID++) {
				auto& layer = nodeLayers[layerID];
				f(layer, layerID, nodeID);
			}
		}
	}
}
