#pragma once
#include "core/api.hpp"
#include "pch.hpp"

namespace ATMA
{
    namespace stdfs = std::filesystem;

    /**
     * Gets the working directory of the executable as an absolute path string
     * @returns full qualifed path
     */
    ATMA_API std::string getWorkingDirectory();

    /**
     * Retrieves the names of all the files in the listed directory that match
     * the given filter
     * @param l_path full qualified path of the directory
     * @param l_filter regex pattern to match against
     * @return list of full qualified paths in the directory
     */
    ATMA_API std::vector<stdfs::path>
    getDirectoryList(const stdfs::path &l_path, const std::string &l_filter = ".*[.].*");

}