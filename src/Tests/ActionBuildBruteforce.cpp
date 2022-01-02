#include "ActionBuildBruteforce.hpp"
#include "literals.hpp"

namespace chm {
	ActionBuildBruteforce::ActionBuildBruteforce() : Action(false) {}

	void ActionBuildBruteforce::run() {
		this->s->bruteforce = new Bruteforce(this->s->nodeCoords->data(), DIM, NODE_COUNT);
	}

	std::string ActionBuildBruteforce::text(long long elapsedMS) {
		return ("Bruteforce built in "_f << elapsedMS << " ms.").str();
	}
}
