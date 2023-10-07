#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "GUI/AppWindow.hpp"


namespace ATMA
{

    class ATMA_API GLRenderContext
    {
    public:
        virtual ~GLRenderContext();

        virtual void setWindow(std::shared_ptr<AppWindow> l_window) = 0;

        static std::unique_ptr<GLRenderContext> makeRenderContext();
    protected:
        GLRenderContext();
    };

}