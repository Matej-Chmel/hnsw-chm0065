#include <cstdlib>
#include <functional>
#include <iostream>
#include <unordered_set>
#include "AppError.hpp"
#include "Bruteforce.hpp"
#include "ElementGenerator.hpp"
#include "Graph.hpp"
#include "literals.hpp"
using namespace chm::literals;

constexpr size_t DIM = 128;
constexpr auto ELEMENT_MAX = 1.f;
constexpr auto ELEMENT_MIN = 0.f;
constexpr unsigned int ELEMENT_SEED = 100;
constexpr unsigned int LEVEL_SEED = 100;
constexpr size_t NODE_COUNT = 100;
constexpr size_t SEARCH_EF = 10;

typedef std::function<void(chm::IDVec& layer, size_t layerID, size_t nodeID)> LayerFunc;

void forEachLayer(chm::Graph& hnsw, LayerFunc f) {
	auto count = hnsw.getNodeCount();

	for(size_t nodeID = 0; nodeID < count; nodeID++) {
		auto& nodeLayers = hnsw.layers[nodeID];
		auto nodeLayersLen = nodeLayers.size();

		for(size_t layerID = 0; layerID < nodeLayersLen; layerID++) {
			auto& layer = nodeLayers[layerID];
			f(layer, layerID, nodeID);
		}
	}
}

void passed(const char* name) {
	std::cout << name << " PASSED\n";
}

void testConnectionWithItself(chm::Graph& hnsw) {
	forEachLayer(hnsw, [](chm::IDVec& layer, size_t layerID, size_t nodeID) {
		for(auto& neighbor : layer)
			if(neighbor == nodeID)
				throw chm::AppError("Element "_f << nodeID << " is connected with itself at layer " << layerID << '.');
	});
	passed("testConnectionWithItself");
}

void testCoordinatesLen(chm::FloatVec& coords, size_t elementCount) {
	auto actualLen = coords.size();
	auto expectedLen = elementCount * DIM;

	if(actualLen != expectedLen)
		throw chm::AppError("Wrong coordinates length.\nActual: "_f << actualLen << "\nExpected: " << expectedLen);

	passed("testCoordinatesLen");
}

void testCoordinatesRange(chm::FloatVec& coords) {
	auto len = coords.size();

	for(size_t i = 0; i < len; i++) {
		auto& c = coords[i];

		if(c < ELEMENT_MIN || c > ELEMENT_MAX)
			throw chm::AppError(
				"Coordinate "_f << c << " at index " << i <<
				" out of range.\nRange: [" << ELEMENT_MIN << ", " << ELEMENT_MAX << "]."
			);
	}

	passed("testCoordinatesRange");
}

void testQueryForThemselves(chm::IDVec2D& resultIDs, chm::FloatVec2D& resultDistances) {
	for(size_t i = 0; i < NODE_COUNT; i++) {
		auto& IDs = resultIDs[i];
		auto& distances = resultDistances[i];

		if(IDs.size() != 1)
			throw chm::AppError(""_f << IDs.size() << " elements were found for element " << i << '.');
		if(IDs.size() != distances.size())
			throw chm::AppError("Vectors of IDs and distances have mismatched length for element "_f << i << '.');
		if(IDs[0] != i)
			throw chm::AppError("Element "_f << i << " didn't query for itself but for element " << IDs[i] << '.');
		if(distances[0] != 0.f)
			throw chm::AppError("Distance is not 0 for element "_f << i << '.');
	}
}

void testQueryForThemselves(chm::Bruteforce& bruteforce, chm::FloatVec& nodeCoords) {
	chm::IDVec2D resultIDs;
	chm::FloatVec2D resultDistances;

	bruteforce.search(nodeCoords.data(), NODE_COUNT, 1, resultIDs, resultDistances);
	testQueryForThemselves(resultIDs, resultDistances);
	passed("testQueryForThemselves(bruteforce)");
}

void testQueryForThemselves(chm::Graph& hnsw, chm::FloatVec& nodeCoords) {
	chm::IDVec2D resultIDs;
	chm::FloatVec2D resultDistances;

	hnsw.search(nodeCoords.data(), NODE_COUNT, 1, SEARCH_EF, resultIDs, resultDistances);
	testQueryForThemselves(resultIDs, resultDistances);
	passed("testQueryForThemselves(HNSW)");
}

void testSingleLayerDuplicates(chm::Graph& hnsw) {
	forEachLayer(hnsw, [](chm::IDVec& layer, size_t layerID, size_t nodeID) {
		std::unordered_set<size_t> neighbors;
		neighbors.reserve(layer.size());

		for(auto& neighborID : layer)
			if(neighbors.find(neighborID) == neighbors.end())
				neighbors.insert(neighborID);
			else
				throw chm::AppError(
					"Element "_f << neighborID << " is duplicated in layer " << layerID <<
					" for element " << nodeID << '.'
				);
	});
	passed("testSingleLayerDuplicates");
}

int main() {
	try {
		chm::ElementGenerator gen(ELEMENT_MIN, ELEMENT_MAX, ELEMENT_SEED);
		chm::FloatVec nodeCoords;
		gen.fill(nodeCoords, DIM, NODE_COUNT);

		testCoordinatesLen(nodeCoords, NODE_COUNT);
		testCoordinatesRange(nodeCoords);

		chm::Bruteforce bruteforce(nodeCoords.data(), DIM, NODE_COUNT);
		testQueryForThemselves(bruteforce, nodeCoords);

		chm::Graph hnsw(LEVEL_SEED, false);
		hnsw.build(nodeCoords.data(), DIM, NODE_COUNT);

		testQueryForThemselves(hnsw, nodeCoords);
		testSingleLayerDuplicates(hnsw);
		testConnectionWithItself(hnsw);

		hnsw.printLayers(std::cout);

	} catch(chm::AppError& e) {
		std::cout << e.what() << '\n';
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
