#include "CppUnitTest.h"
#include <functional>
#include <atomina.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Event {

	TEST_CLASS(EventDispatcher) {

		TEST_CLASS_INITIALIZE(Start_Logger) {
			ATMA::Log::Init();
		}

		TEST_METHOD(dispatch_mouse_event) {

			ATMA::MousePressedEvent e(0.0f, 0.0f, 0);
			ATMA::EventDispatcher

		}

	};

}
