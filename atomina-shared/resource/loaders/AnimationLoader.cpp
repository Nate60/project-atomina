#include "pch.hpp"
#include "util/ATConst.hpp"
#include "util/Log.hpp"
#include "AnimationLoader.hpp"
#include "file/FileFuncs.hpp"

namespace ATMA
{
    ResourceLoader<Animation>::ResourceLoader() {}

    ResourceLoader<Animation>::~ResourceLoader() {}

    size_t ResourceLoader<Animation>::anim_header_size = sizeof(unsigned int) + sizeof(unsigned int) + sizeof(float)
                                                       + sizeof(float) + sizeof(float) + sizeof(float) + sizeof(bool);
    size_t ResourceLoader<Animation>::anim_frame_size = sizeof(unsigned short) + sizeof(unsigned long long);

    std::shared_ptr<Animation> ResourceLoader<Animation>::load(
        ATMAContext *l_ctx,
        const std::string &l_name,
        const Path &l_path,
        std::vector<char> &l_buffer,
        size_t &l_bytes
    )
    {
        unsigned int frameCount;
        unsigned int sheetWidth;
        Vec2<float> startPos{0.f, 0.f};
        Vec2<float> frameSize{0.f, 0.f};
        bool loop;
        l_bytes = 0ul;
        move(l_buffer, l_bytes, sizeof(unsigned int), reinterpret_cast<unsigned char *>(&frameCount));
        move(l_buffer, l_bytes, sizeof(unsigned int), reinterpret_cast<unsigned char *>(&sheetWidth));
        move(l_buffer, l_bytes, sizeof(float), reinterpret_cast<unsigned char *>(&startPos.x));
        move(l_buffer, l_bytes, sizeof(float), reinterpret_cast<unsigned char *>(&startPos.y));
        move(l_buffer, l_bytes, sizeof(float), reinterpret_cast<unsigned char *>(&frameSize.x));
        move(l_buffer, l_bytes, sizeof(float), reinterpret_cast<unsigned char *>(&frameSize.y));
        move(l_buffer, l_bytes, sizeof(bool), reinterpret_cast<unsigned char *>(&loop));
        std::vector<FrameData> data{};
        data.reserve(frameCount);
        for(unsigned int i = 0; i < frameCount; i++)
        {
            if(l_bytes + sizeof(long long) + sizeof(unsigned char) > l_buffer.size())
            {
                ATMA_ENGINE_ERROR("unexpected end of file: l_bytes={} filelength={}", l_bytes, l_buffer.size());
                break;
            }
            unsigned short ticks;
            unsigned long long flags;
            move(l_buffer, l_bytes, sizeof(unsigned short), reinterpret_cast<unsigned char *>(&ticks));
            move(l_buffer, l_bytes, sizeof(unsigned long long), reinterpret_cast<unsigned char *>(&flags));
            std::bitset<ATConst::BITSET_SIZE> bitset{flags};
            FrameData fd{ticks, bitset};
            data.emplace_back(fd);
        }
        ATMA_ENGINE_INFO(
            "loaded {} frameCount={} sheetWidth={} startPos.x={} startPos.y={} frameSize.x={} frameSize.y={} "
            "loop={}",
            l_path.toString().c_str(),
            frameCount,
            sheetWidth,
            startPos.x,
            startPos.y,
            frameSize.x,
            frameSize.y,
            loop
        );
        AnimationData a{l_name, frameCount, sheetWidth, frameSize, startPos, data, loop};
        return std::make_shared<Animation>(a);
    }

    std::shared_ptr<Animation> ResourceLoader<Animation>::load(ATMAContext *l_ctx, const std::string &l_name)
    {
        AnimationData a{l_name, 0, 0, {}, {}, {}, false};
        return std::make_shared<Animation>(a);
    }

}
