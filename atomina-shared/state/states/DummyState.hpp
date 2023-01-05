#pragma once
#include "core/api.hpp"
#include "state/BaseState.hpp"

namespace ATMA
{
    /**
     * Dummy state used as a place holder  
     */
    class ATMA_API DummyState: public BaseState
    {
    public:
    
        //default constructor
        DummyState();

        //deconstructor
        virtual ~DummyState();

        /**
         * stub function for creation of state
         */
        virtual void onCreate() override;

        /**
         * stub function for deletion of state 
         */
        virtual void onDestroy() override;

        /**
         * stub function for activation of state 
         */
        virtual void activate() override;

        /**
         * stub function for deactivation of state 
         */
        virtual void deactivate() override;

        /**
         * gives type id of dummy state
         * @return type id of dummy state 
         */
        virtual unsigned int getId() const override
        {
            return StateType(State::Dummy);
        }

        /**
         * stub update function
         * @param l_time time passed since last update 
         */
        virtual void update(const sf::Time &l_time) override;
        
        /**
         * stub draw function 
         */
        virtual void draw() override;
    };
}