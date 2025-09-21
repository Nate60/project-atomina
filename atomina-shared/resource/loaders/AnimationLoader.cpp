#include "pch.hpp"
#include "util/ATConst.hpp"
#include "util/Log.hpp"
#include "AnimationLoader.hpp"

namespace ATMA
{
    ResourceLoader<Animation>::ResourceLoader() {}

    ResourceLoader<Animation>::~ResourceLoader() {}

    std::shared_ptr<Animation> ResourceLoader<Animation>::load(const std::string &l_name, const Path &l_path)
    {
        std::basic_ifstream<char> animFile{l_path.toString(), std::ios_base::binary};
        std::vector<char> buffer;
        animFile.seekg(0, animFile.end);
        size_t length = animFile.tellg();
        animFile.seekg(0, animFile.beg);
        if(length > 0)
        {
            buffer.resize(length);
            animFile.exceptions(std::ios::failbit | std::ios::badbit);
            try
            {
                animFile.read(&buffer[0], length);
            }
            catch(const std::bad_cast &e)
            {
                ATMA_ENGINE_ERROR("failed to cast: {}", e.what());
                return nullptr;
            }
            catch(const std::ios_base::failure &e)
            {
                ATMA_ENGINE_ERROR("failed to read file {} : {}", l_path.toString().c_str(), e.what());
                return nullptr;
            }
            unsigned int frameCount;
            unsigned int sheetWidth;
            Vec2<float> startPos{0.f, 0.f};
            Vec2<float> frameSize{0.f, 0.f};
            bool loop;
            size_t bufferAdv = 0ul;
            auto copy = [](const std::vector<char> &buffer, size_t &cursor, size_t adv, unsigned char *dest)
            {
                size_t begin = cursor;
                size_t end = cursor + adv;
                cursor += adv;
                std::copy(buffer.begin() + begin, buffer.begin() + end, dest);
            };
            copy(buffer, bufferAdv, sizeof(unsigned int), reinterpret_cast<unsigned char *>(&frameCount));
            copy(buffer, bufferAdv, sizeof(unsigned int), reinterpret_cast<unsigned char *>(&sheetWidth));
            copy(buffer, bufferAdv, sizeof(float), reinterpret_cast<unsigned char *>(&startPos.x));
            copy(buffer, bufferAdv, sizeof(float), reinterpret_cast<unsigned char *>(&startPos.y));
            copy(buffer, bufferAdv, sizeof(float), reinterpret_cast<unsigned char *>(&frameSize.x));
            copy(buffer, bufferAdv, sizeof(float), reinterpret_cast<unsigned char *>(&frameSize.y));
            copy(buffer, bufferAdv, sizeof(bool), reinterpret_cast<unsigned char *>(&loop));
            std::vector<FrameData> data{};
            data.reserve(frameCount);
            for(int i = 0; i < frameCount; i++)
            {
                if(bufferAdv + sizeof(long long) + sizeof(unsigned char) > length)
                {
                    ATMA_ENGINE_ERROR("unexpected end of file: bufferAdv={} filelength={}", bufferAdv, length);
                    break;
                }
                unsigned short ticks;
                unsigned long long flags;
                copy(buffer, bufferAdv, sizeof(unsigned short), reinterpret_cast<unsigned char *>(&ticks));
                copy(buffer, bufferAdv, sizeof(unsigned long long), reinterpret_cast<unsigned char *>(&flags));
                std::bitset<ATConst::BITSET_SIZE> bitset{flags};
                FrameData fd{ticks, bitset};
                data.emplace_back(fd);
            }
            animFile.close();
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
        return nullptr;
    }

    std::shared_ptr<Animation> ResourceLoader<Animation>::load(const std::string &l_name)
    {
        AnimationData a{l_name, 0, 0, {}, {}, {}, false};
        return std::make_shared<Animation>(a);
    }

}
