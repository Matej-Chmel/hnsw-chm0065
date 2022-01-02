#pragma once
#include "Bruteforce.hpp"
#include "ElementGenerator.hpp"
#include "filesystem.hpp"
#include "Graph.hpp"
#include "Unique.hpp"

namespace chm {
	constexpr size_t DIM = 128;
	constexpr auto ELEMENT_MAX = 1.f;
	constexpr auto ELEMENT_MIN = 0.f;
	constexpr unsigned int ELEMENT_SEED = 100;
	constexpr unsigned int LEVEL_SEED = 100;
	constexpr size_t NODE_COUNT = 100;
	constexpr size_t SEARCH_EF = 10;

	struct CommonState : public Unique {
		Bruteforce* bruteforce;
		fs::path dataDir;
		ElementGenerator* gen;
		Graph* hnsw;
		FloatVec* nodeCoords;

		~CommonState();
		CommonState();
	};
}
