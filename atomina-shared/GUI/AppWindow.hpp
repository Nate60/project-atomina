#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "math/Vec2.hpp"
#include "util/Log.hpp"
#include "WindowEvent.hpp"
#include "core/ATMAContext.hpp"

namespace ATMA
{
    using CallbackContainer = std::vector<std::function<void(const WindowEvent &)>>;
    using CallbackMap = std::unordered_map<WindowEventEnum, CallbackContainer>;

    /**
     * Abstract framework for Windows to display the application to
     * be implemented for each platform
     */
    class ATMA_API AppWindow: public std::enable_shared_from_this<AppWindow>
    {
    public:
        // default deconstructor
        virtual ~AppWindow();

        /**
         * sets the size of the window to the new size
         * @param l_size new dimensions of the window
         */
        virtual void setSize(const Vec2<unsigned int> &l_size) = 0;

        /**
         * getter for window dimensions
         * @returns dimensions as a vector
         */
        virtual const Vec2<unsigned int> &getSize() const;

        /**
         * notify the window to show to the display
         */
        virtual void show() = 0;

        /**
         * get events that have been sent to the window and dispatch them
         */
        virtual void poll() = 0;

        /**
         * getter for window name
         * @returns window name as string
         */
        virtual const std::string &getName() const;

        /**
         * set the flag for the window that it should close
         */
        virtual void notifyClose();

        /**
         * getter for the closed flag
         * @returns if the window should be closed
         */
        virtual const bool &shouldClose() const;

        /**
         * Swap the graphic buffers and bring the drawn buffer to the front
         */
        virtual void swapBuffers() = 0;

        /**
         * factory function for creating window for the platform
         * the application is running on
         * @returns pointer to the new window
         */
        static std::shared_ptr<AppWindow> makeWindow();
    protected:
        // Only constructor with default values to allow for default constructor
        // Specified the size and name of the window
        AppWindow(
            const Vec2<unsigned int> &l_size = {180, 180},
            const std::string &l_name = "Atomina Application"
        );

        unsigned int m_id;
        CallbackMap m_callbacks{};
        Vec2<unsigned int> m_size{};
        std::string m_name{};
        bool m_closed{};
    };

}