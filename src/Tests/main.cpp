#include <iostream>
#include "Runner.hpp"

int main() {
	chm::Runner r(std::cout);
	return r.runAll();
}
