#include "pch.hpp"
#include "ObjectEventManager.hpp"

namespace ATMA
{

    ObjectEventManager::ObjectEventManager() {}

    ObjectEventManager::~ObjectEventManager() {}

    void ObjectEventManager::dispatchObjectEvent(ATMAContext *l_ctx, const ObjectEventContext &l_e)
    {
        for(auto &listenerVec: m_listeners)
        {
            if(l_e.m_objectEventType == listenerVec.first)
            {
                for(auto &listener: listenerVec.second)
                {
                    if(listener->isEnabled())
                    {
                        ATMA_ENGINE_INFO("Listener for event type {0:d} notified", l_e.m_objectEventType);
                        listener->notify(l_ctx, l_e);
                    }
                }
            }
        }
    }

    void ObjectEventManager::addObjectEventListener(
        const ObjectEventID &l_id,
        std::shared_ptr<ObjectEventListener> l_listener
    )
    {
        auto itr = m_listeners.find(l_id);
        if(itr == m_listeners.end())
        {
            std::vector<std::shared_ptr<ObjectEventListener>> newVec{l_listener};
            m_listeners[l_id] = newVec;
            ATMA_ENGINE_INFO("Object Event Listener for Object Event ID: {0:d} has been added", l_id);
        }
        else
        {
            m_listeners[l_id].emplace_back(l_listener);
            ATMA_ENGINE_INFO("Object Event Listener for Object Event ID: {0:d} has been added", l_id);
        }
    }

    void ObjectEventManager::purge()
    {
        m_listeners.clear();
        ATMA_ENGINE_INFO("purged listeners from context");
    }
}
