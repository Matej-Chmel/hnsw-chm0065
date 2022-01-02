#include <cstdlib>
#include <iostream>
#include "AppError.hpp"
#include "Bruteforce.hpp"
#include "ElementGenerator.hpp"
#include "Graph.hpp"
#include "recall.hpp"
#include "Timer.hpp"

constexpr size_t DIM = 128;
constexpr auto ELEMENT_MAX = 1.f;
constexpr auto ELEMENT_MIN = 0.f;
constexpr unsigned int ELEMENT_SEED = 100;
constexpr size_t K = 10;
constexpr unsigned int LEVEL_SEED = 100;
constexpr size_t NODE_COUNT = 100;
constexpr size_t QUERY_COUNT = 10;
constexpr size_t SEARCH_EF = 10;

struct Result {
	long long buildTimeMS{};
	chm::FloatVec2D distances;
	chm::IDVec2D IDs;
	long long searchTimeMS{};

	void print(const char* name) {
		std::cout << name <<
			"\nBuild time: " << this->buildTimeMS <<
			" ms\nSearch time: " << this->searchTimeMS << " ms\n";
	}

	void printRecall(Result& trueRes) {
		std::cout << "Recall: " << chm::recall(this->IDs, trueRes.IDs, K * QUERY_COUNT) << '\n';
	}
};

void runHNSW(
	const chm::Config& cfg, chm::FloatVec& nodeCoords, chm::FloatVec& queryCoords, Result& res, chm::Timer& timer
) {
	timer.start();
	chm::Graph hnsw(cfg, LEVEL_SEED, false);
	hnsw.build(nodeCoords.data(), NODE_COUNT);
	res.buildTimeMS = timer.stop();

	timer.start();
	hnsw.search(queryCoords.data(), QUERY_COUNT, K, SEARCH_EF, res.IDs, res.distances);
	res.searchTimeMS = timer.stop();
}

int main() {
	try {
		Result bfRes, hnswSimpleRes, hnswHeuristicRes;
		chm::ElementGenerator gen(ELEMENT_MIN, ELEMENT_MAX, ELEMENT_SEED);
		chm::FloatVec nodeCoords, queryCoords;
		chm::Timer timer;

		gen.fill(nodeCoords, DIM, NODE_COUNT);
		gen.fill(queryCoords, DIM, QUERY_COUNT);

		timer.start();
		chm::Bruteforce bf(nodeCoords.data(), DIM, NODE_COUNT);
		bfRes.buildTimeMS = timer.stop();
		
		timer.start();
		bf.search(queryCoords.data(), QUERY_COUNT, K, bfRes.IDs, bfRes.distances);
		bfRes.searchTimeMS = timer.stop();

		runHNSW(chm::Config(DIM).setHeuristic(), nodeCoords, queryCoords, hnswHeuristicRes, timer);
		runHNSW(chm::Config(DIM), nodeCoords, queryCoords, hnswSimpleRes, timer);

		bfRes.print("Bruteforce");
		std::cout << '\n';
		hnswHeuristicRes.print("HNSW(heuristic)");
		hnswHeuristicRes.printRecall(bfRes);
		std::cout << '\n';
		hnswSimpleRes.print("HNSW(simple)");
		hnswSimpleRes.printRecall(bfRes);
		

	} catch(chm::AppError& e) {
		std::cout << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
