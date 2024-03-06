#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "GUI/AppWindow.hpp"
#include "render/GLRenderable.hpp"
#include "render/GLBuffer.hpp"

namespace ATMA
{

    class ATMA_API GLRenderContext
    {
    public:
        virtual ~GLRenderContext();

        virtual void setWindow(std::shared_ptr<AppWindow> l_window) = 0;

        virtual void draw(std::shared_ptr<Renderable> l_renderable) = 0;

        // virtual void drawText(const std::string &l_text) = 0;

        static std::unique_ptr<GLRenderContext> makeRenderContext();
    protected:
        GLRenderContext();
    };

}