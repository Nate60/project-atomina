#include "OAS/Attribute.hpp"
#include "pch.hpp"
#include "AnimationWriter.hpp"

namespace ATMA
{
    ResourceWriter<Animation>::ResourceWriter() {}

    ResourceWriter<Animation>::~ResourceWriter() {}

    void ResourceWriter<Animation>::write(const std::shared_ptr<Animation> l_res, const Path &l_path)
    {
        std::basic_ofstream<char> animFile{l_path.toString(), std::ios_base::binary};
        animFile.exceptions(std::ios::failbit | std::ios::badbit);
        animFile.write(reinterpret_cast<const char *>(&l_res->data().frameCount()), sizeof(unsigned int));
        animFile.write(reinterpret_cast<const char *>(&l_res->data().sheetWidth()), sizeof(unsigned int));
        animFile.write(reinterpret_cast<const char *>(&l_res->data().startPos().x), sizeof(float));
        animFile.write(reinterpret_cast<const char *>(&l_res->data().startPos().y), sizeof(float));
        animFile.write(reinterpret_cast<const char *>(&l_res->data().frameSize().x), sizeof(float));
        animFile.write(reinterpret_cast<const char *>(&l_res->data().frameSize().y), sizeof(float));
        animFile.write(reinterpret_cast<const char *>(&l_res->data().loop()), sizeof(bool));
        ATMA_ENGINE_INFO(
            "wrote {} frameCount={} sheetWidth={} startPos.x={} startPos.y={} frameSize.x={} frameSize.y={} "
            "loop={}",
            l_path.toString().c_str(),
            l_res->data().frameCount(),
            l_res->data().sheetWidth(),
            l_res->data().startPos().x,
            l_res->data().startPos().y,
            l_res->data().frameSize().x,
            l_res->data().frameSize().y,
            l_res->data().loop()
        );
        for(unsigned int i = 0; i < l_res->data().frameCount(); i++)
        {
            animFile.write(
                reinterpret_cast<const char *>(&l_res->data().frameData()[i].ticks()), sizeof(unsigned short)
            );
            unsigned long long flags = l_res->data().frameData()[i].flags().to_ullong();
            animFile.write(reinterpret_cast<const char *>(&flags), sizeof(unsigned long long));
        }
    }

}
