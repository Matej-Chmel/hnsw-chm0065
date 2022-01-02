#include "CommonState.hpp"

namespace chm {
	CommonState::~CommonState() {
		delete this->bruteforce;
		delete this->gen;
		delete this->hnsw;
		delete this->nodeCoords;
	}

	CommonState::CommonState()
		: bruteforce(nullptr), dataDir(fs::path(SOLUTION_DIR) / "data"),
		gen(nullptr), hnsw(nullptr), nodeCoords(nullptr) {

		ensureDir(this->dataDir);
	}
}
