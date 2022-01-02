#include "filesystem.hpp"

namespace chm {
	void ensureDir(const fs::path& p) {
		if(!fs::exists(p))
			fs::create_directory(p);
	}
}
