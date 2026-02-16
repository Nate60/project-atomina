#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "resource/ResourceWriter.hpp"
#include "sound/AudioWave.hpp"
#include "util/Log.hpp"

namespace ATMA
{
    template<>
    class ResourceWriter<AudioWave>
    {
    public:
        ResourceWriter();
        virtual ~ResourceWriter();
        void write(const std::shared_ptr<AudioWave> l_res, const Path &l_path);
    };
}
