#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "render/GLRenderContext.hpp"
#include "GUI/AppWindow.hpp"
#include "util/Log.hpp"

namespace ATMA
{

    /**
     * Dummy Implementation of Render Context
     */
    class ATMA_API GLRenderContextDummyImpl: public GLRenderContext
    {
    public:
        // default constructor
        GLRenderContextDummyImpl();

        // default deconstructor
        virtual ~GLRenderContextDummyImpl();

        /**
         * sets render context to target the given app window
         * @param l_window app window for the render context to target
         */
        virtual void setWindow(std::shared_ptr<AppWindow> l_window) override;

        virtual void draw(std::shared_ptr<Renderable> l_renderable) override;
    };

}