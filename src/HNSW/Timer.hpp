#pragma once
#include <chrono>

namespace chm {
	namespace chr = std::chrono;

	class Timer {
		chr::system_clock::time_point from;

	public:
		void start();
		long long stop();
		Timer();
	};
}
