#include "ActionGenerateElements.hpp"
#include "literals.hpp"

namespace chm {
	ActionGenerateElements::ActionGenerateElements() : Action(false) {}

	void ActionGenerateElements::run() {
		this->s->gen = new ElementGenerator(ELEMENT_MIN, ELEMENT_MAX, ELEMENT_SEED);
		this->s->nodeCoords = new FloatVec();
		this->s->gen->fill(*this->s->nodeCoords, DIM, NODE_COUNT);
	}

	std::string ActionGenerateElements::text(long long elapsedMS) {
		return ("Elements generated in "_f << elapsedMS << " ms.").str();
	}
}
