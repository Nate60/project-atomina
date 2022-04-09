#pragma once
#include "pch.h"
#include "api.h"
#include "State.h"
#include "Binding.h"
#include "Event.h"
#include "StateSensitive.h"
#include "AtominaException.h"
#include "Log.h"

namespace ATMA {
	
	using Bindings = std::unordered_map<std::string, std::shared_ptr<Binding>>;
	using CallbackContainer = std::unordered_map <EventType, std::function<void (Event&)>>;
	using StateType = unsigned int;
	using Callbacks = std::unordered_map<StateType, CallbackContainer>;


	class ATMA_API EventManager: public StateSensitive {
	public: 

		EventManager();

		~EventManager();

		bool addBinding(const std::string &l_name, std::shared_ptr<Binding> l_binding);

		bool removeBinding(const std::string &l_name);

		bool addCallBack(const EventType &l_event_type, std::function<void(Event &)> l_func, const StateType &l_type = 0u);

		bool removeCallBack(const EventType &l_event_type, const StateType &l_type = 0u);

		virtual void onStateCreate(const StateType &l_type) override;

		virtual void onStateChange(const StateType &l_type) override;

		virtual void onStateRemove(const StateType &l_type) override;

		void handleEvent(Event &e);

		void update();

	private:

		 Bindings m_bindings;
		 Callbacks m_callbacks;

	};

}