#include "pch.hpp"
#include "Music.hpp"

namespace ATMA
{

    Music::Music(const std::string &l_name): Resource(l_name) {}

    Music::Music(const std::string &l_name, const std::string &l_filename): Resource(l_name, l_filename) {}

    Music::~Music() {}

}