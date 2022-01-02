#pragma once
#include <string>
#include "CommonState.hpp"
#include "Unique.hpp"

namespace chm {
	class Action : public Unique {
	protected:
		Action(bool isTest = true);
		CommonState* s;

	public:
		const bool isTest;

		virtual ~Action() = default;
		virtual void run() = 0;
		void setCommonState(CommonState* s);
		virtual std::string text(long long elapsedMS) = 0;
	};
}
