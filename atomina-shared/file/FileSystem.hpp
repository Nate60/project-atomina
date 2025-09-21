#pragma once

#include "util/Path.hpp"

namespace ATMA
{

    class FileSystem
    {
    protected:
        FileSystem();
    public:
        virtual ~FileSystem();

        static std::shared_ptr<FileSystem> makeFileSystem();

        virtual void removeFile(const Path &l_path) = 0;
    };

}
