#include <ios>
#include "AppError.hpp"
#include "DataReader.hpp"
#include "literals.hpp"

namespace chm {
	void throwMissingComponents(size_t actualLen, size_t expectedLen) {
		throw AppError("Not enough components in file.\nAvailable: "_f << actualLen << "\nExpected: " << expectedLen);
	}

	void throwUnsupportedExtension(const fs::path& p) {
		throw AppError("File "_f << p << " has unsupported extension.");
	}

	size_t DataReader::getExpectedLen() {
		return this->count * this->dim;
	}

	void DataReader::readBin(std::ifstream& s) {
		s.seekg(0, std::ios::end);
		auto fileSize = s.tellg();
		s.seekg(0, std::ios::beg);

		auto actualLen = fileSize / sizeof(float);
		auto expectedLen = this->getExpectedLen();

		if(fileSize % sizeof(float))
			throw AppError("Not all components in file are floats.");
		if(actualLen < expectedLen)
			throwMissingComponents(actualLen, expectedLen);

		this->coords->resize(expectedLen);
		s.read(reinterpret_cast<std::ifstream::char_type*>(this->coords->data()), expectedLen * sizeof(float));
	}

	void DataReader::writeBin(std::ofstream& s) {
		auto expectedLen = this->count * this->dim;

		if(this->coords->size() < expectedLen)
			throwMissingComponents(this->coords->size(), expectedLen);

		s.write(reinterpret_cast<std::ifstream::char_type*>(this->coords->data()), expectedLen * sizeof(float));
	}

	DataReader::DataReader(size_t count, size_t dim) : coords(nullptr), count(count), dim(dim) {
	}

	void DataReader::read(const fs::path& p, FloatVec* coords) {
		this->coords = coords;
		auto ext = p.extension().string();

		if(!fs::exists(p))
			throw AppError("File "_f << p << " doesn't exist.");

		std::ifstream s(p, std::ios::binary);

		if(!s.is_open())
			throw AppError("File "_f << p << " couldn't be opened.");

		if(ext == ".bin")
			this->readBin(s);
		else
			throwUnsupportedExtension(p);
	}

	void DataReader::write(const fs::path& p, FloatVec* coords) {
		this->coords = coords;
		auto ext = p.extension().string();
		std::ofstream s(p, std::ios::binary);

		if(ext == ".bin")
			this->writeBin(s);
		else
			throwUnsupportedExtension(p);
	}
}
