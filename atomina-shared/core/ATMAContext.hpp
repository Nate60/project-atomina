#pragma once
#include "pch.hpp"

namespace ATMA
{

    class GLRenderer;
    class WindowManager;
    class NetworkManager;
    class ObjectEventManager;
    class AudioManager;
    class SystemManager;
    class AttributeManager;
    class ResourceManager;
    class StateManager;

    /**
     * Singleton that houses all internal state within the Atomina Engine.
     * Manages all resources and objects available to the engine.
     */
    class ATMAContext
    {
    public:
        GLRenderer *m_renderer = nullptr;
        WindowManager *m_winMan = nullptr;
        NetworkManager *m_netMan = nullptr;
        ObjectEventManager *m_eventMan = nullptr;
        AudioManager *m_audioMan = nullptr;
        SystemManager *m_sysMan = nullptr;
        AttributeManager *m_attrMan = nullptr;
        ResourceManager *m_resMan = nullptr;
        StateManager *m_stateMan = nullptr;
        int *argc = nullptr;
        char **argv = nullptr;

        const long long m_id;
        // destructor
        ~ATMAContext();
        // constructor
        ATMAContext();
    public:
        /**
         * helper function for purging all members
         */
        void purge();
    protected:
        inline static std::atomic<long long> m_lastId{0LL};
    };

}
