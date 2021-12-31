#include <iostream>
#include <unordered_set>
#include "Bruteforce.hpp"
#include "ElementGenerator.hpp"
#include "Graph.hpp"
using namespace chm;

constexpr size_t COUNT = 100;
constexpr size_t DIM = 128;
constexpr size_t K = 10;
constexpr size_t QUERY_COUNT = 100;

int main() {
	ElementGenerator gen(0.f, 1.f, 100);

	std::vector<float> coords;
	gen.fill(coords, DIM, COUNT);

	/*std::vector<float> queryCoords;
	gen.fill(queryCoords, DIM, QUERY_COUNT);*/

	/*Bruteforce bruteforce(coords.data(), DIM, COUNT);
	std::vector<std::vector<BruteforceItem>> bruteforceResults;
	bruteforce.search(coords.data(), COUNT, bruteforceResults, 1);

	for(size_t i = 0; i < QUERY_COUNT; i++) {
		std::cout << "QUERY " << i << '\n';

		auto& results = bruteforceResults[i];

		for(auto& item : results)
			std::cout << item.nodeID << ": " << item.distance << '\n';
		std::cout << '\n';
	}*/

	Graph hnsw(100, false);
	hnsw.build(coords.data(), DIM, COUNT);

	bool duplicateFound = false;

	for(size_t i = 0; i < COUNT; i++) {
		std::cout << "Node " << i << '\n';

		auto& layers = hnsw.layers[i];

		for(size_t j = 0; j < layers.size(); j++) {
			std::cout << "Layer " << j << ": ";

			std::unordered_set<size_t> elements;

			for(auto& neighbor : layers[j]) {
				std::cout << neighbor << ' ';

				if(elements.find(neighbor) == elements.end())
					elements.insert(neighbor);
				else {
					std::cout << "\nDUPLICATE " << neighbor << '\n';
					duplicateFound = true;
					break;
				}
			}

			if(duplicateFound)
				break;

			std::cout << '\n';
		}

		if(duplicateFound)
			break;

		std::cout << '\n';
	}

	std::cout << "ENTRY: " << hnsw.entryID << ", level " << hnsw.entryLevel << '\n';

	return 0;
}
