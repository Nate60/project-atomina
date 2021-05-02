#include "CppUnitTest.h"
//Note Source files from atomina-game must be included as obj files 
// Properties > Linker > Input > Additional Dependencies
#include <atominamixin.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace atominatest
{
	TEST_CLASS(atomina_game)
	{
	public:
		
		TEST_METHOD(create_game)
		{
			GameApp* app = new GameApp();
			app->run();
			Assert::IsTrue(app->active);
			delete app;
		}
	};
}
