#pragma once
#include "Action.hpp"

namespace chm {
	class TestConnectionWithItself : public Action {
	public:
		void run(CommonState* s) override;
		std::string text(long long elapsedMS) override;
	};
}
