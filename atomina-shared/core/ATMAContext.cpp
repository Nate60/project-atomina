#include "../pch.hpp"
#include "ATMAContext.hpp"
#include <bitset>
#include <mutex>
#include <string>
#include <utility>

namespace ATMA{

    void ATMAContext::objectUpdated(const unsigned int &l_objectID, const std::bitset<ATConst::OBJECT_BIT_SIZE> &l_bits)
    {
        for(auto &system: m_systems)
        {
            if(system.second->match(l_bits) && !system.second->hasObject(l_objectID))
            {
                system.second->addObject(l_objectID);
            }
            else if(!system.second->match(l_bits) && system.second->hasObject(l_objectID) )
            {
                system.second->removeObject(l_objectID);
            }
        }
    
    }

    void ATMAContext::addCallback(const unsigned int &l_eventType, const unsigned int &l_stateType, CallBackFunction l_func)
    {
        CallBackKey pair{l_eventType,l_stateType};
        m_callbacks[pair] = l_func;
        ATMA_ENGINE_INFO("Registered Callback for event type {0:d} and state type {1:d}", l_eventType, l_stateType);
    }

    void ATMAContext::removeCallback(const unsigned int &l_eventType, const unsigned int &l_stateType)
    {
        CallBackKey pair{l_eventType,l_stateType};
        auto itr = m_callbacks.find(pair);
        if(itr != m_callbacks.end())
        {
            m_callbacks.erase(itr);
            ATMA_ENGINE_INFO("Removed Callback for event type {0:d} and state type {1:d}", l_eventType, l_stateType);
        }
    }

    void ATMAContext::addEvent(const unsigned int &l_eventType, const unsigned int &l_stateType, EventContext &&l_context)
    {
        std::tuple<EventTypeID,StateTypeID,EventContext> tuple{l_eventType,l_stateType,std::move(l_context)};
        m_eventQueue.emplace_back(tuple);
    }

    unsigned int ATMAContext::createObject()
    {
        std::lock_guard<std::mutex>lock{m_mtx};
        auto id = m_lastId++;
        ATMA_ENGINE_INFO("Created Object ID {0:d}", id);
        return id;
    }

    unsigned int ATMAContext::createObject(const std::bitset<ATConst::OBJECT_BIT_SIZE> &l_bits)
    {
        std::lock_guard<std::mutex>lock{m_mtx};
        auto id = m_lastId++;
        ATMA_ENGINE_INFO("Created Object ID {0:d}", id);
        for(unsigned int i = 0; i < ATConst::OBJECT_BIT_SIZE; i++)
        {
            if(!l_bits.test(i))
                continue;
            addAttribute(id,i);
        }
        objectUpdated(id,l_bits);
        return id;
    }

