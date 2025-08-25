#pragma once
#include "pch.hpp"
#include "file/FileSystem.hpp"
#include "util/Path.hpp"
#include <cstdio>

namespace ATMA
{
    class FileSystemUnix: public FileSystem
    {
    public:
        virtual void removeFile(const Path &l_path) override;
    };
}
