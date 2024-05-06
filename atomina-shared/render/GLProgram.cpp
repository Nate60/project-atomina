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
        ATMA_ENGINE_TRACE("Creating GL Program");
    }

    GLProgram::~GLProgram() 
    {
        ATMA_ENGINE_TRACE("Deleting GL Program");
    }

    std::shared_ptr<GLProgram> GLProgram::makeProgram()
    {
        __ATMAMAKEGLPROGRAM();
    }

    std::shared_ptr<GLProgram> GLProgram::makeDefaultProgram()
    {
        static std::shared_ptr<GLShader> defaultFrag;
        static std::shared_ptr<GLShader> defaultVert;
        static std::shared_ptr<GLProgram> prog;
        static std::once_flag flag;
        std::call_once(flag, [&]() {

            defaultFrag = GLShader::makeShader(ATConst::DEFAULT_FRAG_SHADER_PATH);
            defaultVert = GLShader::makeShader(ATConst::DEFAULT_SHADER_PATH);
            prog = GLProgram::makeProgram();
            defaultFrag->compile(ShaderType::Fragment);
            defaultVert->compile(ShaderType::Vertex);
            prog->attachShader(defaultVert);
            prog->attachShader(defaultFrag);
            prog->link();
        });

        return prog;
    }

}