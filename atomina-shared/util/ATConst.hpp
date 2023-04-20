#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "Log.hpp"
#include "render/ShaderProgram.hpp"

namespace ATConst
{

    using namespace std::string_literals;

    static const size_t OBJECT_BIT_SIZE = 32;
    static const unsigned int MAIN_WINDOW_ID = 0;
    static const std::string DEFAULT_SHADER_PATH = "shader\\defaultVertex.shader"s;
    static const std::string DEFAULT_FRAG_SHADER_PATH = "shader\\defaultFrag.shader"s;
    static const std::string DEFAULT_TEXTURE_PATH = "res\\shaggysheet.png"s;

}
