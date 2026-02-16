#include "pch.hpp"
#include "util/Log.hpp"
#include "GLShaderLoader.hpp"

using namespace std::string_literals;

namespace ATMA
{

    ResourceLoader<GLShader>::ResourceLoader() {}

    ResourceLoader<GLShader>::~ResourceLoader() {}

    std::shared_ptr<GLShader> ResourceLoader<GLShader>::load(
        ATMAContext *l_ctx,
        const std::string &l_name,
        const Path &l_path,
        std::vector<char> &l_buffer,
        size_t &l_bytes
    )
    {
        ATMA_ENGINE_TRACE("stating to loading in shader from buffer");
        std::string shaderText = ""s;
        ATMA_ENGINE_TRACE("Resizing string buffer");
        shaderText.resize(l_buffer.size());
        ATMA_ENGINE_TRACE("moving values to string buffer");
        std::move(l_buffer.begin(), l_buffer.end(), shaderText.begin());
        Shader shader{l_name, l_path, shaderText};
        return GLShader::makeShader(shader);
    }

    std::shared_ptr<GLShader> ResourceLoader<GLShader>::load(ATMAContext *l_ctx, const std::string &l_name)
    {
        Shader shader{l_name, ATMA::Path{""}, ""};
        return GLShader::makeShader(shader);
    }
}
