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

    GLProgram::GLProgram() {}

    GLProgram::~GLProgram() {}

    std::shared_ptr<GLProgram> GLProgram::makeProgram()
    {
        __ATMAMAKEGLPROGRAM();
    }

    std::shared_ptr<GLProgram> GLProgram::makeDefaultProgram()
    {
        std::shared_ptr<GLShader> defaultFrag =
            GLShader::makeShader(ATConst::DEFAULT_FRAG_SHADER_PATH);
        std::shared_ptr<GLShader> defaultVert = GLShader::makeShader(ATConst::DEFAULT_SHADER_PATH);
        defaultFrag->compile(ShaderType::Fragment);
        defaultVert->compile(ShaderType::Vertex);
        std::shared_ptr<GLProgram> prog = GLProgram::makeProgram();
        prog->attachShader(defaultVert);
        prog->attachShader(defaultFrag);
        prog->link();
        return prog;
    }

}