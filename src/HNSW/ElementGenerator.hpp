#pragma once
#include <random>
#include "types.hpp"
#include "Unique.hpp"

namespace chm {
	class ElementGenerator : public Unique {
		std::default_random_engine gen;
		std::uniform_real_distribution<float> dist;

	public:
		ElementGenerator(float min, float max);
		ElementGenerator(float min, float max, unsigned int seed);
		void fill(FloatVec& target, size_t dim, size_t count);
	};
}
