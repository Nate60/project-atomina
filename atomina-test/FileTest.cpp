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
			auto cwd = std::filesystem::current_path().string();
			
			Assert::AreEqual(
				//Only the project path is relevant since the other parts will change
#ifdef _DEBUG
				cwd.substr(cwd.size() - 5, cwd.size()).c_str(),
				"Debug"
#else
				cwd.substr(cwd.size() - 7, cwd.size()).c_str(),
				"Release"
#endif
			);
		}

		TEST_METHOD(get_files_from_working_directory) {

			auto files = ATMA::getDirectoryList(std::filesystem::current_path());

			Assert::IsTrue(files.size() > 1);

		}


	};

}
