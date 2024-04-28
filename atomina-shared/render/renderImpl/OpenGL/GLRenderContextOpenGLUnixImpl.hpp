#ifdef __linux__
#    pragma once
#    include "pch.hpp"
#    include "core/api.hpp"
#    include "util/ATConst.hpp"
#    include "GUI/AppWindow.hpp"
#    include "GUI/window/WindowUnixImpl.hpp"
#    include "render/GLRenderContext.hpp"
#    include "render/GLProgram.hpp"
#    include "math/MathFuncs.hpp"

namespace ATMA
{

    /**
     * Unix Specific OpenGL implementation of Graphic Render Context
     */
    class ATMA_API GLRenderContextOpenGLUnixImpl: public GLRenderContext
    {
    public:
        // default deconstructor
        virtual ~GLRenderContextOpenGLUnixImpl();

        // default constructor
        GLRenderContextOpenGLUnixImpl();

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
        virtual void draw() override;

        /**
         * clears the view port that he Render context has been set to
         * to be all one colour
         */
        virtual void clear() override;

        // virtual void drawText(const std::string &l_text) override;
    protected:
        Display *m_display;
        Window m_rootWindow;
        GLint m_attributes[5] = {GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, 0};
        XVisualInfo *m_visualInfo;
        GLXContext m_glContext;
    };

}
#else
#    error Linux implementation included in non-Linux target
#endif