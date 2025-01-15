#include "event/ObjectEventContext.hpp"
#include "pch.hpp"
#include "SysBase.hpp"

namespace ATMA
{

    bool SysBase::addObject(const ObjectId &l_id, const unsigned int &l_patternID)
    {
        if(hasObject(l_id) >= 0)
        {
            ATMA_ENGINE_WARN("Unable to add object id: {0:d} as it already exists in system: {1:d} ", l_id, getType());
            return false;
        }
        m_objects.push_back(std::make_pair(l_patternID, l_id));
        ATMA_ENGINE_INFO("Added object id: {0:d} to system: {1} ", l_id, shared_from_this());
        return true;
    }

    int SysBase::hasObject(const ObjectId &l_id) const
    {
        for(auto itr = m_objects.begin(); itr != m_objects.end(); itr++)
        {
            if(itr->second == l_id)
            {
                return (int)itr->first;
            }
        }
        return -1;
    }

    bool SysBase::removeObject(const ObjectId &l_id)
    {
        for(auto itr = m_objects.begin(); itr != m_objects.end(); itr++)
        {
            if(itr->second == l_id)
            {
                m_objects.erase(itr);
                ATMA_ENGINE_INFO("Removed object id: {0:d} from system: {1} ", l_id, shared_from_this());
                return true;
            }
        }
        ATMA_ENGINE_WARN("Unable to remove object id: {0:d} in system: {1:d} as it does not exist", l_id, getType());
        return false;
    }

    SystemType SysBase::getType() const
    {
        return m_type;
    }

    const int SysBase::match(const std::bitset<ATConst::OBJECT_BIT_SIZE> &l_bits) const
    {
        for(auto itr = m_req.begin(); itr != m_req.end(); itr++)
        {
            if((~(*itr) | l_bits).all())
            {
                return itr - m_req.begin();
            }
        }
        return -1;
    }

    void SysBase::purge()
    {
        ATMA_ENGINE_INFO("Cleared all objects from system: {0:d} ", getType());
        m_objects.clear();
    }

}