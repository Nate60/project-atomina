#pragma once
#include "ATConst.h"
#include "api.h"
#include "Observer.h"
#include "System.h"
#include "SystemManager.h"
#include "ATConst.h"
#include "Event.h"
#include "Log.h"

namespace ATMA {

	using SystemType = unsigned int;

	class SystemManager;

	using ObjectId = unsigned int;
	using EventId = unsigned int;
	class ATMA_API SysBase : public Observer {

	public:
		SysBase(const SystemType &l_type, SystemManager &l_man) : m_type(l_type), m_sysMan(l_man){

		}

		virtual ~SysBase() {

		}

		/**
		* adds object to the system, returns true only if successful
		*/
		bool addObject(const ObjectId& l_id);


		/**
		* returns if object is in the system or not
		*/
		bool hasObject(const ObjectId& l_id) const;

		/**
		* removes object from the system, returns true only if succesful
		*/
		bool removeObject(const ObjectId& l_id);


		/**
		* gives the enumerator for the type of system
		*/
		SystemType getType() const;

		/**
		* returns true if the bitset matches the required bitset completely
		*/
		bool match(const std::bitset<ATConst::OBJECT_BIT_SIZE>& l_bits) const;

		/**
		* removes all objects
		*/
		void purge();
		 
		/**
		* updates all attributes of all the objects contained in the system
		*/
		virtual void update(float l_dt) = 0;

		virtual void handleEvent(const ObjectId& l_id, Event &l_event) = 0;
		
	protected:
		SystemType m_type;
		std::bitset<ATConst::OBJECT_BIT_SIZE> m_req;
		std::vector<ObjectId> m_objects;

		SystemManager& m_sysMan;

	};

}