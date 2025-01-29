#include "pch.hpp"
#include "StateManager.hpp"

namespace ATMA
{

    StateManager::StateManager() {}

    StateManager::~StateManager() {}

    void StateManager::addState(const unsigned int &l_stateType, std::shared_ptr<BaseState> l_state)
    {
        ATMA_ENGINE_INFO("Registering State type: {0:d}", l_stateType);
        bool initState = m_states.empty();
        if(m_states.count(l_stateType) == 0)
        {
            m_states[l_stateType] = std::move(l_state);
            if(initState)
                switchToState(l_stateType);
        }
        else
            throw RegistrationException(
                "State of type:" + std::to_string(l_stateType) + " has already been registered to the context"
            );
        ATMA_ENGINE_INFO("Registered State type: {0:d}", l_stateType);
    }

    void StateManager::removeState(const unsigned int &l_stateType)
    {
        auto itr = m_states.find(l_stateType);
        if(itr == m_states.end())
        {
            throw ValueNotFoundException(
                "State of type: " + std::to_string(l_stateType) + " has not been registered to the context"
            );
        }
        else
        {
            m_states.erase(itr);
            ATMA_ENGINE_INFO("Removed State type: {0:d}", l_stateType);
        }
    }

    void StateManager::switchToState(const unsigned int &l_stateType)
    {
        if(m_states.count(l_stateType) == 0)
        {
            throw ValueNotFoundException(
                "State of type: " + std::to_string(l_stateType) + " has not been registered to the context"
            );
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

    bool StateManager::hasState(const unsigned int &l_stateType)
    {
        return m_states.count(l_stateType) > 0;
    }

    void StateManager::dispatchWindowEvent(const WindowEvent &l_winEvent)
    {
        auto itr = m_states.begin();
        if(itr == m_states.end())
        {
            return;
        }
        while(itr != m_states.end())
        {
            itr->second->handleInput(l_winEvent);
            ++itr;
        }
    }

    void StateManager::purge()
    {
        m_states.clear();
        m_currentStateID = 0;
        ATMA_ENGINE_INFO("purged states from context");
    }
}
