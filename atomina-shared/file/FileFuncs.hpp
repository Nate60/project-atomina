#pragma once
#include "core/api.hpp"
#include "pch.hpp"

namespace ATMA
{
    namespace stdfs = std::filesystem;

    /*
     * Gets the working directory of the executable as an absolute path string
     */
    ATMA_API std::string getWorkingDirectory();

    /*
     * Retrieves the names of all the files in the listed directory that match
     * the given filter
     */
    ATMA_API std::vector<stdfs::path>
    getDirectoryList(const stdfs::path &path, const std::string &filter = ".*[.].*");

}