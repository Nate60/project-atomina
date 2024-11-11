#pragma once
#include "pch.hpp"
#include "GLCamera.hpp"
#include "GLRenderable.hpp"
#include "GUI/AppWindow.hpp"
#include "math/MathFuncs.hpp"
#include "GLRenderContext.hpp"

namespace ATMA
{

    class GLRenderer
    {
    public:

        GLRenderer();

        virtual ~GLRenderer();

        void toggleBlend(const bool &l_toggle);

        void setFrameBufferDimensions(const int &w, const int &h);

        void setWindow(std::shared_ptr<AppWindow> l_win);

        void startScene(const GLCamera &l_camera);

        void addElement(std::shared_ptr<GLRenderable> l_renderable);

        void finishScene();
    protected:
        GLCamera m_camera{
            {0.f, 0.f},
            {0.f,0.f}
        };

        std::vector<std::shared_ptr<GLRenderable>> m_elementContainer =
            std::vector<std::shared_ptr<GLRenderable>>();
        std::priority_queue<
            std::shared_ptr<GLRenderable>,
            std::vector<std::shared_ptr<GLRenderable>>,
            GLRenderableCompare>
            m_elementStack{
                m_elementContainer.begin(),
                m_elementContainer.end(),
                GLRenderableCompare()
            };
        std::shared_ptr<AppWindow> m_target{};
        std::shared_ptr<GLRenderContext> m_renderCtx;
    };

}