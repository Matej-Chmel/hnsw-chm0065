#include <ios>
#include "AppError.hpp"
#include "DataReader.hpp"
#include "literals.hpp"

namespace chm {
	void throwMissingComponents(size_t actualLen, size_t expectedLen) {
		throw AppError("Not enough components in file.\nAvailable: "_f << actualLen << "\nExpected: " << expectedLen);
	}

	void throwNotOpened(const fs::path& p) {
		throw AppError("File "_f << p << " couldn't be opened.");
	}

	void throwUnsupportedExtension(const fs::path& p) {
		throw AppError("File "_f << p << " has unsupported extension.");
	}

	size_t DataReader::getExpectedLen() {
		return this->count * this->dim;
	}

	DataReader::DataReader(size_t count, size_t dim) : count(count), dim(dim) {}

	void DataReader::read(const fs::path& p, FloatVec* coords) {
		auto ext = p.extension().string();

		if(!fs::exists(p))
			throw AppError("File "_f << p << " doesn't exist.");

		std::ifstream s(p, std::ios::binary);

		if(!s.is_open())
			throwNotOpened(p);

		if(ext == ".bin")
			this->readBin(s, coords);
		else
			throwUnsupportedExtension(p);
	}

	void DataReader::readBin(std::istream& s, FloatVec* coords) {
		s.seekg(0, std::ios::end);
		auto fileSize = s.tellg();
		s.seekg(0, std::ios::beg);

		auto actualLen = fileSize / sizeof(float);
		auto expectedLen = this->getExpectedLen();

		if (fileSize % sizeof(float))
			throw AppError("Not all components in file are floats.");
		if (actualLen < expectedLen)
			throwMissingComponents(actualLen, expectedLen);

		coords->resize(expectedLen);
		s.read(reinterpret_cast<std::istream::char_type*>(coords->data()), expectedLen * sizeof(float));
	}

	void DataReader::write(const fs::path& p, FloatVec* coords) {
		auto ext = p.extension().string();
		std::ofstream s(p, std::ios::binary);

		if (!s.is_open())
			throwNotOpened(p);

		if(ext == ".bin")
			this->writeBin(s, coords);
		else
			throwUnsupportedExtension(p);
	}

	void DataReader::writeBin(std::ostream& s, FloatVec* coords) {
		auto expectedLen = this->getExpectedLen();

		if (coords->size() < expectedLen)
			throwMissingComponents(coords->size(), expectedLen);

		s.write(reinterpret_cast<std::ostream::char_type*>(coords->data()), expectedLen * sizeof(float));
	}
}
