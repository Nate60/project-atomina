#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "math/Vec2.hpp"
#include "util/Log.hpp"

namespace ATMA
{

    /**
     * Abstract framework for Windows to display the application to
     * be implemented for each platform
     */
    class ATMA_API AppWindow
    {
    public:
        // Only constructor with default values to allow for default constructor
        // Specified the size and name of the window
        AppWindow(
            const Vec2<int> &l_size = {180, 180},
            const std::string &l_name = "Atomina Application"
        );

        // default deconstructor
        virtual ~AppWindow();

        /**
         * sets the size of the window to the new size
         * @param l_size new dimensions of the window
         */
        virtual void setSize(Vec2<int> l_size) = 0;

        /**
         * getter for window dimensions
         * @returns dimensions as a vector
         */
        virtual Vec2<int> getSize() = 0;

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
        virtual std::string_view getName();

        /**
         * getter for the closed flag
         * @returns if the window should be closed
         */
        virtual bool shouldClose();

        /**
         * factory function for creating window for the platform
         * the application is running on
         * @returns pointer to the new window
         */
        static std::shared_ptr<AppWindow> makeWindow();
    protected:
        Vec2<int> m_size{};
        std::string m_name{};
        bool m_closed{};
    };

}