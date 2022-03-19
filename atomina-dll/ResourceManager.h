#pragma once
#include "api.h"
#include "pch.h"

template <typename derived, typename T>
class ATMA_API ResourceManager {
public:
	ResourceManager(const std::string& l_pathsFile)
	{
		//load files specified in paths file

	}

	virtual ~ResourceManager()
	{

	}

	std::optional<std::shared_ptr<T>> getResource(const std::string& l_id)
	{
		
	}

	std::optional<std::string> getPath(const std::string& l_id)
	{

	}

	bool requireResource(const std::string& l_id)
	{

	}

	bool releaseResource(const std::string& l_id)
	{

	}

	void purgeResources()
	{

	}

protected:

	bool load(std::shared_ptr<T> l_resource, const std::string& l_path)
	{
		return static_cast<std::shared_ptr<derived>>(this)->load(l_resource, l_path);
	}

private:


};