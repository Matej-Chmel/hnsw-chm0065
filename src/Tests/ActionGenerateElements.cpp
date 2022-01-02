#include "ActionGenerateElements.hpp"
#include "literals.hpp"

namespace chm {
	ActionGenerateElements::ActionGenerateElements() : Action(false) {}

	void ActionGenerateElements::run(CommonState* s) {
		s->gen = new ElementGenerator(ELEMENT_MIN, ELEMENT_MAX, ELEMENT_SEED);
		s->nodeCoords = new FloatVec();
		s->gen->fill(*s->nodeCoords, DIM, NODE_COUNT);
	}

	std::string ActionGenerateElements::text(long long elapsedMS) {
		return ("Elements generated in "_f << elapsedMS << " ms.").str();
	}
}
