#pragma once
#include "pch.hpp"
#include "ObjectEventListener.hpp"
#include "util/Log.hpp"

namespace ATMA
{

    using ObjectEventID = unsigned int;
    using ObjectEventListeners = std::unordered_map<ObjectEventID, std::vector<std::shared_ptr<ObjectEventListener>>>;

    /**
     * Manager for Object Events, handles dispatching of object events to
     * corresponding listeners
     */
    class ObjectEventManager
    {
    public:
        ObjectEventManager();
        virtual ~ObjectEventManager();
        /**
         * pushes object event to all registered object event listeners
         * for that object event type
         * @param l_e object event details
         */
        void dispatchObjectEvent(ATMAContext *l_ctx, const ObjectEventContext &l_e);

        /**
         * Adds object event listener to the notification interface
         * of the context
         * @param l_id type id of the object event that the listener is listening for
         * @param l_listener pointer to the listener
         */
        void addObjectEventListener(const ObjectEventID &l_id, std::shared_ptr<ObjectEventListener> l_listener);

        /**
         * unregisters all listeners from the context
         */
        void purge();
    protected:
        ObjectEventListeners m_listeners{};
    };
}
