#include "Engine/Utils/File.h"

#include "Engine/Core/Log.h"
#include <fstream>

#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <limits.h>
#include <unistd.h>
#elif __APPLE__
#include <climits>
#include <mach-o/dyld.h>
#endif

namespace Frisk
{
    STRING ParseFile(const std::filesystem::path &a_FilePath)
    {
        std::ifstream file(GetExecutableDir() / a_FilePath);

        if (!file.is_open())
        {
            Log::Error("failed to open file: ", a_FilePath, "\n\n");
            return "";
        }

        STRING source = "";
        STRING line;

        while (std::getline(file, line))
        {
            source += line;
            source += '\n';
        }

        return source;
    }

    std::filesystem::path GetExecutableDir()
    {
#ifdef _WIN32
        char buf[MAX_PATH];
        GetModuleFileNameA(nullptr, buf, MAX_PATH);
        return std::filesystem::path(buf).parent_path();
#elif __linux__
        char buf[PATH_MAX];
        ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
        if (len != -1)
            buf[len] = '\0';
        return std::filesystem::path(buf).parent_path();
#elif __APPLE__
        char buf[PATH_MAX];
        uint32_t size = sizeof(buf);
        if (_NSGetExecutablePath(buf, &size) != 0)
        {
            // buffer too small, resize and retry
            std::vector<char> big(size);
            _NSGetExecutablePath(big.data(), &size);
            return std::filesystem::canonical(big.data()).parent_path();
        }
        return std::filesystem::canonical(buf).parent_path();
#endif
    }
} // namespace Frisk
