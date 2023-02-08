#include "pch.hpp"
#include "ShaderProgram.hpp"
#include "GLAD/ShaderProgramGLADImpl.hpp"

namespace ATMA
{

    ShaderProgram::ShaderProgram() {}

    ShaderProgram::~ShaderProgram() {}

    std::shared_ptr<ShaderProgram> ShaderProgram::makeProgram()
    {
#ifdef ATMA_USE_OPENGL
        return std::make_shared<ShaderProgramGLADImpl>();
#endif
    }

}