#include "CommonState.hpp"

namespace chm {
	CommonState::~CommonState() {
		delete this->bruteforce;
		delete this->gen;
		delete this->hnsw;
		delete this->nodeCoords;
	}
}
