#pragma once
#include "Action.hpp"

namespace chm {
	class ActionBuildHNSW : public Action {
	public:
		ActionBuildHNSW();
		void run(CommonState* s) override;
		std::string text(long long elapsedMS) override;
	};
}
