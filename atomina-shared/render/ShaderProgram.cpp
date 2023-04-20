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

    std::shared_ptr<ShaderProgram> ShaderProgram::makeDefaultProgram()
    {
        std::shared_ptr<Shader> defaultFrag =
            std::make_shared<Shader>("defaultFrag", ATConst::DEFAULT_FRAG_SHADER_PATH);
        std::shared_ptr<Shader> defaultVert =
            std::make_shared<Shader>("defaultVert", ATConst::DEFAULT_SHADER_PATH);
        defaultFrag->compile(ShaderType::Fragment);
        defaultVert->compile(ShaderType::Vertex);
        std::shared_ptr<ShaderProgram> prog = ShaderProgram::makeProgram();
        prog->attachShader(defaultVert);
        prog->attachShader(defaultFrag);
        prog->link();
        return prog;
    }

}