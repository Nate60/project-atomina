#include "pch.hpp"
#include "core/ATMAContext.hpp"
#include "AttributeManager.hpp"
#include "SystemManager.hpp"

namespace ATMA
{

    AttributeManager::AttributeManager() {}

    AttributeManager::~AttributeManager() {}

    unsigned int AttributeManager::createObject(ATMAContext &l_ctx)
    {
        std::lock_guard<std::mutex> lock{m_mtx};
        auto id = m_lastObjectID++;
        ATMA_ENGINE_INFO("Created Object ID {0:d}", id);
        return id;
    }

    unsigned int AttributeManager::createObject(ATMAContext &l_ctx, const std::bitset<ATConst::OBJECT_BIT_SIZE> &l_bits)
    {
        std::lock_guard<std::mutex> lock{m_mtx};
        auto id = m_lastObjectID++;
        ATMA_ENGINE_INFO("Created Object ID {0:d}", id);
        for(unsigned int i = 0; i < ATConst::OBJECT_BIT_SIZE; i++)
        {
            if(!l_bits.test(i))
                continue;
            addAttribute(l_ctx, id, i);
        }
        l_ctx.m_sysMan->objectUpdated(id, l_bits);
        return id;
    }

    void
    AttributeManager::addAttribute(ATMAContext &l_ctx, const unsigned int &l_objectID, const unsigned int &l_attrType)
    {
        if(l_objectID >= m_lastObjectID)
            throw ValueNotFoundException("Object id: " + std::to_string(l_objectID) + " was not found");

        auto attrItr = m_attrFactory.find(l_attrType);
        if(attrItr == m_attrFactory.end())
            throw ValueNotFoundException(
                "Attribute type: " + std::to_string(l_attrType) + " has not been registered in factory"
            );

        auto itr = m_objects.find(l_objectID);
        if(itr == m_objects.end())
        {
            // create new attribute container
            std::bitset<ATConst::OBJECT_BIT_SIZE> bits{};
            bits.set(l_attrType);
            std::shared_ptr<AttrBase> attr = m_attrFactory[l_attrType]();
            std::unordered_map<AttrTypeID, std::shared_ptr<AttrBase>> attrMap{};
            attrMap[l_attrType] = attr;
            std::pair<std::bitset<ATConst::OBJECT_BIT_SIZE>, std::unordered_map<AttrTypeID, std::shared_ptr<AttrBase>>>
                pair{bits, attrMap};
            ObjectAttributes attrs{pair};
            m_objects[l_objectID] = attrs;
            ATMA_ENGINE_INFO("Added attribute type {0:d} to object id {1:d}", l_attrType, l_objectID);
            l_ctx.m_sysMan->objectUpdated(l_objectID, bits);
        }
        else
        {
            // update attribute container
            itr->second.first.set(l_attrType);
            itr->second.second[l_attrType] = m_attrFactory[l_attrType]();
            ATMA_ENGINE_INFO("Added attribute type {0:d} to object id {1:d}", l_attrType, l_objectID);
            l_ctx.m_sysMan->objectUpdated(l_objectID, itr->second.first);
        }
    }

    void AttributeManager::removeAttribute(
        ATMAContext &l_ctx,
        const unsigned int &l_objectID,
        const unsigned int &l_attrType
    )
    {
        auto itr = m_objects.find(l_objectID);
        if(itr == m_objects.end())
        {
            throw ValueNotFoundException(
                "object id: " + std::to_string(l_objectID) + " does not contain any attributes or does not exist"
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
                itr->second.first.reset(innerItr->first);
                itr->second.second.erase(innerItr);
                ATMA_ENGINE_INFO("Removed attribute type {0:d} to object id {1:d}", l_attrType, l_objectID);
                l_ctx.m_sysMan->objectUpdated(l_objectID, itr->second.first);
            }
        }
    }

    bool AttributeManager::hasAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType)
    {
        auto itr = m_objects.find(l_objectID);
        if(itr == m_objects.end())
        {
            return false;
        }
        else
        {
            return itr->second.first.test(l_attrType);
        }
    }

    void AttributeManager::purge(ATMAContext &l_ctx)
    {
        m_objects.clear();
        m_attrFactory.clear();
        std::bitset<ATConst::OBJECT_BIT_SIZE> emptybits{};
        for(auto &system: l_ctx.m_sysMan->m_systems)
        {
            l_ctx.m_sysMan->purgeSystem(system.second->getType());
        }
        m_lastObjectID = 0;
        ATMA_ENGINE_INFO("purged objects from context");
    }
}
