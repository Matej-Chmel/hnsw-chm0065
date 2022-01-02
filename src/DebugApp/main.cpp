#include <filesystem>
#include <fstream>
#include "ElementGenerator.hpp"
#include "Graph.hpp"
namespace fs = std::filesystem;

constexpr size_t DIM = 128;
constexpr auto ELEMENT_MAX = 1.f;
constexpr auto ELEMENT_MIN = 0.f;
constexpr unsigned int ELEMENT_SEED = 100;
constexpr unsigned int LEVEL_SEED = 100;
constexpr size_t NODE_COUNT = 100;

void run(const fs::path& logsDir, const char* logName, bool useHeuristic, chm::FloatVec& nodeCoords) {
	chm::Config cfg(DIM);

	if(useHeuristic)
		cfg.setHeuristic();

	std::ofstream log(logsDir / logName);
	chm::Graph graph(cfg, LEVEL_SEED, false);
	graph.setDebugStream(log);
	graph.build(nodeCoords.data(), NODE_COUNT);
}

int main() {
	auto logsDir = fs::path(SOLUTION_DIR) / "logs";

	if(!fs::exists(logsDir))
		fs::create_directory(logsDir);

	chm::ElementGenerator gen(ELEMENT_MIN, ELEMENT_MAX, ELEMENT_SEED);
	chm::FloatVec nodeCoords;
	gen.fill(nodeCoords, DIM, NODE_COUNT);

	run(logsDir, "simple.log", false, nodeCoords);
	run(logsDir, "heuristic.log", true, nodeCoords);
	return 0;
}
