#include "AppError.hpp"
#include "literals.hpp"
#include "TestCoordinatesLength.hpp"

namespace chm {
	void TestCoordinatesLength::run() {
		auto actualLen = this->s->nodeCoords->size();
		auto expectedLen = NODE_COUNT * DIM;

		if(actualLen != expectedLen)
			throw AppError("Wrong coordinates length.\nActual: "_f << actualLen << "\nExpected: " << expectedLen);
	}

	std::string TestCoordinatesLength::text(long long elapsedMS) {
		return "Coordinates length";
	}
}
