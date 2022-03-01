#include "pch.h"
#include "FileHandler.h"
#include "Log.h"


namespace ATMA {
	FileHandler::FileHandler() : m_totalLines(0), m_currentLine(0)
	{

	}

	void FileHandler::addFile(const std::string& l_file)
	{

	}

	size_t FileHandler::getTotalLines() const
	{
		return m_totalLines;
	}

	size_t FileHandler::getCurrentLine() const
	{
		return m_currentLine;
	}

	void FileHandler::saveToFile(const std::string& l_file)
	{

	}

	void FileHandler::reset()
	{

	}

	void FileHandler::count()
	{
		m_totalLines = 0;
		m_currentLine = 0;

		for (auto path_itr = m_files.begin(); path_itr != m_files.end();)
		{
			if (path_itr->first.empty())
			{
				m_files.erase(path_itr);
				continue;
			}

			std::ifstream file{ path_itr->first };

			if (!file.is_open())
			{
				ATMA_ENGINE_ERROR("Failed to load file {}", path_itr->first);
				m_files.erase(path_itr);
				continue;
			}

			file.unsetf(std::ios_base::skipws);

			//MUTEX LOCK
			std::lock_guard<std::mutex> lock{m_mtx};
			path_itr->second = static_cast<size_t>
				(
					std::count(
						std::istreambuf_iterator<char>(file),
						std::istreambuf_iterator<char>(),
						'\n'
					)
					);

			++path_itr;
			file.close();
		}
	}

	void FileHandler::work()
	{
		m_started = true;
		count();
		if (!m_totalLines)
		{
			return;
		}

		for (auto& path_itr : m_files)
		{
			reset();
			std::ifstream file{ path_itr.first };
			std::string line;
			std::string name;
			std::atomic<size_t> linesLeft = path_itr.second;

			while (std::getline(file, line))
			{
				++m_currentLine;
				--linesLeft;

				if (line[0] == '|')
				{
					continue;
				}

				std::stringstream keystream(line);
				if (!nextLine(keystream))
				{
					ATMA_ENGINE_ERROR("File Handler terminated due to an internal error");
					m_currentLine += linesLeft;
					break;
				}

			}
			file.close();
		}
	}

}
