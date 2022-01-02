#include "ActionBuildHNSW.hpp"
#include "literals.hpp"

namespace chm {
	ActionBuildHNSW::ActionBuildHNSW() : Action(false) {}

	void ActionBuildHNSW::run(CommonState* s) {
		s->hnsw = new Graph(LEVEL_SEED, false);
		s->hnsw->build(s->nodeCoords->data(), DIM, NODE_COUNT);
	}

	std::string ActionBuildHNSW::text(long long elapsedMS) {
		return ("HNSW graph built in "_f << elapsedMS << " ms.").str();
	}
}
