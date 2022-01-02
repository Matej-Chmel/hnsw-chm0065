#include "AppError.hpp"
#include "DataReader.hpp"
#include "literals.hpp"
#include "TestDataReader.hpp"

namespace chm {
	void TestDataReader::run() {
		auto path = this->s->dataDir / "nodeCoords.bin";
		DataReader reader(NODE_COUNT, DIM);

		reader.write(path, this->s->nodeCoords);

		if(!fs::exists(path))
			throw AppError("File "_f << path << " wasn't created.");

		auto len = this->s->nodeCoords->size();
		FloatVec readCoords;
		reader.read(path, &readCoords);

		for(size_t i = 0; i < len; i++) {
			auto& actual = readCoords[i];
			auto& expected = (*this->s->nodeCoords)[i];

			if(actual != expected)
				throw AppError("Components at index "_f << i << " mismatch.\nActual: " << actual << "\nExpected: " << expected);
		}
	}

	std::string TestDataReader::text(long long elapsedMS) {
		return "Data reader";
	}
}
