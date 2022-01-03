#pragma once
#include <fstream>
#include "filesystem.hpp"
#include "types.hpp"
#include "Unique.hpp"

namespace chm {
	class DataReader : public Unique {
		size_t count;
		size_t dim;

		size_t getExpectedLen();

	public:
		DataReader(size_t count, size_t dim);
		void read(const fs::path& p, FloatVec* coords);
		void readBin(std::istream& s, FloatVec* coords);
		void write(const fs::path& p, FloatVec* coords);
		void writeBin(std::ostream& s, FloatVec* coords);
	};
}
