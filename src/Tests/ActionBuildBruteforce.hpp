#pragma once
#include "Action.hpp"

namespace chm {
	class ActionBuildBruteforce : public Action {
	public:
		ActionBuildBruteforce();
		void run() override;
		std::string text(long long elapsedMS) override;
	};
}
