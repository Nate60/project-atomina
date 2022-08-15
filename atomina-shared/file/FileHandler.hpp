#pragma once
#include "../pch.hpp"
#include "../core/api.hpp"
#include "../util/Worker.hpp"



namespace ATMA {

	using FilePaths = std::vector<std::pair<std::string, size_t>>;

	class ATMA_API FileHandler : public Worker
	{

	public:
		FileHandler();
		void addFile(const std::string& l_file);
		virtual void saveToFile(const std::string& file);
		size_t getTotalLines() const;
		size_t getCurrentLine() const;

	protected:
		virtual bool nextLine(std::stringstream& l_stream) = 0;
		virtual void reset();

		void work();
		void count();

		FilePaths m_files;
		std::atomic<size_t> m_totalLines;
		std::atomic<size_t> m_currentLine;
	};

}

