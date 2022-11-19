#include "event/ObjectEventContext.hpp"
#include "pch.hpp"
#include "SysBase.hpp"

namespace ATMA
{

    bool SysBase::addObject(const ObjectId &l_id)
    {
        if(std::count(m_objects.begin(), m_objects.end(), l_id))
        {
            ATMA_ENGINE_WARN(
                "Unable to add object id: {0:d} as it already exists in system: {1:d} ",
                l_id,
                getType()
            );
            return false;
        }
        m_objects.push_back(l_id);
        ATMA_ENGINE_INFO("Added object id: {0:d} to system: {1:d} ", l_id, getType());
        return true;
    }

    bool SysBase::hasObject(const ObjectId &l_id) const
    {
        if(std::count(m_objects.begin(), m_objects.end(), l_id))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool SysBase::removeObject(const ObjectId &l_id)
    {
        for(auto it = m_objects.begin(); it != m_objects.end(); it++)
        {
            if(*it == l_id)
            {
                m_objects.erase(it);
                ATMA_ENGINE_INFO("Removed object id: {0:d} from system: {1:d} ", l_id, getType());
                return true;
            }
        }
        ATMA_ENGINE_WARN(
            "Unable to remove object id: {0:d} in system: {1:d} as it does not exist",
            l_id,
            getType()
        );
        return false;
    }

    SystemType SysBase::getType() const
    {
        return m_type;
    }

    bool SysBase::match(const std::bitset<ATConst::OBJECT_BIT_SIZE> &l_bits) const
    {
        return (~m_req | l_bits).all();
    }

    void SysBase::purge()
    {
        ATMA_ENGINE_INFO("Cleared all objects from system: {0:d} ", getType());
        m_objects.clear();
    }

}