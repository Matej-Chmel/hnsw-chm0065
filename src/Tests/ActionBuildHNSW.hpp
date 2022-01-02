#pragma once
#include "Action.hpp"
#include "Config.hpp"

namespace chm {
	class ActionBuildHNSW : public Action {
		Config cfg;

	public:
		ActionBuildHNSW(const Config& cfg);
		void run() override;
		std::string text(long long elapsedMS) override;
	};
}
