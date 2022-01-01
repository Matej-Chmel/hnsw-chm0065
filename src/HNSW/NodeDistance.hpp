#pragma once
#include <vector>

namespace chm {
	struct NodeDistance {
		float distance;
		size_t nodeID;
	};

	typedef std::vector<NodeDistance> NodeDistanceVec;
}
