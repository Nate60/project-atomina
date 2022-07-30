#pragma once
#include "../AtominaTest.hpp"
#include "StateFixtures.hpp"

class TestState : public ATMA::BaseState
{
public:

	bool failOnCallback{false};

	ATMA::ATMAContext &ctx = ATMA::ATMAContext::getContext();

		TestState();


		virtual ~TestState();

		virtual void onCreate() override;
		virtual void onDestroy() override;
		virtual void activate() override;
		virtual void deactivate() override;

		virtual unsigned int getId() const override
		{
			return 3u;
		}


		virtual void update(const sf::Time& l_time) override;
		virtual void draw() override;

};