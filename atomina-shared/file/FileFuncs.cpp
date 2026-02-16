#include "pch.hpp"
#include "FileFuncs.hpp"

namespace ATMA
{

    std::string getWorkingDirectory()
    {
        return stdfs::current_path().string();
    }

    std::vector<stdfs::path> getDirectoryList(const Path &path, const std::string &filter)
    {
        std::basic_regex regex{filter, std::regex_constants::ECMAScript | std::regex_constants::icase};
        std::vector<stdfs::path> paths{};
        std::vector<stdfs::path> filtered_paths{};
        stdfs::path source_path{path.toString()};
        for(const auto &dir: stdfs::directory_iterator{source_path})
        {
            paths.emplace_back(dir.path());
        }

        std::copy_if(
            std::make_move_iterator(paths.begin()),
            std::make_move_iterator(paths.end()),
            std::back_inserter(filtered_paths),
            [regex](const stdfs::path &de) { return std::regex_search(de.string(), regex); }
        );

        return filtered_paths;
    }

    void removeFile(const Path &l_path)
    {
        static std::shared_ptr<FileSystem> filesystem = FileSystem::makeFileSystem();
        filesystem->removeFile(l_path);
    }

    void move(std::vector<char> &l_buffer, size_t &l_cursor, const size_t &l_adv, unsigned char *l_dest)
    {
        size_t begin = l_cursor;
        size_t end = l_cursor + l_adv;
        l_cursor += l_adv;
        std::move(l_buffer.begin() + begin, l_buffer.begin() + end, l_dest);
    }
}
