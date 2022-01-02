#pragma once
#include "Action.hpp"

namespace chm {
	class ActionGenerateElements : public Action {
	public:
		ActionGenerateElements();
		void run(CommonState* s) override;
		std::string text(long long elapsedMS) override;
	};
}
