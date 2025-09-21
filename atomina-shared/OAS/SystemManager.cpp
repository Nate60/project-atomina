#include "core/ATMAContext.hpp"
#include "pch.hpp"
#include "SystemManager.hpp"
#include "AttributeManager.hpp"
#include "util/ATConst.hpp"
#include "util/AtominaException.hpp"

namespace ATMA
{

    SystemManager::SystemManager() {}

    SystemManager::~SystemManager() {}

    void SystemManager::objectUpdated(const unsigned int &l_objectID, const std::bitset<ATConst::BITSET_SIZE> &l_bits)
    {
        for(auto &system: m_systems)
        {
            int patternID = system.second->match(l_bits);
            bool hasObj = system.second->hasObject(l_objectID) != -1;
            if(patternID >= 0 && !hasObj)
            {
                system.second->addObject(l_objectID, patternID);
            }
            else if(patternID < 0 && hasObj)
            {
                system.second->removeObject(l_objectID);
            }
        }
    }

    void SystemManager::systemUpdated(ATMAContext *l_ctx, const unsigned int &l_systemID)
    {
        for(auto &obj: l_ctx->m_attrMan->m_objects)
        {
            if(auto patternID = m_systems[l_systemID]->match(obj.second.first); patternID >= 0)
            {
                m_systems[l_systemID]->addObject(obj.first, patternID);
            }
        }
    }

    void SystemManager::enableSystem(const unsigned int &l_systemID)
    {
        if(m_systems.count(l_systemID) == 0)
            throw ValueNotFoundException(
                "System type: " + std::to_string(l_systemID) + " has not been registered in ATMA Context"
            );
        m_systems[l_systemID]->m_enabled = true;
        ATMA_ENGINE_INFO("Enabled system type: {0:d}", l_systemID);
    }

    void SystemManager::disableSystem(const unsigned int &l_systemID)
    {
        if(m_systems.count(l_systemID) == 0)
            throw ValueNotFoundException(
                "System type: " + std::to_string(l_systemID) + " has not been registered in ATMA Context"
            );
        m_systems[l_systemID]->m_enabled = false;
        ATMA_ENGINE_INFO("Disabled system type: {0:d}", l_systemID);
    }

    bool SystemManager::hasSystem(const unsigned int &l_systemID)
    {
        return m_systems.count(l_systemID) > 0;
    }

    void SystemManager::removeSystem(const unsigned int &l_systemID)
    {
        auto itr = m_systems.find(l_systemID);
        if(itr == m_systems.end())
        {
            throw ValueNotFoundException(
                "System type: " + std::to_string(l_systemID) + " does not exist in ATMA context"
            );
        }
        else
        {
            ATMA_ENGINE_INFO("Removed System type: {0:d}", itr->second->getType());
            m_systems.erase(itr);
        }
    }

    void SystemManager::purge()
    {
        m_systems.clear();
        ATMA_ENGINE_INFO("purged systems from context");
    }

    void SystemManager::purgeSystem(const unsigned int &l_systemID)
    {
        if(auto itr = m_systems.find(l_systemID); itr != m_systems.end())
        {
            ATMA_ENGINE_INFO("Purged System type: {0:d}", itr->second->getType());
            itr->second->purge();
        }
        else
        {
            throw ValueNotFoundException("System type: " + std::to_string(l_systemID) + " does not exist");
        }
    }

    void SystemManager::update(ATMAContext *l_ctx, const double &l_dt)
    {
        for(auto &sys: m_systems)
        {
            if(sys.second->m_enabled)
                sys.second->update(l_ctx, l_dt);
        }
    }

}
