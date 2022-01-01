#include "ElementGenerator.hpp"

namespace chm {
	ElementGenerator::ElementGenerator(float min, float max) : ElementGenerator(min, max, std::random_device{}()) {}

	ElementGenerator::ElementGenerator(float min, float max, unsigned int seed) {
		this->gen = std::default_random_engine(seed);
		this->dist = std::uniform_real_distribution<float>(min, max);
	}

	void ElementGenerator::fill(FloatVec& target, size_t dim, size_t count) {
		size_t len = count * dim;
		target.reserve(len);

		for(size_t i = 0; i < len; i++)
			target.push_back(this->dist(this->gen));
	}
}
