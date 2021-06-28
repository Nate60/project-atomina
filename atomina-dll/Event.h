#pragma once
#include "pch.h"
#include "api.h"
#include "EventType.h"

namespace ATMA {

	struct ATMA_API Event {

	public:

		Event() : type_(EventInfoType::RAW), code_(0) {}

		Event(int l_code) : type_(EventInfoType::RAW), code_(l_code) {}

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
			int code_;
		};

		EventInfoType type_;

		/**
		* prints out members of the class, mainly for debugging and logging
		*/
		virtual std::string toString() const {
			std::stringstream ss;
			ss << "Event: " << code_;
			return ss.str();
		}

	private:
		void move(const Event& l_event) {
			type_ = l_event.type_;
			if (type_ == EventInfoType::RAW) { code_ = l_event.code_; }
		}

	};


	inline std::ostream& operator<<(std::ostream& l_o, const Event& l_e) {
		return l_o << l_e.toString();
	}

}
