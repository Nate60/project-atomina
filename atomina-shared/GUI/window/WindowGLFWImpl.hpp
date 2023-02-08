#ifdef ATMA_USE_GLFW
#    pragma once
#    include "pch.hpp"
#    include "core/api.hpp"
#    include <GLFW/glfw3.h>
#    include "GUI/Window.hpp"

namespace ATMA
{

    class ATMA_API WindowGLFWImpl: public Window
    {
    public:
        WindowGLFWImpl(const std::string &l_name = "ATMA_APP");

        WindowGLFWImpl(const Props &l_props, const std::string &l_name);

        void setInputCallback(std::function<void(Window *, int, int, int, int)> l_callback
        ) override;

        virtual void swapBuffers() override;

        virtual void pollEvents() override;

        virtual void focus() override;

        virtual void setWindowShouldClose(bool l_bool) override;

        virtual bool getWindowShouldClose() const override;
    protected:
        GLFWwindow *m_window;

        struct CallbackContainer
        {

            WindowGLFWImpl *m_parent;
            std::function<void(Window *, int, int, int, int)> m_self;
        };

        CallbackContainer m_callback_container;
    };
}

#endif
