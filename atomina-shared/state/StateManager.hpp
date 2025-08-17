#pragma once
#include "pch.hpp"
#include "BaseState.hpp"
#include "util/Log.hpp"

namespace ATMA
{

    using StateTypeID = unsigned int;
    using StateStack = std::unordered_map<StateTypeID, std::shared_ptr<BaseState>>;

    class StateManager
    {
    public:
        StateManager();

        virtual ~StateManager();

        /**
         * Add state to the context as the owner
         * @param l_stateType type id of the state to be associated with the state
         * @param l_state unique pointer to the state
         * @throws Registration Exception if the state id has a state already registered
         */
        void addState(ATMAContext *l_ctx, const unsigned int &l_stateType, std::shared_ptr<BaseState> l_state);

        /**
         * Remove state from the context
         * @param l_stateType type id of the state to remove
         * @throws ValueNotFound Exception if the state type id has not state register
         */
        void removeState(const unsigned int &l_stateType);

        /**
         * switches the state associated with the given type id to the active state
         * @param l_stateType state type id of the state to switch to
         * @throws ValueNotFound Exception when the state type id is not registered
         */
        void switchToState(ATMAContext *l_ctx, const unsigned int &l_stateType);

        /**
         * checks if the state is registered in the context
         * @param l_stateType the type id to check for
         * @returns if the state type id has been registered
         */
        [[nodiscard]] bool hasState(const unsigned int &l_stateType);

        /**
         * Pushes event to the state stack until it is handled
         * @param l_ctx Engine Context
         * @param l_winEvent window event
         */
        void dispatchWindowEvent(ATMAContext *l_ctx, const WindowEvent &l_winEvent);

        /**
         * removes and deletes all states from the context
         */
        void purge();
    protected:
        StateTypeID m_currentStateID{};
        StateStack m_states{};
    };

}
