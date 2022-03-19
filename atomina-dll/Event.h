#pragma once
#include "pch.h"
#include "api.h"
#include "EventType.h"

namespace ATMA {

	struct ATMA_API Event {

	public:

		Event() : m_type(EventInfoType::RAW), m_code(0) {}

		Event(int l_code) : m_type(EventInfoType::RAW), m_code(l_code) {}

		Event(const Event& l_event) {
			move(l_event);
		}

		//copy operator
		Event& operator=(const Event& l_event) {
			if (&l_event != this) { move(l_event); }
			return *this;
		}

		~Event() {
	
		}

		union {
			int m_code;
		};

		EventInfoType m_type;

		/**
		* prints out members of the class, mainly for debugging and logging
		*/
		virtual std::string toString() const {
			std::stringstream ss;
			ss << "Event: " << m_code;
			return ss.str();
		}

	private:
		void move(const Event& l_event) {
			m_type = l_event.m_type;
			if (m_type == EventInfoType::RAW) { m_code = l_event.m_code; }
		}

	};


	inline std::ostream& operator<<(std::ostream& l_o, const Event& l_e) {
		return l_o << l_e.toString();
	}

}