    void ATMAContext::addAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType)
    {
        if(l_objectID >= m_lastId)
            throw ValueNotFoundException("Object id: " + std::to_string(l_objectID) + " was not found");

        auto attrItr = m_attrFactory.find(l_attrType);
        if(attrItr == m_attrFactory.end())
            throw ValueNotFoundException("Attribute type: " + std::to_string(l_attrType) + " has not been registered in factory");
            
        auto itr = m_objects.find(l_objectID);
        if(itr == m_objects.end())
        {
            //create new attribute container
            std::bitset<ATConst::OBJECT_BIT_SIZE> bits{};
            bits.set(l_attrType);
            std::shared_ptr<AttrBase> attr = m_attrFactory[l_attrType]();
            std::unordered_map<AttrTypeID, std::shared_ptr<AttrBase>> attrMap{};
            attrMap[l_attrType] = attr;
            std::pair<std::bitset<ATConst::OBJECT_BIT_SIZE>,std::unordered_map<AttrTypeID, std::shared_ptr<AttrBase>>> pair{bits, attrMap};
            ObjectAttributes attrs{pair};
            m_objects[l_objectID] = attrs;
            ATMA_ENGINE_INFO("Added attribute type {0:d} to object id {1:d}", l_attrType, l_objectID);
            objectUpdated(l_objectID, bits);
        }
        else{
            //update attribute container
            itr->second.first.set(l_attrType);
            itr->second.second[l_attrType] = m_attrFactory[l_attrType]();
            ATMA_ENGINE_INFO("Added attribute type {0:d} to object id {1:d}", l_attrType, l_objectID);
            objectUpdated(l_objectID, itr->second.first);
        }
    }

    void ATMAContext::removeAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType)
    {
        auto itr = m_objects.find(l_objectID);
        if(itr == m_objects.end())
        {
            throw ValueNotFoundException("object id: " + std::to_string(l_objectID) + " does not contain any attributes or does not exist");
        }
        else
        {
            auto innerItr = itr->second.second.find(l_attrType);
            if(innerItr == itr->second.second.end())
            {
                  throw ValueNotFoundException("object id: " + std::to_string(l_objectID) + " does not contain attribute type: " + std::to_string(l_attrType));
            }
            else
            {
                itr->second.first.reset(innerItr->first);
                itr->second.second.erase(innerItr);
                ATMA_ENGINE_INFO("Removed attribute type {0:d} to object id {1:d}", l_attrType, l_objectID);
                objectUpdated(l_objectID,itr->second.first);
            }
        }
    }

    bool ATMAContext::hasAttribute(const unsigned int &l_objectID, const unsigned int &l_attrType)
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

    void ATMAContext::addSystem(const unsigned int &l_systemID, std::unique_ptr<SysBase> l_system)
    {
        if(m_systems.find(l_systemID) != m_systems.end())
            throw RegistrationException("System Type: " + std::to_string(l_systemID) + " already registered with ATMA Context");

        m_systems[l_systemID] = std::move(l_system);
        ATMA_ENGINE_INFO("Registered System type: {0:d}", l_systemID);
        for(auto &obj: m_objects)
        {
            if(m_systems[l_systemID]->match(obj.second.first)){
                m_systems[l_systemID]->addObject(obj.first);
            }
        }
    }

    void ATMAContext::enableSystem(const unsigned int &l_systemID)
    {
        if(m_systems.count(l_systemID) == 0)
            throw ValueNotFoundException("System type: " + std::to_string(l_systemID) + " has not been registered in ATMA Context");
        m_systems[l_systemID]->m_enabled = true;
        ATMA_ENGINE_INFO("Enabled system type: {0:d}", l_systemID);
    }

    void ATMAContext::disableSystem(const unsigned int &l_systemID)
    {
        if(m_systems.count(l_systemID) == 0)
            throw ValueNotFoundException("System type: " + std::to_string(l_systemID) + " has not been registered in ATMA Context");        
        m_systems[l_systemID]->m_enabled = false;
        ATMA_ENGINE_INFO("Disabled system type: {0:d}", l_systemID);
    }

    bool ATMAContext::hasSystem(const unsigned int &l_systemID)
    {
        return m_systems.count(l_systemID) > 0;
    }

    void ATMAContext::removeSystem(const unsigned int &l_systemID)
    {
        auto itr = m_systems.find(l_systemID);
        if(itr == m_systems.end())
        {
            throw ValueNotFoundException("System type: " + std::to_string(l_systemID) +  " does not exist in ATMA context");
        }
        else
        {
            ATMA_ENGINE_INFO("Removed System type: {0:d}", itr->second->getType());
            m_systems.erase(itr);
            
        }
    }

    void ATMAContext::addState(const unsigned int &l_stateType, std::unique_ptr<BaseState> l_state)
    {
        bool initState = m_states.empty();
        if(m_states.count(l_stateType) == 0){
             m_states[l_stateType] = std::move(l_state);
             if(initState)
                switchToState(l_stateType);
        }
        else
            throw RegistrationException("State of type:" + std::to_string(l_stateType) + " has already been registered to the context");
        ATMA_ENGINE_INFO("Registered State type: {0:d}", l_stateType);

    }

    void ATMAContext::removeState(const unsigned int &l_stateType)
    {
        auto itr = m_states.find(l_stateType);
        if(itr == m_states.end())
        {
            throw ValueNotFoundException("State of type: " + std::to_string(l_stateType) + " has not been registered to the context");
        }
        else
        {
            m_states.erase(itr);
            ATMA_ENGINE_INFO("Removed State type: {0:d}", l_stateType);
        }
    }

    void ATMAContext::switchToState(const unsigned int &l_stateType)
    {
        if(m_states.count(l_stateType) == 0)
        {
            throw ValueNotFoundException("State of type: " + std::to_string(l_stateType) + " has not been registered to the context");
        }
        if(m_states.count(m_currentStateID) != 0)
        {
             ATMA_ENGINE_INFO("Deactivating State: {0:d}", m_currentStateID); 
            m_states[m_currentStateID]->deactivate();
        }
        ATMA_ENGINE_INFO("Switching from state Type: {0:d} to state Type: {1:d}", m_currentStateID, l_stateType);   
        m_currentStateID = l_stateType;
        ATMA_ENGINE_INFO("Activating State: {0:d}", m_currentStateID); 
        m_states[m_currentStateID]->activate();
    }

    bool ATMAContext::hasState(const unsigned int &l_stateType)
    {
        return m_states.count(l_stateType) > 0;
    }


    void ATMAContext::update()
    {
        for(auto &e: m_eventQueue)
        {
            auto &[eType, sType, eCtx] = e;
            CallBackKey key{eType,sType};
            auto itr = m_callbacks.find(key);
            if(itr == m_callbacks.end()){
                ATMA_ENGINE_INFO("No matching Callback was found for eventType: {0:d} , StateType: {1:d} ", eType, sType);
                continue;
            }
            else
            {
                itr->second(eCtx);
                ATMA_ENGINE_INFO("Handled EventType {0:d} for StateType {1:d}", eType, sType);
            }
        }

        for(auto &sys: m_systems){
            if(sys.second->m_enabled)
                sys.second->update(0.0f);
        }

        for(auto &state: m_states)
        {
            state.second->update(sf::Time{});
        }
    }

    void ATMAContext::purgeObjects()
    {
        m_objects.clear();
        std::bitset<ATConst::OBJECT_BIT_SIZE> emptybits{};
        for(auto &system: m_systems)
        {
            system.second->purge();
        }
        m_lastId = 0;

    }

    void ATMAContext::purgeSystems()
    {
        m_systems.clear();
    }

    void ATMAContext::purgeStates()
    {
        m_states.clear();
        m_currentStateID = 0;
    }

    void ATMAContext::purgeEvents()
    {
        m_eventQueue.clear();
    }

    void ATMAContext::purgeResources()
    {
        m_resources.clear();
    }

	void ATMAContext::purge()
    {
        ATMA_ENGINE_INFO("Purging ATMA Context");
        m_objects.clear();
        m_attrFactory.clear();
        m_systems.clear();
        m_states.clear();
        m_eventQueue.clear();
        m_resources.clear();
        m_callbacks.clear();
        m_lastId = 0;
        m_currentStateID = 0;
    }

}