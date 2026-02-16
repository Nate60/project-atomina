#include "pch.hpp"
#include "FileSystem.hpp"
#ifdef _WIN32
#    include "platform/Win/file/FileSystem.hpp"
#    define __ATMAMAKEFS() return std::make_shared<FileSystemWin>()
#elif __linux__
#    include "platform/Linux/file/FileSystem.hpp"
#    define __ATMAMAKEFS() return std::make_shared<FileSystemUnix>()
#endif

namespace ATMA
{

    FileSystem::FileSystem() {}

    FileSystem::~FileSystem() {}

    std::shared_ptr<FileSystem> FileSystem::makeFileSystem()
    {
        __ATMAMAKEFS();
    }

}
