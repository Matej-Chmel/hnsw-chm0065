#pragma once
#include "Action.hpp"

namespace chm {
	class TestQueryItself : public Action {
		bool bruteforce;

	public:
		void run() override;
		TestQueryItself(bool bruteforce);
		std::string text(long long elapsedMS) override;
	};
}
