#include "pch.hpp"
#include "ShaderBinding.hpp"

namespace ATMA
{

    ShaderBinding::ShaderBinding(const std::string &l_fileName): m_shaderFile(l_fileName) {}

    ShaderBinding::~ShaderBinding() {}

    const unsigned int &ShaderBinding::getBindID() const
    {
        return m_bindID;
    }

}