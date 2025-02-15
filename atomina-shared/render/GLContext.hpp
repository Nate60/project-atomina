#pragma once
#include "pch.hpp"
#include "core/api.hpp"

namespace ATMA
{
    /**
     * class for initializing GL library
     */
    class GLContext
    {
    public:
        /**
         * initialize GL library
         */
        static void init()
        {
            static std::once_flag once;
            std::call_once(
                once,
                []
                {
                    if(!glfwInit())
                    {
                        ATMA_ENGINE_ERROR("Failed to initialize GLFW");
                        return;
                    }
                    ATMA_ENGINE_INFO("GLFW INIT OK!");
                }
            );
        }
    };

}