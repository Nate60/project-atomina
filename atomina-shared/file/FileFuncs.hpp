#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/Path.hpp"
#include "FileSystem.hpp"

namespace ATMA
{
    namespace stdfs = std::filesystem;

    /**
     * Gets the working directory of the executable as an absolute path string
     * @returns full qualifed path
     */
    std::string getWorkingDirectory();

    /**
     * Retrieves the names of all the files in the listed directory that match
     * the given filter
     * @param l_path full qualified path of the directory
     * @param l_filter regex pattern to match against
     * @return list of full qualified paths in the directory
     */
    std::vector<stdfs::path> getDirectoryList(const Path &l_path, const std::string &l_filter = ".*[.].*");

    /**
     * to remove file from the file system at the given path
     * does not support directories.
     * @param l_path
     */
    void removeFile(const Path &l_path);

    /**
     * move bytes from buffer into another value reinterpreted as a char pointer
     * @param l_buffer buffer to consume
     * @param l_cursor cursor to track position in buffer
     * @param l_adv how many bytes to consume
     * @param l_dest destination pointer
     */
    void move(std::vector<char> &l_buffer, size_t &l_cursor, const size_t &l_adv, unsigned char *l_dest);
}
