#include "pch.h"
#include "SysUtil.h"
#include "AtominaException.h"


namespace ATMA {

#ifdef _WINDOWS

	std::string getWorkingDir() {

		char full[_MAX_PATH];
		if(_fullpath(full, ".\\", _MAX_PATH) != NULL)
			return full;
		else
			throw std::filesystem::filesystem_error(std::string("unable to get current directory"),std::error_code());

	}

	std::vector<std::string> getFileList(
		const std::string& l_dir,
		const std::string& l_search
	) {

		std::vector<std::string> files;
		if (l_search.empty()) { return files; }
		std::string path = l_dir + l_search;
		WIN32_FIND_DATAA data;
		HANDLE found = FindFirstFileA(path.c_str(), &data);
		if (found == INVALID_HANDLE_VALUE) { return files; }
		do {
			if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{
				files.emplace_back(data.cFileName);
			}
		} while (FindNextFileA(found, &data));
		FindClose(found);
		return files;
	}


#elif _LINUX



#endif

}