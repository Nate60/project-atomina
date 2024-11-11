#include "pch.hpp"
#include "GLProgram.hpp"
#ifdef ATMA_OPENGL
#    include "renderImpl/OpenGL/GLProgramOpenGLImpl.hpp"
#    define __ATMAMAKEGLPROGRAM() return std::make_shared<GLProgramOpenGLImpl>()
#else
#    include "renderImpl/Dummy/GLProgramDummyImpl.hpp"
#    define __ATMAMAKEGLPROGRAM() return std::make_shared<GLProgramDummyImpl>()
#endif

namespace ATMA
{

    GLProgram::GLProgram() 
    {
    }

    GLProgram::~GLProgram() 
    {
    }

    std::shared_ptr<GLProgram> GLProgram::makeProgram()
    {
        __ATMAMAKEGLPROGRAM();
    }

}