#pragma once
#include "pch.hpp"
#include "AppWindow.hpp"

namespace ATMA
{
    using AppWindowID = unsigned int;
    using AppWindowContainer = std::unordered_map<AppWindowID, std::shared_ptr<AppWindow>>;

    class WindowManager
    {
    public:
        WindowManager();

        ~WindowManager();

        /**
         * Creates a new app window in the context
         * @returns id of the new window
         */
        [[nodiscard]] unsigned int createWindow(ATMAContext *ctx);

        /**
         * Gets the window pointer from the associated id
         * @param id of the window
         * @returns pointer to the window
         */
        [[nodiscard]] std::shared_ptr<AppWindow> getWindow(const unsigned int &l_id);

        /**
         * Removes the window from the context
         * @param id of the window
         */
        void removeWindow(const unsigned int &l_id);

        /**
         * destroys all windows and resets the last id to 0
         */
        void purge();
    protected:
        AppWindowID m_lastWindowID{0u};
        AppWindowContainer m_windows{};
    };
}
