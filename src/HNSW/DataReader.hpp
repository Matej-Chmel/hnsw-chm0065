#pragma once
#include <fstream>
#include "filesystem.hpp"
#include "types.hpp"
#include "Unique.hpp"

namespace chm {
	class DataReader : public Unique {
		FloatVec* coords;
		size_t count;
		size_t dim;

		size_t getExpectedLen();
		void readBin(std::ifstream& s);
		void writeBin(std::ofstream& s);

	public:
		DataReader(size_t count, size_t dim);
		void read(const fs::path& p, FloatVec* coords);
		void write(const fs::path& p, FloatVec* coords);
	};
}
