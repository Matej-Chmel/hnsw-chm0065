#pragma once
#include "Action.hpp"

namespace chm {
	class TestCoordinatesLength : public Action {
	public:
		void run(CommonState* s) override;
		std::string text(long long elapsedMS) override;
	};
}
