#include <cmath>
#include "Config.hpp"

namespace chm {
	void Config::calcML() {
		this->mL = 1 / std::logf(float(this->M));
	}

	Config::Config(size_t dim) :
		dim(dim), efConstruction(200), M(16), Mmax(this->M), Mmax0(this->M * 2),
		useHeuristic(false), extendCandidates(false), keepPrunedConnections(false) {

		this->calcML();
	}

	Config& Config::setHeuristic(bool extendCandidates, bool keepPrunedConnections) {
		this->useHeuristic = true;
		this->extendCandidates = extendCandidates;
		this->keepPrunedConnections = keepPrunedConnections;
		return *this;
	}
}
