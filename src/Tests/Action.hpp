#pragma once
#include <string>
#include "CommonState.hpp"
#include "Unique.hpp"

namespace chm {
	class Action : public Unique {
	protected:
		Action(bool isTest = true);

	public:
		const bool isTest;

		virtual ~Action() = default;
		virtual void run(CommonState* s) = 0;
		virtual std::string text(long long elapsedMS) = 0;
	};
}
