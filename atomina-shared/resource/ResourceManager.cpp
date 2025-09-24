#include "pch.hpp"
#include "ResourceManager.hpp"

namespace ATMA
{

    ResourceManager::ResourceManager() {}

    ResourceManager::~ResourceManager() {}

    unsigned int ResourceManager::registerResource(
        const std::string &l_name,
        const unsigned int &l_resourceType,
        const std::optional<std::string> &l_filename
    )
    {
        auto id = m_lastResourceId++;
        m_resources[id] = std::make_tuple(l_resourceType, l_name, l_filename);
        if(m_aliasMap.contains(l_name))
        {
            throw RegistrationException("Resource alias: " + l_name + " already has been registered to the context");
        }
        m_aliasMap[l_name] = id;
        ATMA_ENGINE_INFO("registered resource {0} with id {1:d}", l_name, l_resourceType);
        return id;
    }

    bool ResourceManager::hasResource(const unsigned int &l_resourceID)
    {
        return m_resources.count(l_resourceID) > 0;
    }

    void ResourceManager::unloadResource(const unsigned int &l_resourceID)
    {
        auto itr = m_loadedResources.find(l_resourceID);
        if(itr == m_loadedResources.end())
        {
            throw ValueNotFoundException(
                "Resource of id: " + std::to_string(l_resourceID) + " has not been loaded to the context"
            );
        }
        else
        {
            m_loadedResources.erase(itr);
            ATMA_ENGINE_INFO("Unloaded Resource id: {0:d}", l_resourceID);
        }
    }

    bool ResourceManager::hasLoadedResource(const unsigned int &l_resourceID)
    {
        return m_loadedResources.count(l_resourceID) > 0;
    }

    void ResourceManager::removeResource(const unsigned int &l_resourceID)
    {
        auto itr = m_resources.find(l_resourceID);
        if(itr == m_resources.end())
        {
            throw ValueNotFoundException(
                "Resource of id: " + std::to_string(l_resourceID) + " has not been registered to the context"
            );
        }
        else
        {
            try
            {
                unloadResource(l_resourceID);
            }
            catch(ValueNotFoundException const &e)
            {
                ATMA_ENGINE_INFO("Resource being removed: {0}", e.what());
            }
            m_resources.erase(itr);
            ATMA_ENGINE_INFO("removed Resource id: {0:d}", l_resourceID);
        }
    }

    void ResourceManager::purge()
    {
        m_resources.clear();
        m_loadedResources.clear();
        m_lastResourceId = 0;
        ATMA_ENGINE_INFO("purged resources from context");
    }

}
