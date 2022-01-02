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
};

int main() {
	try {
		Result bfRes, hnswRes;
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

		timer.start();
		chm::Graph hnsw(chm::Config(DIM), LEVEL_SEED, false);
		hnsw.build(nodeCoords.data(), NODE_COUNT);
		hnswRes.buildTimeMS = timer.stop();

		timer.start();
		hnsw.search(queryCoords.data(), QUERY_COUNT, K, SEARCH_EF, hnswRes.IDs, hnswRes.distances);
		hnswRes.searchTimeMS = timer.stop();

		auto recall = chm::recall(hnswRes.IDs, bfRes.IDs, K * QUERY_COUNT);

		bfRes.print("Bruteforce");
		std::cout << '\n';
		hnswRes.print("HNSW(simple)");
		std::cout << "Recall: " << recall << '\n';

	} catch(chm::AppError& e) {
		std::cout << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
