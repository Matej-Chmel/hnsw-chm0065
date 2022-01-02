#pragma once
#include <filesystem>

namespace chm {
	namespace fs = std::filesystem;

	void ensureDir(const fs::path& p);
}
