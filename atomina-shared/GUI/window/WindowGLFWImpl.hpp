#ifdef ATMA_USE_GLFW
#    pragma once
#    include "pch.hpp"
#    include "core/api.hpp"
#    include "GUI/Window.hpp"
#    include "util/Log.hpp"
#    include "render/RenderContext.hpp"

namespace ATMA
{

    /**
     * @brief GLFW specific implementation of window
     */
    class ATMA_API WindowGLFWImpl: public Window
    {
    public:
        // constructor specifying window name
        WindowGLFWImpl(const std::string &l_name = "ATMA_APP");

        // constructor specifying window properties and name
        WindowGLFWImpl(const Props &l_props, const std::string &l_name);

        // default deconstructor
        virtual ~WindowGLFWImpl();

        /**
         * @brief define the callback for when the window receives input
         * @param l_callback the function that is to be called
         */
        void setInputCallback(std::function<void(Window *, int, int, int, int)> l_callback
        ) override;

        /**
         * @brief define the callback for when the window receives the resize event
         * @param l_callback the function that is to be called
         */
        void setFrameResizeCallback(std::function<void(Window *, int, int)> l_callback) override;

        /**
         * @brief swap the frame buffers of the window to show the updated buffer
         */
        virtual void swapBuffers() override;

        /**
         * @brief poll the window for any events
         */
        virtual void pollEvents() override;

        /**
         * @brief switch the render context to make this window current
         * @param l_context Render Context of the Main Context
         */
        virtual void focusContext(const std::unique_ptr<RenderContext> &l_context) override;

        /**
         * @brief set the flag to let the program know that the window should close
         * @param l_bool toggle flag
         */
        virtual void setWindowShouldClose(bool l_bool) override;

        /**
         * @brief check the flag to see if the window should close
         * @return if the flag is true
         */
        virtual bool getWindowShouldClose() const override;

        /**
         * @brief get the dimensions of the frame buffer
         * @return dimensions of the frame
         */
        virtual Vec2<int> getFrameBufferSize() const override;

        /**
         * @brief static function to be called when OpenGL encounters
         * an error
         * @param source source of the error
         * @param type type of error
         * @param id error id
         * @param severity level of criticality
         * @param length length of message
         * @param message string of the error message
         * @param param user input parameter
         */
        static void glErrorCallback(
            GLenum source,
            GLenum type,
            GLuint id,
            GLenum severity,
            GLsizei length,
            const GLchar *message,
            const void *param
        );
    protected:
        GLFWwindow *m_window;

        /**
         * @brief contains data needed to send callbacks to GLFW
         */
        struct CallbackContainer
        {

            WindowGLFWImpl *m_parent;
            std::function<void(Window *, int, int, int, int)> m_input;
            std::function<void(Window *, int, int)> m_resize;
        };

        CallbackContainer m_callback_container;
    };
}

#endif
