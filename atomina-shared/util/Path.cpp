#include "pch.hpp"
#include "Path.hpp"

namespace ATMA
{

    Path::Path(std::string l_path)
    {
        m_path = std::filesystem::path{l_path};
        if(m_path.is_relative())
        {
            std::string composed_path =
                Path::getRootPath().parent_path().generic_string() + "/" + m_path.generic_string();
            m_path = std::filesystem::path(composed_path);
        }
    }

    const std::string Path::toString() const
    {
        return m_path.generic_string();
    }

}