#pragma once
#include "api.h"

namespace ATMA {


	/*
	* Gets the working directory of the executable as an absolute path string
	*/
	ATMA_API std::string getWorkingDir();
	
	/*
	* Retrieves the names of all the files in the listed directory that match
	* the given filter
	*/
	ATMA_API std::vector<std::string> getFileList(
		const std::string& l_dir,
		const std::string& l_search = "*.*"
	);

}

