#pragma once
#include "core/api.hpp"
#include "state/BaseState.hpp"

namespace ATMA
{
    class ATMA_API DummyState: public BaseState
    {
    public:
        DummyState();

        virtual ~DummyState();

        virtual void onCreate() override;
        virtual void onDestroy() override;
        virtual void activate() override;
        virtual void deactivate() override;

        virtual unsigned int getId() const override
        {
            return StateType(State::Dummy);
        }

        virtual void update(const sf::Time &l_time) override;
        virtual void draw() override;
    };
}