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

        /**
         * Sets the size of the current view port that he render context is drawing to
         * @param l_size dimensions of the new viewport
         */
        virtual void setSize(const Vec2<unsigned int> &l_size) override;

        /**
         * Starts a draw call for the renderable object
         * @param l_renderable the object to be drawn
         */
        virtual void draw(std::shared_ptr<GLRenderable> l_renderable) override;

        /**
         * clears the view port that he Render context has been set to
         * to be all one colour
         */
        virtual void clear() override;
    };

}