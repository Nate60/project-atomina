#include "pch.hpp"
#include "resource/ResourceWriter.hpp"
#include "MapdataWriter.hpp"

namespace ATMA
{

    ResourceWriter<Mapdata>::ResourceWriter() {}

    ResourceWriter<Mapdata>::~ResourceWriter() {}

    void ResourceWriter<Mapdata>::write(const std::shared_ptr<Mapdata> l_res, const Path &l_path)
    {

        std::basic_ofstream<char> mapFile{l_path.toString(), std::ios_base::binary};
        mapFile.exceptions(std::ios::failbit | std::ios::badbit);
        unsigned long mapSize = l_res->data().size();
        mapFile.write(reinterpret_cast<const char *>(&l_res->width()), sizeof(unsigned int));
        mapFile.write(reinterpret_cast<const char *>(&l_res->tilesize().x), sizeof(unsigned int));
        mapFile.write(reinterpret_cast<const char *>(&l_res->tilesize().y), sizeof(unsigned int));
        mapFile.write(reinterpret_cast<const char *>(&mapSize), sizeof(unsigned long));
        for(auto &tile: l_res->data())
        {
            mapFile.write(reinterpret_cast<const char *>(&tile), sizeof(unsigned int));
        }
        ATMA_ENGINE_INFO("Wrote {} width={} mapsize={}", l_path.toString(), l_res->width(), l_res->data().size());
    }
}
