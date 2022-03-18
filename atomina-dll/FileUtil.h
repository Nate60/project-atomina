#pragma once
#include "api.h"
#include "pch.h"

namespace ATMA
{
	namespace stdfs = std::filesystem;

	/*
	* Retrieves the names of all the files in the listed directory that match
	* the given filter
	*/
	ATMA_API std::vector<stdfs::path> getDirectoryList(
		const stdfs::path &path,
		const std::string &filter = ".*[.].*"
	);

}