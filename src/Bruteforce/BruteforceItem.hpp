#pragma once

namespace chm {
	struct BruteforceItem {
		float distance;
		size_t nodeID;

		BruteforceItem(float distance, size_t nodeID);
	};
}
