#include "pch.hpp"
#include "WindowManager.hpp"

namespace ATMA
{
    WindowManager::WindowManager() {}

    WindowManager::~WindowManager() {}

    unsigned int WindowManager::createWindow(ATMAContext *ctx)
    {
        m_windows[m_lastWindowID] = std::make_shared<AppWindow>(ctx);
        auto id = m_lastWindowID++;
        ATMA_ENGINE_INFO("Created Window with id {}", id);
        return id;
    }

    std::shared_ptr<AppWindow> WindowManager::getWindow(const unsigned int &l_id)
    {
        auto itr = m_windows.find(l_id);
        if(itr == m_windows.end())
        {
            throw ValueNotFoundException("Window with id: " + std::to_string(l_id) + " does not exist");
        }
        else
        {
            return itr->second;
        }
    }

    void WindowManager::removeWindow(const unsigned int &l_id)
    {
        auto itr = m_windows.find(l_id);
        if(itr == m_windows.end())
        {
            throw ValueNotFoundException("Window with id: " + std::to_string(l_id) + " does not exist in ATMA context");
        }
        else
        {
            ATMA_ENGINE_INFO("Removed Window: {}", itr->second->getName());
            m_windows.erase(itr);
        }
    }

    void WindowManager::purge()
    {
        m_windows.clear();
        m_lastWindowID = 0u;
    }

}
