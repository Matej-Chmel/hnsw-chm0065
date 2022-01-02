#pragma once
#include <functional>
#include "Graph.hpp"

namespace chm {
	typedef std::function<void(chm::IDVec& layer, size_t layerID, size_t nodeID)> LayerFunc;

	void forEachLayer(chm::Graph& hnsw, LayerFunc f);
}
