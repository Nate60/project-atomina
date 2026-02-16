#include "pch.hpp"
#include "resource/ResourceLoader.hpp"
#include "resource/ResourceWriter.hpp"
#include "resource/loaders/AnimationLoader.hpp"
#include "resource/graphics/Animation.hpp"
#include "TilesetWriter.hpp"

namespace ATMA
{
    ResourceWriter<Tileset>::ResourceWriter() {}

    ResourceWriter<Tileset>::~ResourceWriter() {}

    void ResourceWriter<Tileset>::write(const std::shared_ptr<Tileset> l_res, const Path &l_path)
    {
        std::basic_ofstream<char> tileFile{l_path.toString(), std::ios_base::binary};
        tileFile.exceptions(std::ios::failbit | std::ios::badbit);
        size_t setSize = l_res->m_tiles.size();
        tileFile.write(reinterpret_cast<const char *>(&setSize), sizeof(size_t));
        ATMA_ENGINE_INFO("wrote {} tileCount={}", l_path.toString().c_str(), setSize);
        for(auto &tile: l_res->m_tiles)
        {
            tileFile.write(reinterpret_cast<const char *>(&tile.first), sizeof(unsigned int));
            bool hasAnimation = tile.second.animation() == nullptr;
            tileFile.write(reinterpret_cast<const char *>(&hasAnimation), sizeof(bool));
            if(hasAnimation)
            {
                size_t animBufferSize =
                    ResourceLoader<Animation>::anim_header_size
                    + tile.second.animation()->data().frameCount() * ResourceLoader<Animation>::anim_frame_size;
                tileFile.write(reinterpret_cast<const char *>(&animBufferSize), sizeof(size_t));
                tileFile.flush();
                ResourceWriter<Animation> animWriter{};
                animWriter.write(tile.second.animation(), l_path);
            }
        }
    }

}
