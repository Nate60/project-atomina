#pragma once

#include "pch.hpp"
#include "core/api.hpp"
#include "State.hpp"
#include "util/Log.hpp"

namespace ATMA
{

    class StateManager;

    /**
     * Basic State that defines all functions of a state to be inherited
     * All states should extend this class
     */
    class ATMA_API BaseState
    {
    public:
        // default constructor
        BaseState();

        // move constructor
        BaseState(BaseState &&b) noexcept;

        // destructor
        virtual ~BaseState();

        /**
         * function called by context on creation of state
         */
        virtual void onCreate() = 0;

        /**
         * function called by context before deletion of the state
         */
        virtual void onDestroy() = 0;

        /**
         * function called by context when activating state
         */
        virtual void activate();

        /**
         * function called by context when deactivating state
         */
        virtual void deactivate();

        /**
         * checks if state is active
         * @returns if the state is active or not
         */
        virtual bool isActive() const
        {
            return m_active;
        }

        /**
         * gives the type id of the state
         * each state should give a different type id
         * @returns type id of the state
         */
        virtual unsigned int getId() const
        {
            return StateType(State::Empty);
        }

        // equality operator
        bool operator==(const BaseState &b) const;

        // less than operator
        bool operator<(const BaseState &b) const;

        // greate than operator
        bool operator>(const BaseState &b) const;
    protected:
        bool m_active;
        bool m_transparent;
        bool m_transcendent;
        bool m_communicable;
    };

}
