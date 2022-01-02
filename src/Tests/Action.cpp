#include "Action.hpp"

namespace chm {
	Action::Action(bool isTest) : isTest(isTest), s(nullptr) {}

	void Action::setCommonState(CommonState* s) {
		this->s = s;
	}
}
