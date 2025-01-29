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

        // destructor
        ~ATMAContext();
    protected:
        /**
         * protected constructor that should only be called
         * by the get context function to maintain a singleton
         * pattern
         */
        ATMAContext();
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

        void purge();
    };

}
