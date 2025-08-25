#pragma once
#include "core/ATMAContext.hpp"
#include "pch.hpp"
#include "SysBase.hpp"
#include "util/ATConst.hpp"

namespace ATMA
{

    using SystemID = unsigned int;
    using SystemContainer = std::unordered_map<SystemID, std::shared_ptr<SysBase>>;

    class SystemManager
    {
    public:
        SystemManager();
        virtual ~SystemManager();

        /**
         * Called when an object has had an attribute added or removed
         * and will let any relevant systems know.
         * @param l_objectID object id of the object that was changed
         * @param l_bits the bit set of the object describing which attributes it has
         */
        void objectUpdated(const unsigned int &l_objectID, const std::bitset<ATConst::BITSET_SIZE> &l_bits);

        /**
         * Called when a system has been removed or added to the context and
         * will notify the system of any potential relevant objects
         * @param l_ctx Engine Context
         * @param l_systemID id of the system that has changed
         */
        void systemUpdated(ATMAContext *l_ctx, const unsigned int &l_systemID);

        /**
         * Registers a system type to the context and associates it with the given class type
         * @tparam Class Type of the system
         * @param l_systemID type id of the system to register
         * @throws Registration Exception if the type id already has an existing system class
         * registered
         */
        template<class T>
        void addSystemType(ATMAContext *l_ctx, const unsigned int &l_systemID)
        {
            auto itr = m_systems.find(l_systemID);
            if(itr != m_systems.end())
            {
                throw RegistrationException(
                    "System type: " + std::to_string(l_systemID) + " has already been registered"
                );
            }
            else
            {
                m_systems[l_systemID] = std::make_shared<T>();
                ATMA_ENGINE_INFO("Registered System of type {0}", m_systems[l_systemID]->getType());
                systemUpdated(l_ctx, l_systemID);
            }
        }

        /**
         * Disables a system so it no longer is notifed for object events
         * @param l_systemID type id of the system to disable
         * @throws ValueNotFound Exception if the type id is not registered
         */
        void disableSystem(const unsigned int &l_systemID);

        /**
         * Enables a system to listen for object events
         * @param l_systemID type id of the system to enable
         * @throws ValueNotFound Exception if the type id is not registered
         */
        void enableSystem(const unsigned int &l_systemID);

        /**
         * checks if the context has the system type id registered
         * @param l_systemID type id of the system to check for
         * @returns if the system type id is registered
         */
        [[nodiscard]] bool hasSystem(const unsigned int &l_systemID);

        /**
         * gets a pointer to the corresponding system
         * @tparam type class of the system
         * @param l_systemID type id of the system to get
         * @returns pointer of the system
         * @throws ValueNotFound Exception if the system id is not registered
         */
        template<class T>
        [[nodiscard]] std::shared_ptr<T> getSystem(const unsigned int &l_systemID)
        {
            auto itr = m_systems.find(l_systemID);
            if(itr == m_systems.end())
            {
                throw ValueNotFoundException("system id: " + std::to_string(l_systemID) + " does not exist");
            }
            else
            {
                return std::dynamic_pointer_cast<T>(itr->second);
            }
        }

        /**
         * Removes a system from the context registry
         * @param l_systemID type id of the system to unregister
         * @throws ValueNotFound Exception when system id is not found in registry
         */
        void removeSystem(const unsigned int &l_systemID);

        /**
         * update all systems according to delta time
         * @param l_dt time since last tick
         */
        void update(ATMAContext *l_ctx, const double &l_dt);

        /**
         * removes all systems and resets the next id back to 0
         */
        void purge();

        /**
         * removes all objects from a system
         * @param l_systemID
         */
        void purgeSystem(const unsigned int &l_systemID);

        friend class AttributeManager;
    protected:
        SystemContainer m_systems{};
    };
}
