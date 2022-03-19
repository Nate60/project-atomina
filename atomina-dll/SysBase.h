#pragma once
#include "ATConst.h"
#include "api.h"
#include "Observer.h"
#include "System.h"
#include "SystemManager.h"
#include "ATConst.h"

namespace ATMA {

	class SystemManager;
	class ATMA_API SysBase : public Observer {
		using ObjectId = unsigned int;
	public:
		SysBase(const System& l_type, SystemManager &l_man) : m_type(l_type), m_sysMan(l_man){

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
		System getType() const;

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
		
	protected:
		System m_type;
		std::bitset<ATConst::OBJECT_BIT_SIZE> m_req;
		std::vector<ObjectId> m_objects;

		SystemManager& m_sysMan;

		//TODO: Events

	};

}