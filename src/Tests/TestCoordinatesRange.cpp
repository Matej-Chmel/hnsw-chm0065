#include "AppError.hpp"
#include "literals.hpp"
#include "TestCoordinatesRange.hpp"

namespace chm {
	void TestCoordinatesRange::run(CommonState* s) {
		auto len = s->nodeCoords->size();

		for(size_t i = 0; i < len; i++) {
			auto& c = (*s->nodeCoords)[i];

			if(c < ELEMENT_MIN || c > ELEMENT_MAX)
				throw AppError(
					"Coordinate "_f << c << " at index " << i <<
					" out of range.\nRange: [" << ELEMENT_MIN << ", " << ELEMENT_MAX << "]."
				);
		}
	}

	std::string TestCoordinatesRange::text(long long elapsedMS) {
		return "Coordinates range";
	}
}
