#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

    /**
     * Wrapper for std::filesystem::path that maps relative paths to the path
     * that contains the running executable
     */
    class ATMA_API Path
    {
    public:
        /**
         * Constructor taking string as param to construct path from
         */
        Path(std::string l_path);

        /**
         * converts path to absolute path string
         */
        const std::string toString() const;

        /**
         * static function to find the path of where the executable is
         * located
         */
        static const std::filesystem::path &getRootPath()
        {
            // TODO: Execute once
#ifdef __linux__
            static const std::filesystem::path ROOTPATH =
                std::filesystem::canonical("/proc/self/exe");
#elif _WINDOWS
            wchar_t filename[MAX_PATH];
            DWORD maxLength = MAX_PATH;
            GetModuleFileNameW(NULL, filename, maxLength);
            std::wstring wstring = std::wstring{filename};
            static const std::filesystem::path ROOTPATH = std::filesystem::path{wstring};
#endif
            return ROOTPATH;
        }
    protected:
        std::filesystem::path m_path;
    };

}