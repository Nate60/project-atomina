#pragma once
#include "pch.hpp"
#include "math/Vec2.hpp"
#include "util/Log.hpp"
#include "GUI/WindowEvent.hpp"


namespace ATMA
{

    using CallbackContainer = std::vector<std::function<void(const WindowEvent &)>>;
    using CallbackMap = std::unordered_map<WindowEventEnum, CallbackContainer>;

    /**
     * Framework for Windows to display the application to
     * be implemented for each platform
     */
    class AppWindow: public std::enable_shared_from_this<AppWindow>
    {
    public:
        AppWindow(
            const Vec2<unsigned int> &l_size = {180, 180},
            const std::string &l_name = "Atomina Application"
        );
        // default deconstructor
        virtual ~AppWindow();

        /**
         * sets the size of the window to the new size
         * @param l_size new dimensions of the window
         */
        void setSize(const Vec2<unsigned int> &l_size);

        /**
         * getter for window dimensions
         * @returns dimensions as a vector
         */
        const Vec2<unsigned int> &getSize() const;


        /**
         * notify the window to show to the display
         */
        void show();

        /**
         * get events that have been sent to the window and dispatch them
         */
        void poll();

        /**
         * swap the frame buffers for the the window
         */
        void swapBuffers();

        /**
         * getter for window name
         * @returns window name as string
         */
        const std::string &getName() const;

        /**
         * set the flag for the window that it should close
         */
        void notifyClose();

        /**
         * getter for the closed flag
         * @returns if the window should be closed
         */
        const bool shouldClose() const;

        GLFWwindow *m_windowHandle;

    protected:
        // Only constructor with default values to allow for default constructor
        // Specified the size and name of the window

        CallbackMap m_callbacks{};
        Vec2<unsigned int> m_size{};
        std::string m_name{};
        bool m_closed{};

        friend class GLRenderer;
    };

}