#include "pch.hpp"
#include "render/GLTexture.hpp"
#include "util/AtominaException.hpp"
#include "util/Log.hpp"
#include "TilesetLoader.hpp"
#include "core/ATMAContext.hpp"
#include "resource/ResourceManager.hpp"
#include "file/FileFuncs.hpp"

namespace ATMA
{
    ResourceLoader<Tileset>::ResourceLoader() {}

    ResourceLoader<Tileset>::~ResourceLoader() {}

    std::shared_ptr<Tileset> ResourceLoader<Tileset>::load(
        ATMAContext *l_ctx,
        const std::string &l_name,
        const Path &l_path,
        std::vector<char> &l_buffer,
        size_t &l_bytes
    )
    {
        std::unordered_map<unsigned int, Tile> tiles{};
        size_t setSize{};
        l_bytes = 0ul;
        move(l_buffer, l_bytes, sizeof(size_t), reinterpret_cast<unsigned char *>(&setSize));
        for(size_t i = 0; i < setSize; i++)
        {
            unsigned int tileType{};
            bool hasAnim{};
            move(l_buffer, l_bytes, sizeof(unsigned int), reinterpret_cast<unsigned char *>(&tileType));
            move(l_buffer, l_bytes, sizeof(bool), reinterpret_cast<unsigned char *>(&hasAnim));
            std::shared_ptr<Animation> anim{};
            if(hasAnim)
            {
                size_t animBufferSize{};
                std::vector<char> animBuffer{};
                animBuffer.resize(animBufferSize);
                std::move(l_buffer.begin() + l_bytes, l_buffer.begin() + animBufferSize, animBuffer.begin());
                ResourceLoader<Animation> animLoader{};
                size_t animBytes{};
                Tile tile{
                    tileType,
                    animLoader.load(l_ctx, l_name + "_anim" + std::to_string(i), l_path, animBuffer, animBytes)
                };
                tiles.emplace(std::make_pair(tileType, std::move(tile)));
                l_bytes += animBufferSize;
            }
            tiles.emplace(std::make_pair(tileType, Tile{tileType, anim}));
        }
        ATMA_ENGINE_INFO("loaded {} setSize={}", l_path.toString().c_str(), setSize);
        return std::make_shared<Tileset>(tiles);
    }

    std::shared_ptr<Tileset> ResourceLoader<Tileset>::load(ATMAContext *l_ctx, const std::string &l_name)
    {
        Tileset t{{}};
        return std::make_shared<Tileset>(t);
    }
}
