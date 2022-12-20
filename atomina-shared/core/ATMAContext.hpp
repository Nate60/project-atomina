#pragma once
#include "api.hpp"
#include "event/ObjectEvent.hpp"
#include "event/ObjectEventListener.hpp"
#include "util/ATConst.hpp"
#include "OAS/AttrBase.hpp"
#include "OAS/SysBase.hpp"
#include "state/BaseState.hpp"
#include "event/WindowEvent.hpp"
#include "GUI/Window.hpp"
#include "util/Log.hpp"
#include "util/AtominaException.hpp"
#include "resource/Resource.hpp"
#include <memory>

namespace ATMA
{

    using StateTypeID = unsigned int;
    using EventTypeID = unsigned int;

    class ATMAContext;
    class SysBase;
    class BaseState;

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
    using WindowID = unsigned int;
    using ResourceContainer =
        std::unordered_map<ResourceID, std::pair<ResourceTypeID, std::optional<std::string>>>;
    using LoadedResourceContainer = std::unordered_map<ResourceID, std::shared_ptr<Resource>>;
    using WindowContainer = std::unordered_map<WindowID, std::shared_ptr<Window>>;

    using ObjectEventID = unsigned int;
    using ObjectEventListeners =
        std::unordered_map<ObjectEventID, std::vector<std::shared_ptr<ObjectEventListener>>>;

    class ATMA_API ATMAContext
    {
    protected:
        bool initialized{false};
        std::mutex m_mtx{};
        ObjectID m_lastObjectID{0u};
        AttributeFactory m_attrFactory{};
        ObjectContainer m_objects{};

        SystemContainer m_systems{};

        StateTypeID m_currentStateID{};
        StateStack m_states{};

        ResourceContainer m_resources{};
        LoadedResourceContainer m_loadedResources{};
        ResourceID m_lastResourceId{0u};

        WindowID m_lastWindowID{0u};
        WindowContainer m_windows{};

        ObjectEventListeners m_listeners{};

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

        void initalize();

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
        [[nodiscard]] bool
        hasAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType);

        // get Attribute
        template<class T>
        [[nodiscard]] std::shared_ptr<T>
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

        [[nodiscard]] bool hasSystem(const unsigned int &l_systemID);

        template<class T>
        [[nodiscard]] std::shared_ptr<T> getSystem(const unsigned int &l_systemID)
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
        [[nodiscard]] bool hasState(const unsigned int &l_stateType);

        // register resource
        [[nodiscard]] unsigned int registerResource(
            const unsigned int &l_resourceType,
            const std::optional<std::string> &l_filename = std::nullopt
        );

        [[nodiscard]] bool hasResource(const unsigned int &l_resourceID);

        // load resource
        template<class T>
        [[nodiscard]] std::shared_ptr<T> loadResource(const unsigned int &l_resourceID)
        {
            ATMA_ENGINE_TRACE("trying to load resource with id {}", l_resourceID);
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

                if(auto loadeditr = m_loadedResources.find(l_resourceID);
                   loadeditr == m_loadedResources.end())
                {
                    ATMA_ENGINE_TRACE(
                        "resource with id {} has not been loaded into memory so loading now", l_resourceID
                    );
                    if(auto &filename = itr->second.second; filename.has_value())
                    {
                        ATMA_ENGINE_TRACE(
                            "resource with id {0:d} has filename of {1}",
                            l_resourceID,
                            filename.value()
                        );
                        m_loadedResources[l_resourceID] =
                            std::shared_ptr<T>{new T{filename.value()}};
                    }
                    else
                    {
                        ATMA_ENGINE_TRACE(
                            "resource with id {0:d} has no filename; creating default resource",
                            l_resourceID
                        );
                        m_loadedResources[l_resourceID] = std::shared_ptr<T>{new T{}};
                    }
                    return std::static_pointer_cast<T>(m_loadedResources[l_resourceID]);
                }
                else
                {
                    ATMA_ENGINE_TRACE(
                        "resource with id {} already has been loaded, loading from cache", l_resourceID
                    );
                    return std::static_pointer_cast<T>(loadeditr->second);
                }
            }
        }

        [[nodiscard]] bool hasLoadedResource(const unsigned int &l_resourceID);

        // unload resource
        void unloadResource(const unsigned int &l_resourceID);

        // remove resource
        void removeResource(const unsigned int &l_resourceID);

        [[nodiscard]] unsigned int createWindow();

        [[nodiscard]] std::shared_ptr<Window> getWindow(const unsigned int &l_windowID);

        void pushWindowEvent(const WindowEvent &l_e);

        void deleteWindow(const unsigned int &l_windowID);

        void dispatchObjectEvent(const ObjectEventContext &l_e);

        void addObjectEventListener(
            const ObjectEventID &l_id,
            std::shared_ptr<ObjectEventListener> l_listener
        );

        void update();

        void purgeObjects();

        void purgeSystems();

        void purgeStates();

        void purgeResources();

        void purgeWindows();

        void purgeListeners();

        void purge();
    };

}