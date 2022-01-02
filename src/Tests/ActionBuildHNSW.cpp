#include "ActionBuildHNSW.hpp"
#include "literals.hpp"

namespace chm {
	ActionBuildHNSW::ActionBuildHNSW(const Config& cfg) : Action(false), cfg(cfg) {}

	void ActionBuildHNSW::run() {
		delete this->s->hnsw;
		this->s->hnsw = new Graph(this->cfg, LEVEL_SEED, false);
		this->s->hnsw->build(this->s->nodeCoords->data(), NODE_COUNT);
	}

	std::string ActionBuildHNSW::text(long long elapsedMS) {
		return (
			"HNSW ("_f << (this->s->hnsw->cfg.useHeuristic ? "heuristic" : "simple") <<
			") graph built in " << elapsedMS << " ms."
		).str();
	}
}
