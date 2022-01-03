#include <cstdlib>
#include <iostream>
#include "AppError.hpp"
#include "DataReader.hpp"
#include "filesystem.hpp"
#include "Graph.hpp"
namespace fs = chm::fs;

constexpr size_t DIM = 128;
constexpr unsigned int LEVEL_SEED = 100;
constexpr size_t NODE_COUNT = 20;
constexpr auto USE_RND_SEED = false;

void run(const fs::path& logsDir, const char* logName, bool useHeuristic, chm::FloatVec& coords) {
	chm::Config cfg(DIM);

	if(useHeuristic)
		cfg.setHeuristic();

	chm::Graph hnsw(cfg, LEVEL_SEED, USE_RND_SEED);
	hnsw.build(coords.data(), NODE_COUNT);

	std::ofstream log(logsDir / logName);
	hnsw.printLayers(log);
}

int main() {
	try {
		auto slnDir = fs::path(SOLUTION_DIR);
		auto dataDir = slnDir / "data";
		auto logsDir = slnDir / "logs";
		chm::ensureDir(logsDir);

		chm::FloatVec coords;
		chm::DataReader reader(NODE_COUNT, DIM);
		reader.read(dataDir / "sift1M.bin", &coords);

		run(logsDir, "SIFT_heuristic.log", true, coords);
		run(logsDir, "SIFT_simple.log", false, coords);

	} catch(chm::AppError& e) {
		std::cerr << e.what() << '\n';
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}
