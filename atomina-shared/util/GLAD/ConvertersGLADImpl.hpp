#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{

    inline const int GLADImageDataFormat(const int &l_channels, const int &l_bitsPerChannel = 8)
    {
        switch(l_channels)
        {
        case 1:
            switch(l_bitsPerChannel)
            {
            case 1:
            case 2:
            case 4:
                return -1;
            case 8:
                return GL_R8;
            case 16:
                return GL_R16;
            }
        case 2:
            switch(l_bitsPerChannel)
            {
            case 1:
            case 2:
            case 4:
                return -1;
            case 8:
                return GL_RG8;
            case 16:
                return GL_RG16;
            }
        case 3:
            switch(l_bitsPerChannel)
            {
            case 1:
            case 2:
                return -1;
            case 4:
                return GL_RGB4;
            case 8:
                return GL_RGB8;
            case 16:
                return GL_RGB16F;
            }
        case 4:
            switch(l_bitsPerChannel)
            {
            case 1:
                return -1;
            case 2:
                return GL_RGBA2;
            case 4:
                return GL_RGBA4;
            case 8:
                return GL_RGBA8;
            case 16:
                return GL_RGBA16;
            }
        }
        return -1;
    }

    inline const int GLADImageFormat(const int &l_channels)
    {
        switch(l_channels)
        {
        case 1:
            return GL_LUMINANCE;
        case 2:
            return GL_LUMINANCE_ALPHA;
        case 3:
            return GL_RGB;
        case 4:
            return GL_RGBA;
        }
        return -1;
    }

}