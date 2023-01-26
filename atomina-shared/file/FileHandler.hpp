#pragma once
#include "pch.hpp"
#include "core/api.hpp"
#include "util/Worker.hpp"

namespace ATMA
{

    using FilePaths = std::vector<std::pair<std::string, size_t>>;

    /**
     * Handles reading and writing pure text or byte files asynchronously
     */
    class ATMA_API FileHandler: public Worker
    {
    public:
        // default constructor
        FileHandler();

        /**
         * add file to the list of files to be read
         * @param l_file string of the full qualified filename
         */
        void addFile(const std::string &l_file);

        /**
         * saves buffer to file
         * @param l_file full qualified filename as string for output file
         */
        virtual void saveToFile(const std::string &l_file);

        /**
         * get total lines of all files in worker
         * @returns number of lines
         */
        size_t getTotalLines() const;

        /**
         * gets the current number of lines that have been
         * processed
         * @returns number of processed lines
         */
        size_t getCurrentLine() const;
    protected:
        /**
         * advance the iterator by one line
         * @param l_stream string stream of the file
         * @returns if the iterator has hit end of stream
         */
        virtual bool nextLine(std::stringstream &l_stream) = 0;

        /**
         * reset iterator to beginning
         */
        virtual void reset();

        /**
         * process all files
         */
        void work();

        /**
         * counts the number of lines in all files and stores it
         * in internal members
         */
        void count();

        FilePaths m_files;
        std::atomic<size_t> m_totalLines;
        std::atomic<size_t> m_currentLine;
    };

}
