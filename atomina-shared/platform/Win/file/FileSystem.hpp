#pragma once
#include "pch.hpp"
#include "file/FileSystem.hpp"
#include "util/Path.hpp"

namespace ATMA
{
    class FileSystemWin: public FileSystem
    {
    public:
        virtual void removeFile(const Path &l_path) override;
    };
}
