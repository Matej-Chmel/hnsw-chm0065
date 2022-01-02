#pragma once
#include <ostream>
#include <vector>
#include "Action.hpp"
#include "Timer.hpp"

namespace chm {
	class Runner : public Unique {
		std::vector<Action*> actions;
		CommonState state;
		std::ostream* stream;
		Timer timer;

		void run(Action* a);

	public:
		~Runner();
		int runAll();
		Runner(std::ostream& stream);
	};
}
