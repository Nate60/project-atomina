#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "Log.hpp"

namespace ATConst
{
    using namespace std::string_literals;
    static const size_t OBJECT_BIT_SIZE = 32;
    static const std::string DEFAULT_SHADER_PATH =
        "C:\\Users\\Sixti\\Source\\Repos\\project-atomina\\atomina-shared\\shader\\defaultVertex.shader"s;
    static const std::string DEFAULT_FRAG_SHADER_PATH =
        "C:\\Users\\Sixti\\Source\\Repos\\project-atomina\\atomina-shared\\shader\\defaultFrag.shader"s;

#ifdef _WINDOWS
    const PIXELFORMATDESCRIPTOR DEFAULT_PIXEL_FORMAT_D = {
        sizeof(PIXELFORMATDESCRIPTOR),
        1,
        PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER, // Flags
        PFD_TYPE_RGBA, // The kind of framebuffer. RGBA or palette.
        32,            // Colordepth of the framebuffer.
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        24, // Number of bits for the depthbuffer
        8,  // Number of bits for the stencilbuffer
        0,  // Number of Aux buffers in the framebuffer.
        PFD_MAIN_PLANE,
        0,
        0,
        0,
        0};

#elif __linux__
    const int DEFAULT_VISUAL_ATTRIBUTES[] = {
        GLX_X_RENDERABLE,
        True,
        GLX_DRAWABLE_TYPE,
        GLX_WINDOW_BIT,
        GLX_RENDER_TYPE,
        GLX_RGBA_BIT,
        GLX_X_VISUAL_TYPE,
        GLX_TRUE_COLOR,
        GLX_RED_SIZE,
        8,
        GLX_GREEN_SIZE,
        8,
        GLX_BLUE_SIZE,
        8,
        GLX_ALPHA_SIZE,
        8,
        GLX_DEPTH_SIZE,
        24,
        GLX_STENCIL_SIZE,
        8,
        GLX_DOUBLEBUFFER,
        True,
        GLX_SAMPLE_BUFFERS,
        1,
        GLX_SAMPLES,
        4,
        0L};
#endif
}
