#pragma once
#include "Action.hpp"

namespace chm {
	class TestCoordinatesRange : public Action {
	public:
		void run(CommonState* s) override;
		std::string text(long long elapsedMS) override;
	};
}
