#include "CppUnitTest.h"
#include <atomina.h>
#include <string>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SystemUtils {

	TEST_CLASS(DirectoryUtils)
	{
	public:

		TEST_METHOD(get_current_working_directory)
		{
			auto cwd = ATMA::getWorkingDir();
			
			Assert::AreEqual(
				//Only the project path is relevant since the other parts will change
				cwd.substr(cwd.size() - 25, cwd.size() - 1).c_str(), 
				"\\project-atomina\\Release\\"
			);
		}

		TEST_METHOD(get_files_from_working_directory) {

			auto files = ATMA::getFileList(ATMA::getWorkingDir());

			Assert::IsTrue(files.size() > 1);

		}


	};

}
