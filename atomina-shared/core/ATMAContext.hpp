#pragma once
#include "api.hpp"
#include "event/EventContext.hpp"
#include "util/ATConst.hpp"
#include "OAS/AttrBase.hpp"
#include "OAS/SysBase.hpp"
#include "state/BaseState.hpp"
#include "event/CallBackKey.hpp"
#include "util/Log.hpp"
#include "util/AtominaException.hpp"
#include "resource/Resource.hpp"
#include <memory>
#include <utility>

namespace ATMA
{

    using StateTypeID = unsigned int;
    using EventTypeID = unsigned int;

    class ATMAContext;
    class SysBase;
    class BaseState;

    using CallBackFunction = std::function<void(EventContext &)>;
    using CallBackRegistry = std::unordered_map<CallBackKey, CallBackFunction>;
    using EventQueue = std::vector<std::tuple<EventTypeID, StateTypeID, EventContext>>;

    using ObjectID = unsigned int;
    using AttrTypeID = unsigned int;
    using ObjectAttributes = std::pair<
        std::bitset<ATConst::OBJECT_BIT_SIZE>,
        std::unordered_map<AttrTypeID, std::shared_ptr<AttrBase>>>;
    using ObjectContainer = std::unordered_map<ObjectID, ObjectAttributes>;
    using AttributeFactory =
        std::unordered_map<AttrTypeID, std::function<std::shared_ptr<AttrBase>(void)>>;

    using SystemID = unsigned int;
    using SystemContainer = std::unordered_map<SystemID, std::shared_ptr<SysBase>>;

    using StateStack = std::unordered_map<StateTypeID, std::unique_ptr<BaseState>>;

    using ResourceID = unsigned int;
    using ResourceTypeID = unsigned int;
    using ResourceContainer =
        std::unordered_map<ResourceID, std::pair<ResourceTypeID, std::optional<std::string>>>;
    using LoadedResourceContainer = std::unordered_map<ResourceID, std::shared_ptr<Resource>>;

    class ATMA_API ATMAContext
    {
    private:
        CallBackRegistry m_callbacks{};
        EventQueue m_eventQueue{};

        std::mutex m_mtx{};
        ObjectID m_lastId{0u};
        AttributeFactory m_attrFactory{};
        ObjectContainer m_objects{};

        SystemContainer m_systems{};

        StateTypeID m_currentStateID{};
        StateStack m_states{};

        ResourceContainer m_resources;
        LoadedResourceContainer m_loadedResources;
        ResourceID m_lastResourceId{0u};

        ATMAContext()
        {
            ATMA_ENGINE_INFO("ATMAContext has been initialized");
        }

        // helper function
        void objectUpdated(
            const unsigned int &l_objectID,
            const std::bitset<ATConst::OBJECT_BIT_SIZE> &l_bits
        );
        void systemUpdated(const unsigned int &l_systemID);
    public:
        // get context
        static ATMAContext &getContext()
        {
            static ATMAContext context; // Guaranteed to be destroyed.
                                        // Instantiated on first use.
            return context;
        }

        ATMAContext(ATMAContext const &) = delete;
        void operator=(ATMAContext const &) = delete;

        // add callback
        void addCallback(
            const unsigned int &l_eventType,
            const unsigned int &l_stateType,
            CallBackFunction l_func
        );

        // remove callback
        void removeCallback(const unsigned int &l_eventType, const unsigned int &l_stateType);

        // add event
        void addEvent(
            const unsigned int &l_eventType,
            const unsigned int &l_stateType,
            EventContext &&l_context
        );

        // add factory function
        template<class T>
        void registerAttributeType(const unsigned int &l_attrType)
        {
            auto itr = m_attrFactory.find(l_attrType);
            if(itr != m_attrFactory.end())
            {
                throw RegistrationException(
                    "Attribute type: " + std::to_string(l_attrType) + " has already been registered"
                );
            }
            else
            {
                m_attrFactory[l_attrType] = []() -> std::shared_ptr<AttrBase>
                { return std::make_shared<T>(); };
                ATMA_ENGINE_INFO("Registered Attribute of type {0:d}", l_attrType);
            }
        }

