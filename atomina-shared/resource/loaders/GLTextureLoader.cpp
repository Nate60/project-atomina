#include "pch.hpp"
#ifndef STB_IMAGE_IMPLEMENTATION
#    define STB_IMAGE_IMPLEMENTATION
#endif
#include <stb_image.h> //header only library only used here
                       //does not like being part of a precompiled header
#include "GLTextureLoader.hpp"

namespace ATMA
{

    ResourceLoader<GLTexture>::ResourceLoader() {}

    ResourceLoader<GLTexture>::~ResourceLoader() {}

    std::shared_ptr<GLTexture> ResourceLoader<GLTexture>::load(
        ATMAContext *l_ctx,
        const std::string &l_name,
        const Path &l_path,
        std::vector<char> &l_buffer,
        size_t &l_bytes
    )
    {
        int width, height, channels;
        unsigned char *data = stbi_load_from_memory(
            reinterpret_cast<unsigned char *>(l_buffer.data()), l_buffer.size(), &width, &height, &channels, 0
        );
        l_bytes = l_buffer.size();
        Texture texture = Texture(l_name, l_path, width, height, channels, data);
        return GLTexture::makeTexture(texture);
    }

    std::shared_ptr<GLTexture> ResourceLoader<GLTexture>::load(ATMAContext *l_ctx, const std::string &l_name)
    {
        Texture texture{l_name, ATMA::Path{""}, 0, 0, 0, 0};
        return GLTexture::makeTexture(texture);
    }
}
