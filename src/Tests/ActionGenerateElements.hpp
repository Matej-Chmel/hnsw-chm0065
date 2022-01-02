#pragma once
#include "Action.hpp"

namespace chm {
	class ActionGenerateElements : public Action {
	public:
		ActionGenerateElements();
		void run() override;
		std::string text(long long elapsedMS) override;
	};
}
