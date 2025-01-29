#include "pch.hpp"
#include "util/Log.hpp"
#include "ATMAContext.hpp"
#include "OAS/AttributeManager.hpp"
#include "OAS/SystemManager.hpp"
#include "event/ObjectEventManager.hpp"
#include "GUI/WindowManager.hpp"
#include "network/NetworkManager.hpp"
#include "resource/ResourceManager.hpp"
#include "state/StateManager.hpp"
#include "sound/AudioManager.hpp"
#include "render/GLRenderer.hpp"

namespace ATMA
{

    ATMAContext::ATMAContext()
    {
        ATMA_ENGINE_INFO("ATMAContext has been initialized");
    }

    ATMAContext::~ATMAContext()
    {
        ATMA_ENGINE_INFO("ATMAContext has been deleted");
    }

    void ATMAContext::purge()
    {
        m_sysMan->purge();
        m_stateMan->purge();
        m_resMan->purge();
        m_netMan->purgeConnections();
        m_netMan->purgeListeners();
        m_eventMan->purge();
        m_winMan->purge();
        m_audioMan->purge();
        m_attrMan->purge(*this);
    }
}
