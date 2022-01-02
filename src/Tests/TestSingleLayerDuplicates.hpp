#pragma once
#include "Action.hpp"

namespace chm {
	class TestSingleLayerDuplicates : public Action {
	public:
		void run() override;
		std::string text(long long elapsedMS) override;
	};
}