        [[nodiscard]] unsigned int createObject();

        [[nodiscard]] unsigned int createObject(const std::bitset<ATConst::OBJECT_BIT_SIZE> &l_bits
        );

        // add attribute
        void addAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType);

        // remove attribute
        void removeAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType);

        // check attribute
        bool hasAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType);

        // get Attribute
        template<class T>
        std::shared_ptr<T>
        getAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType)
        {
            auto itr = m_objects.find(l_objectID);
            if(itr == m_objects.end())
            {
                throw ValueNotFoundException(
                    "object id: " + std::to_string(l_objectID)
                    + " does not contain any attributes or does not exist"
                );
            }
            else
            {
                auto innerItr = itr->second.second.find(l_attrType);
                if(innerItr == itr->second.second.end())
                {
                    throw ValueNotFoundException(
                        "object id: " + std::to_string(l_objectID)
                        + " does not contain attribute type: " + std::to_string(l_attrType)
                    );
                }
                else
                {
                    return std::dynamic_pointer_cast<T>(innerItr->second);
                }
            }
        }

        // add system
        template<class T>
        void addSystemType(const unsigned int &l_systemID)
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
                ATMA_ENGINE_INFO("Registered System of type {0:d}", l_systemID);
                systemUpdated(l_systemID);
            }
        }

        void disableSystem(const unsigned int &l_systemID);

        void enableSystem(const unsigned int &l_systemID);

        bool hasSystem(const unsigned int &l_systemID);

        template<class T>
        std::shared_ptr<T> getSystem(const unsigned int &l_systemID)
        {
            auto itr = m_systems.find(l_systemID);
            if(itr == m_systems.end())
            {
                throw ValueNotFoundException(
                    "system id: " + std::to_string(l_systemID) + " does not exist"
                );
            }
            else
            {
                return std::dynamic_pointer_cast<T>(itr->second);
            }
        }

        // remove system
        void removeSystem(const unsigned int &l_systemID);

        // add state
        void addState(const unsigned int &l_stateType, std::unique_ptr<BaseState> l_state);

        // remove state
        void removeState(const unsigned int &l_stateType);

        // switch to state
        void switchToState(const unsigned int &l_stateType);

        // check state
        bool hasState(const unsigned int &l_stateType);

        // register resource
        unsigned int registerResource(
            const unsigned int &l_resourceType,
            const std::optional<std::string> &l_filename = std::nullopt
        );

        bool hasResource(const unsigned int &l_resourceID);

        // load resource
        template<class T>
        std::shared_ptr<T> loadResource(const unsigned int &l_resourceID)
        {
            auto itr = m_resources.find(l_resourceID);
            if(itr == m_resources.end())
            {
                throw ValueNotFoundException(
                    "resource ID: " + std::to_string(l_resourceID)
                    + " has not been registered with ATMA Context"
                );
            }
            else
            {

                ATMA_ENGINE_INFO("checking file name");
                if(auto &filename = itr->second.second; filename.has_value())
                {
                    m_loadedResources[l_resourceID] = std::shared_ptr<T>{new T{filename.value()}};
                }
                else
                {
                    m_loadedResources[l_resourceID] = std::shared_ptr<T>{new T{}};
                }
                return std::static_pointer_cast<T>(m_loadedResources[l_resourceID]);
            }
        }

        bool hasLoadedResource(const unsigned int &l_resourceID);

        // unload resource
        void unloadResource(const unsigned int &l_resourceID);

        // remove resource
        void removeResource(const unsigned int &l_resourceID);

        void update();

        void purgeObjects();

        void purgeSystems();

        void purgeStates();

        void purgeEvents();

        void purgeResources();

        void purge();
    };

}