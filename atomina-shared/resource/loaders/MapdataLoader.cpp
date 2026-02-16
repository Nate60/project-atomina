#include "pch.hpp"
#include "MapdataLoader.hpp"
#include "file/FileFuncs.hpp"
#include "util/Log.hpp"

namespace ATMA
{
    ResourceLoader<Mapdata>::ResourceLoader() {}

    ResourceLoader<Mapdata>::~ResourceLoader() {}

    std::shared_ptr<Mapdata> ResourceLoader<Mapdata>::load(
        ATMAContext *l_ctx,
        const std::string &l_name,
        const Path &l_path,
        std::vector<char> &l_buffer,
        size_t &l_bytes
    )
    {
        std::vector<unsigned int> mapData{};
        unsigned long mapSize{};
        unsigned int mapWidth{};
        Vec2<unsigned int> tileSize{};
        l_bytes = 0ul;
        move(l_buffer, l_bytes, sizeof(unsigned int), reinterpret_cast<unsigned char *>(&mapWidth));
        move(l_buffer, l_bytes, sizeof(unsigned int), reinterpret_cast<unsigned char *>(&tileSize.x));
        move(l_buffer, l_bytes, sizeof(unsigned int), reinterpret_cast<unsigned char *>(&tileSize.y));
        move(l_buffer, l_bytes, sizeof(unsigned long), reinterpret_cast<unsigned char *>(&mapSize));
        for(unsigned long i = 0; i < mapSize; i++)
        {
            unsigned int tileType{};
            move(l_buffer, l_bytes, sizeof(unsigned int), reinterpret_cast<unsigned char *>(&tileType));
            mapData.emplace_back(tileType);
        }
        ATMA_ENGINE_INFO(
            "loaded {} mapWidth={} tileSet.x={} tileSet.y={} mapSize={}",
            l_path.toString().c_str(),
            mapWidth,
            tileSize.x,
            tileSize.y,
            mapSize
        );
        return std::make_shared<Mapdata>(mapData, mapWidth, tileSize);
    }

    std::shared_ptr<Mapdata> ResourceLoader<Mapdata>::load(ATMAContext *l_ctx, const std::string &l_name)
    {
        Mapdata t{{}, {}, {}};
        return std::make_shared<Mapdata>(t);
    }
}
