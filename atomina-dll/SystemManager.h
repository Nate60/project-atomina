#pragma once
#include "ATConst.h"
#include "api.h"
#include "System.h"
#include "SysBase.h"
#include "ObjectManager.h"
#include "AtominaException.h"

namespace ATMA {

	class SysBase;
	class ObjectManager;

	class ATMA_API SystemManager {
		using ObjectId = unsigned int;
	public:
		
		/**
		* Adds a System to system-class relation to the system manager
		*/
		template <class T>
		void addSystem(const System& l_sys) {
			auto func = [=]()->SysBase* { return new T(l_sys,this); };
			systems_[l_sys] = func();
		}

		/**
		* Gets a system from the system manager but throws exception if it does not exist
		*/
		template <class T>
		T* getSystem(const System& l_sys) {
			if (systems_.count(l_sys) == 0) {
				throw ObjectNotFoundException(std::string("System " + std::to_string((int)l_sys) + " does not exist").c_str());
			}
			return (T*)systems_[l_sys];
		}


		//getter for object manager
		ObjectManager* getObjectManager() {
			return objMan_;
		}

		//TODO events:


		//updates all attributes of all systems
		void update(float l_dt);

		void handleEvents();

		//TODO window abstraction

		/**
		* To be called when an object loses or gains an attribute so that it can be added and removed
		* from the corresponding systems
		*/
		void objectModified(const ObjectId& l_id, const std::bitset<ATConst::OBJECT_BIT_SIZE> l_bits);
		
		/**
		* Removes object id from all systems
		*/
		void removeObject(const ObjectId& l_id);


		/**
		* removes all object Ids
		*/
		void purgeObjects();

		/**
		* removes all system-system class relations
		*/
		void purgeSystems();

		ObjectManager* objMan_;

	private:
		std::unordered_map<System, SysBase*> systems_;

	};

}