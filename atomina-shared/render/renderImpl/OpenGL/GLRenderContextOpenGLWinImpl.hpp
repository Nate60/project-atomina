#ifdef _WINDOWS
#    pragma once
#    include "pch.hpp"
#    include "core/api.hpp"
#    include "util/ATConst.hpp"
#    include "GUI/AppWindow.hpp"
#    include "GUI/window/WindowWinImpl.hpp"
#    include "render/GLRenderContext.hpp"

namespace ATMA
{

    /**
     * Windows Specific OpenGL implementation of Graphic Render Context
     */
    class ATMA_API GLRenderContextOpenGLWinImpl: public GLRenderContext
    {
    public:
        // default deconstructor
        virtual ~GLRenderContextOpenGLWinImpl();

        // default constructor
        GLRenderContextOpenGLWinImpl();

        /**
         * sets render context to target the given app window
         * @param l_window app window for the render context to target
         */
        virtual void setWindow(std::shared_ptr<AppWindow> l_window) override;
    protected:
        // device context handle
        HDC m_hdc;
        // GL Render Context handle
        HGLRC m_hglrc;
    };

}
#else
#    error Windows implementation included in non-Windows target
#endif