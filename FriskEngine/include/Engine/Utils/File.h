#pragma once

#include <fstream>
#include "Engine/Core/Log.h"

namespace Frisk {
    STRING ParseFile(std::filesystem::path &a_FilePath) {
        std::ifstream file(a_FilePath);
        if (!file.is_open()) {
            Log::Error("failed to open file: ", a_FilePath.c_str(), "\n\n");
            return "";
        }

        STRING source = "";
		STRING line;

		while (std::getline(file, line)) {
			source += line;
			source += '\n';
		}

		return source;

    }
}
