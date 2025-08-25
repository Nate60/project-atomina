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
        animFile.write(reinterpret_cast<const char *>(&l_res->m_data.m_frameCount), sizeof(unsigned int));
        animFile.write(reinterpret_cast<const char *>(&l_res->m_data.m_sheetWidth), sizeof(unsigned int));
        animFile.write(reinterpret_cast<const char *>(&l_res->m_data.m_startPos.x), sizeof(float));
        animFile.write(reinterpret_cast<const char *>(&l_res->m_data.m_startPos.y), sizeof(float));
        animFile.write(reinterpret_cast<const char *>(&l_res->m_data.m_frameSize.x), sizeof(float));
        animFile.write(reinterpret_cast<const char *>(&l_res->m_data.m_frameSize.y), sizeof(float));
        animFile.write(reinterpret_cast<const char *>(&l_res->m_data.m_loop), sizeof(bool));
        ATMA_ENGINE_INFO(
            "wrote {} frameCount={} sheetWidth={} startPos.x={} startPos.y={} frameSize.x={} frameSize.y={} "
            "loop={}",
            l_path.toString().c_str(),
            l_res->m_data.m_frameCount,
            l_res->m_data.m_sheetWidth,
            l_res->m_data.m_startPos.x,
            l_res->m_data.m_startPos.y,
            l_res->m_data.m_frameSize.x,
            l_res->m_data.m_frameSize.y,
            l_res->m_data.m_loop
        );
        for(int i = 0; i < l_res->m_data.m_frameCount; i++)
        {
            animFile.write(
                reinterpret_cast<const char *>(&l_res->m_data.m_frameData[i].m_ticks), sizeof(unsigned short)
            );
            unsigned long long flags = l_res->m_data.m_frameData[i].m_flags.to_ullong();
            animFile.write(reinterpret_cast<const char *>(&flags), sizeof(unsigned long long));
        }
    }

}
