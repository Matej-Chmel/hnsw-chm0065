#include <cstdlib>
#include "ActionBuildBruteforce.hpp"
#include "ActionBuildHNSW.hpp"
#include "ActionGenerateElements.hpp"
#include "AppError.hpp"
#include "Runner.hpp"
#include "TestConnectionWithItself.hpp"
#include "TestCoordinatesLength.hpp"
#include "TestCoordinatesRange.hpp"
#include "TestQueryItself.hpp"
#include "TestSingleLayerDuplicates.hpp"

namespace chm {
	void Runner::run(Action* a) {
		this->timer.start();
		a->run(&this->state);
		auto elapsedMS = this->timer.stop();

		if(a->isTest)
			*this->stream << "Test \"" << a->text(elapsedMS) << "\" PASSED in " << elapsedMS << " ms.\n";
		else
			*this->stream << a->text(elapsedMS) << '\n';
	}

	Runner::~Runner() {
		for(auto& a : this->actions)
			delete a;
	}

	int Runner::runAll() {
		try {
			for(auto& a : this->actions)
				this->run(a);

		} catch(AppError& e) {
			*this->stream << e.what() << '\n';
			return EXIT_FAILURE;
		}

		return EXIT_SUCCESS;
	}

	Runner::Runner(std::ostream& stream) : stream(&stream) {
		this->actions = {
			new ActionGenerateElements(),
			new TestCoordinatesLength(),
			new TestCoordinatesRange(),
			new ActionBuildBruteforce(),
			new TestQueryItself(true),
			new ActionBuildHNSW(),
			new TestQueryItself(false),
			new TestSingleLayerDuplicates(),
			new TestConnectionWithItself()
		};
	}
}
