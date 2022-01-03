#include <cstdlib>
#include <fstream>
#include <iostream>
#include "AppError.hpp"
#include "ElementGenerator.hpp"
#include "filesystem.hpp"
#include "Graph.hpp"
namespace fs = chm::fs;

constexpr size_t DIM = 128;
constexpr auto ELEMENT_MAX = 1.f;
constexpr auto ELEMENT_MIN = 0.f;
constexpr unsigned int ELEMENT_SEED = 100;
constexpr unsigned int LEVEL_SEED = 100;
constexpr size_t NODE_COUNT = 100;

void run(const fs::path& logsDir, const char* logName, bool useHeuristic, chm::FloatVec& coords) {
	chm::Config cfg(DIM);

	if(useHeuristic)
		cfg.setHeuristic();

	std::ofstream log(logsDir / logName);
	chm::Graph hnsw(cfg, LEVEL_SEED, false);
	hnsw.setDebugStream(log);
	hnsw.build(coords.data(), NODE_COUNT);
}

int main() {
	try {
		auto logsDir = fs::path(SOLUTION_DIR) / "logs";
		chm::ensureDir(logsDir);

		chm::ElementGenerator gen(ELEMENT_MIN, ELEMENT_MAX, ELEMENT_SEED);
		chm::FloatVec coords;
		gen.fill(coords, DIM, NODE_COUNT);

		run(logsDir, "heuristic.log", true, coords);
		run(logsDir, "simple.log", false, coords);

	} catch(chm::AppError& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
