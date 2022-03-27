#pragma once
#include "pch.h"
#include "api.h"
#include "State.h"
#include "Binding.h"
#include "Event.h"
#include "StateSensitive.h"

namespace ATMA {
	
	using Bindings = std::unordered_map<std::string, std::shared_ptr<Binding>>;
	using CallbackContainer = std::unordered_map <EventType, std::function<void (Event&)>>;
	using StateType = unsigned int;
	using Callbacks = std::unordered_map<StateType, CallbackContainer>;


	class ATMA_API EventManager: public StateSensitive {
	public: 

		EventManager();

		//EventManager(EventManager &&other);

		~EventManager();

		bool addBinding(const std::string &l_name, std::shared_ptr<Binding> l_binding);

		bool removeBinding(std::string l_name);

		template<class T>
		bool addCallBack(const EventType& l_event_type, std::function<void(Event&)> l_func, const StateType& l_type = 0u)
		{
			if(l_type == 0u && m_currentState != 0 )
				return addCallBack<T>(l_event_type, l_func, m_currentState);
			if(m_callbacks.find(l_type) == m_callbacks.end())
			{
				m_callbacks[l_type] = std::move(CallbackContainer{{l_event_type, l_func}});
			}
			else if(m_callbacks[l_type].find(l_event_type) == m_callbacks[l_type].end())
			{
				m_callbacks[l_type][l_event_type] = l_func;
			}
			else
			{
				return false;
			}
			return true;

		}

		bool removeCallBack(const std::string& l_name, const StateType& l_type = 0u);

		virtual void onCreateState(const StateType &l_type) override;

		virtual void onStateChange(const StateType &l_type) override;

		virtual void onStateRemove(const StateType &l_type) override;

		void handleEvent(Event &e);

		void update();

		//TODO: Windows

	private:

		 Bindings m_bindings;
		 Callbacks m_callbacks;

	};

}