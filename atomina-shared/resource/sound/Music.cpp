#include "pch.hpp"
#include "Music.hpp"

namespace ATMA
{

    Music::Music(): Resource() {}

    Music::Music(const std::string &l_filename): Resource(l_filename) {}

    Music::~Music() {}

}