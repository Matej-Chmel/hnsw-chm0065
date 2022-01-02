#pragma once
#include "Action.hpp"

namespace chm {
	class ActionBuildBruteforce : public Action {
	public:
		ActionBuildBruteforce();
		void run(CommonState* s) override;
		std::string text(long long elapsedMS) override;
	};
}
