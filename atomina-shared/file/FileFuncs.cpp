#include "pch.hpp"
#include "FileFuncs.hpp"

namespace ATMA
{

    std::string getWorkingDirectory()
    {
        return stdfs::current_path();
    }

    std::vector<stdfs::path> getDirectoryList(const stdfs::path &path, const std::string &filter)
    {
        std::basic_regex regex{
            filter, std::regex_constants::ECMAScript | std::regex_constants::icase};
        std::vector<stdfs::path> paths{};
        std::vector<stdfs::path> filtered_paths{};
        for(const auto &dir: stdfs::directory_iterator{stdfs::current_path()})
        {
            paths.emplace_back(dir.path());
        }

        auto filtered = std::copy_if(
            std::make_move_iterator(paths.begin()),
            std::make_move_iterator(paths.end()),
            std::back_inserter(filtered_paths),
            [regex](const stdfs::path &de) { return std::regex_search(de.string(), regex); }
        );

        return filtered_paths;
    }
}