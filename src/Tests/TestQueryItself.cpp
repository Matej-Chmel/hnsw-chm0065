#include "AppError.hpp"
#include "literals.hpp"
#include "TestQueryItself.hpp"

namespace chm {
	void TestQueryItself::run(CommonState* s) {
		IDVec2D resultIDs;
		FloatVec2D resultDistances;

		if(this->bruteforce)
			s->bruteforce->search(s->nodeCoords->data(), NODE_COUNT, 1, resultIDs, resultDistances);
		else
			s->hnsw->search(s->nodeCoords->data(), NODE_COUNT, 1, SEARCH_EF, resultIDs, resultDistances);

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

	TestQueryItself::TestQueryItself(bool bruteforce) : bruteforce(bruteforce) {}

	std::string TestQueryItself::text(long long elapsedMS) {
		return ("Query itself("_f << (this->bruteforce ? "bruteforce" : "HNSW") << ')').str();
	}
}
