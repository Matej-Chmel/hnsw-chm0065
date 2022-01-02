#pragma once

namespace chm {
	struct Config {
		size_t dim;

		size_t efConstruction;
		size_t M;
		float mL;
		size_t Mmax;
		size_t Mmax0;

		bool useHeuristic;
		bool extendCandidates;
		bool keepPrunedConnections;

		void calcML();
		Config(size_t dim);
		Config& setHeuristic(bool extendCandidates = false, bool keepPrunedConnections = false);
	};
}
