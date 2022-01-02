#include "ActionBuildBruteforce.hpp"
#include "literals.hpp"

namespace chm {
	ActionBuildBruteforce::ActionBuildBruteforce() : Action(false) {}

	void ActionBuildBruteforce::run(CommonState* s) {
		s->bruteforce = new Bruteforce(s->nodeCoords->data(), DIM, NODE_COUNT);
	}

	std::string ActionBuildBruteforce::text(long long elapsedMS) {
		return ("Bruteforce built in "_f << elapsedMS << " ms.").str();
	}
}
