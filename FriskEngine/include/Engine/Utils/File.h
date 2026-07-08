#pragma once

#include <filesystem>

namespace Frisk
{
    std::filesystem::path GetExecutableDir();
    STRING ParseFile(const std::filesystem::path &a_FilePath);

    enum class FileStatus
    {
        created,
        modified,
        erased
    };

    class FileWatcher
    {
      public:
        std::filesystem::path path;
        std::chrono::duration<int, std::milli> delay;

        FileWatcher(std::filesystem::path path_to_watch, std::chrono::duration<int, std::milli> delay)
            : path(path_to_watch), delay(delay)
        {
            for (auto &file : std::filesystem::recursive_directory_iterator(path_to_watch))
            {
                paths_[file.path().string()] = std::filesystem::last_write_time(file);
            }
        }

      private:
        std::unordered_map<std::string, std::filesystem::file_time_type> paths_;
    };
} // namespace Frisk
