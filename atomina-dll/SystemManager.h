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

	using SystemType = unsigned int;

	class ATMA_API SystemManager : std::enable_shared_from_this<SystemManager> {
		using ObjectId = unsigned int;
	public:
		
		/**
		* Adds a System to system-class relation to the system manager
		*/
		template <class T>
		void addSystem(const System &l_sys)
		{
			addSystem<T>(static_cast<SystemType>(l_sys));
		}

		/**
		* Adds a System to system-class relation to the system manager
		*/
		template <class T>
		void addSystem(const SystemType &l_sys) {
			auto func = [=]()->std::shared_ptr<SysBase> { return std::shared_ptr<T>{new T(l_sys,*this)}; };
			m_systems[l_sys] = func();
		}


		/**
		* Gets a system from the system manager but throws exception if it does not exist
		*/
		template <class T>
		std::optional<std::shared_ptr<T>> getSystem(const System &l_sys)
		{
			return getSystem<T>(static_cast<SystemType>(l_sys));
		}
		/**
		* Gets a system from the system manager but throws exception if it does not exist
		*/
		template <class T>
		std::optional<std::shared_ptr<T>> getSystem(const SystemType &l_sys) {
			if (m_systems.count(l_sys) == 0) {
				return std::nullopt;
			}
			return std::dynamic_pointer_cast<T>(m_systems[l_sys]);
		}


		//getter for object manager
		std::shared_ptr<ObjectManager> getObjectManager() {
			return m_objMan;
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



	private:
		std::shared_ptr<ObjectManager> m_objMan;
		std::unordered_map<SystemType, std::shared_ptr<SysBase>> m_systems;

	};

}