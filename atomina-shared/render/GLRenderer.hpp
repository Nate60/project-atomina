#pragma once
#include "pch.hpp"
#include "GLCamera.hpp"
#include "GLRenderable.hpp"
#include "GUI/AppWindow.hpp"
#include "math/MathFuncs.hpp"
#include "GLRenderContext.hpp"

namespace ATMA
{
    /**
     * used to handle drawing renderable objects to a target window
     */
    class GLRenderer
    {
    public:
        // default constructor
        GLRenderer();

        // deconstructor
        virtual ~GLRenderer();

        /**
         * enable texture blending
         * @param l_toggle set blending
         */
        void toggleBlend(const bool &l_toggle);

        /**
         * define the size of the frame buffer
         * @param w width
         * @param h height
         */
        void setFrameBufferDimensions(const int &w, const int &h);

        /**
         * change the render target to a specific window
         * @param l_win shared pointer to target window
         */
        void setWindow(std::shared_ptr<AppWindow> l_win);

        /**
         * give the camera to render to draw a scene
         * @param l_camera to render from
         */
        void startScene(const GLCamera &l_camera);

        /**
         * add renderable to render queue
         * @param l_renderable to add
         */
        void addElement(std::shared_ptr<GLRenderable> l_renderable);

        /**
         * finish draw call
         */
        void finishScene();
    protected:
        GLCamera m_camera{
            {0.f, 0.f},
            {0.f, 0.f}
        };

        std::vector<std::shared_ptr<GLRenderable>> m_elementContainer = std::vector<std::shared_ptr<GLRenderable>>();
        std::priority_queue<
            std::shared_ptr<GLRenderable>,
            std::vector<std::shared_ptr<GLRenderable>>,
            GLRenderableCompare>
            m_elementStack{m_elementContainer.begin(), m_elementContainer.end(), GLRenderableCompare()};
        std::shared_ptr<AppWindow> m_target{};
        std::shared_ptr<GLRenderContext> m_renderCtx;
    };

}