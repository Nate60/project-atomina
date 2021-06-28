#pragma once
#include "pch.h"
#include "api.h"
#include "EventGroup.h"

namespace ATMA {
	
	class ATMA_API EventManager {
	public: 

		EventManager();

		~EventManager();

		/*
		* Add collection of events to event manager to be matched against,
		* only returns true if successful
		*/
		bool addEventGroup(EventGroup l_group);

		/*
		* remove event group, only returns true if succesful
		*/
		bool removeGroup(EventGroup l_group);

		//TODO:States
		
		void handleEvent(sf::Event&);

		void update();

		//TODO: Windows

	private:

		std::unordered_map<std::string, EventGroup*> eventGroups_;

	};

}