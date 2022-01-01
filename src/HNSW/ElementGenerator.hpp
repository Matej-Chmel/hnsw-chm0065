#pragma once
#include <random>
#include <vector>

namespace chm {
	class ElementGenerator {
		std::default_random_engine gen;
		std::uniform_real_distribution<float> dist;

	public:
		ElementGenerator(float min, float max);
		ElementGenerator(float min, float max, unsigned int seed);
		void fill(std::vector<float>& target, size_t dim, size_t count);
	};
}
