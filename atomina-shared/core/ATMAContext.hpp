#pragma once
#include "pch.hpp"
#include "api.hpp"
#include "event/ObjectEvent.hpp"
#include "event/ObjectEventListener.hpp"
#include "util/ATConst.hpp"
#include "OAS/AttrBase.hpp"
#include "OAS/SysBase.hpp"
#include "state/BaseState.hpp"
#include "util/Log.hpp"
#include "util/AtominaException.hpp"
#include "util/ATConst.hpp"
#include "resource/Resource.hpp"
#include "GUI/Window.hpp"
#include "GUI/window/WindowGLFWImpl.hpp"
#ifdef _WINDOWS
#    include <winsock2.h>
#    include <ws2tcpip.h>
#    include <iphlpapi.h>
#    include <stdio.h>
#endif

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

    using ResourceContainer = std::unordered_map<
        ResourceID,
        std::tuple<ResourceTypeID, std::string, std::optional<std::string>>>;
    using LoadedResourceContainer = std::unordered_map<ResourceID, std::shared_ptr<Resource>>;

    using ObjectEventID = unsigned int;
    using ObjectEventListeners =
        std::unordered_map<ObjectEventID, std::vector<std::shared_ptr<ObjectEventListener>>>;

    using WindowID = unsigned int;
    using WindowContainer = std::unordered_map<WindowID, std::shared_ptr<Window>>;

    /**
     * Singleton that houses all internal state within the Atomina Engine.
     * Manages all resources and objects available to the engine.
     */
    class ATMA_API ATMAContext
    {
    public:
        // destructor
        ~ATMAContext();
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

        ObjectEventListeners m_listeners{};

        WindowID m_lastWindowID{1u};
        WindowContainer m_windows{};

        std::shared_ptr<RenderContext> m_renderer;

        /**
         * protected constructor that should only be called
         * by the get context function to maintain a singleton
         * pattern
         */
        ATMAContext();

        /**
         * Called when an object has had an attribute added or removed
         * and will let any relevant systems know.
         * @param l_objectID object id of the object that was changed
         * @param l_bits the bit set of the object describing which attributes it has
         */
        void objectUpdated(
            const unsigned int &l_objectID,
            const std::bitset<ATConst::OBJECT_BIT_SIZE> &l_bits
        );

        /**
         * Called when a system has been removed or added to the context and
         * will notify the system of any potential relevant objects
         * @param l_systemID id of the system that has changed
         */
        void systemUpdated(const unsigned int &l_systemID);
    public:
        // deleted functions
        ATMAContext(ATMAContext const &) = delete;
        void operator=(ATMAContext const &) = delete;

        /**
         * Global function to obtain a reference to the global Atomina
         * context
         * @returns reference to global Atomina context
         */
        static ATMAContext &getContext()
        {
            static ATMAContext context; // Guaranteed to be destroyed.
                                        // Instantiated on first use.
            return context;
        }

        /**
         * Assigns an Attribute class type to an unsigned integer id
         * @tparam class type to assign id to
         * @param l_attrType id to assign class type to
         * @throws RegistrationException if the id has a type already assigned
         */
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

        /**
         * allocates an unique id for a new object but does not assign any attributes to
         * it
         * @returns id of the new object
         */
        [[nodiscard]] unsigned int createObject();

        /**
         * allocates an unique id for a new object and creates the corresponding attributes listing
         * in the given bit set
         * @param l_bits
         * @returns id of the new object
         */
        [[nodiscard]] unsigned int createObject(const std::bitset<ATConst::OBJECT_BIT_SIZE> &l_bits
        );

        /**
         * Adds an attribute of the given id type to the given id
         * @param l_objectID object id to add attribute to
         * @param l_attrType id type of the attribute
         * @throws ValueNotFound Exception if either the object id or attribute type is not
         * registered to the context
         */
        void addAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType);

        /**
         * Removes an attribute of the given type from the specified object
         * @param l_objectID object id to remove the attribute from
         * @param l_attrType type id of the attribute to remove
         * @throws ValueNotFound Exception if either the object id or attribute type is not
         * registered to the context or if the object does not have the attribute
         */
        void removeAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType);

        /**
         * checks if the object id has the given attribute
         * @param l_objectID id of the object to check
         * @param l_attrType type id to check for
         * @returns if the attribute was found or not
         */
        [[nodiscard]] bool
        hasAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType);

        /**
         * gets a pointer to the specified attribute from the given object
         * @tparam type class of the attribute
         * @param l_objectID id of the object to get attribute from
         * @param l_attrType type id of the attribute to grab
         * @returns pointer to the attribute
         * @throws ValueNotFound Exception if object or attribute cannot be found in the context
         */
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

        /**
         * Registers a system type to the context and associates it with the given class type
         * @tparam Class Type of the system
         * @param l_systemID type id of the system to register
         * @throws Registration Exception if the type id already has an existing system class
         * registered
         */
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
                throw ValueNotFoundException(
                    "system id: " + std::to_string(l_systemID) + " does not exist"
                );
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
         * Add state to the context as the owner
         * @param l_stateType type id of the state to be associated with the state
         * @param l_state unique pointer to the state
         * @throws Registration Exception if the state id has a state already registered
         */
        void addState(const unsigned int &l_stateType, std::unique_ptr<BaseState> l_state);

        /**
         * Remove state from the context
         * @param l_stateType type id of the state to remove
         * @throws ValueNotFound Exception if the state type id has not state register
         */
        void removeState(const unsigned int &l_stateType);

        /**
         * switches the state associated with the given type id to the active state
         * @param l_stateType state type id of the state to switch to
         * @throws ValueNotFound Exception when the state type id is not registered
         */
        void switchToState(const unsigned int &l_stateType);

        /**
         * checks if the state is registered in the context
         * @param l_stateType the type id to check for
         * @returns if the state type id has been registered
         */
        [[nodiscard]] bool hasState(const unsigned int &l_stateType);

        /**
         * registers a resource to the context and assigns it an id
         * @param l_name name of the resource
         * @param l_resourceType type id of the resource
         * @param l_filename full qualified path to the resource
         * @returns id of the registered resource
         */
        [[nodiscard]] unsigned int registerResource(
            const std::string &l_name,
            const unsigned int &l_resourceType,
            const std::optional<std::string> &l_filename = std::nullopt
        );

        /**
         * checks if the resource has been registered
         * @param l_resourceID id of the resource to check for
         * @returns if the resource has been found
         */
        [[nodiscard]] bool hasResource(const unsigned int &l_resourceID);

        /**
         * loads the resource into memory from its source and gives a pointer
         * to the loaded resource
         * @tparam type class of the resource
         * @param l_resourceID id of the registered resource
         * @returns pointer to the resource loaded in memory
         * @throws ValueNotFound Exception if the id is not registered in the context
         */
        template<class T>
        [[nodiscard]] std::shared_ptr<T> loadResource(const unsigned int &l_resourceID)
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

                if(auto loadeditr = m_loadedResources.find(l_resourceID);
                   loadeditr == m_loadedResources.end())
                {
                    auto &name = std::get<1>(itr->second);
                    if(auto &filename = std::get<2>(itr->second); filename.has_value())
                    {

                        m_loadedResources[l_resourceID] = std::shared_ptr<T>{
                            new T{name, filename.value()}
                        };
                    }
                    else
                    {
                        m_loadedResources[l_resourceID] = std::shared_ptr<T>{new T{name}};
                    }
                    return std::static_pointer_cast<T>(m_loadedResources[l_resourceID]);
                }
                else
                {
                    return std::static_pointer_cast<T>(loadeditr->second);
                }
            }
        }

        /**
         * checks if the resource id has been loaded into memory
         * @param l_resourceID id of the resource
         * @returns if the loaded resource is found
         */
        [[nodiscard]] bool hasLoadedResource(const unsigned int &l_resourceID);

        /**
         * removes the loaded resource from the context so it can no new pointers can be grabbed
         * from the context
         * @param l_resourceID id of the loaded resource
         * @throws ValueNotFound Exception if the id has no loaded resource
         */
        void unloadResource(const unsigned int &l_resourceID);

        /**
         * removes the registered resource from the context so it cannot longer be loaded
         * @param l_resourceID id of the registered resource
         * @throws ValueNotFound Exception if the id has no registered resource
         */
        void removeResource(const unsigned int &l_resourceID);

        /**
         * pushes object event to all registered object event listeners
         * for that object event type
         * @param l_e object event details
         */
        void dispatchObjectEvent(const ObjectEventContext &l_e);

        /**
         * Adds object event listener to the notification interface
         * of the context
         * @param l_id type id of the object event that the listener is listening for
         * @param l_listener pointer to the listener
         */
        void addObjectEventListener(
            const ObjectEventID &l_id,
            std::shared_ptr<ObjectEventListener> l_listener
        );
        /**
         * @brief creates a window inside the context and assigns it an id
         * @return the id of the new window
         */
        unsigned int createWindow();

        /**
         * @brief gives a pointer to the corresponding id
         * @param l_id id of the window
         * @return pointer of the window
         */
        std::shared_ptr<Window> getWindow(const unsigned int &l_id);

        /**
         * @brief deletes the window of corresponding id
         * @param l_id id of the window
         */
        void deleteWindow(const unsigned int &l_id);

        std::shared_ptr<RenderContext> getRenderer();

        /**
         * updates all the engine internals. To be called in the main game loop
         */
        void update();

        /**
         * removes all objects and attributes and resets the next id back to 0
         */
        void purgeObjects();

        /**
         * removes all systems and resets the next id back to 0
         */
        void purgeSystems();

        /**
         * removes and deletes all states from the context
         */
        void purgeStates();

        /**
         * removes and unloads all resources from the context and resets the next id
         * back to 0
         */
        void purgeResources();

        /**
         * removes all windows from the context and resets the next id
         * back to 0
         */
        void purgeWindows();

        /**
         * unregisters all listeners from the context
         */
        void purgeListeners();

        /**
         * purges all memory items from the context and resets all next ids for each
         * registry back to 0
         */
        void purge();
    };

}