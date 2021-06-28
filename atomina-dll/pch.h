#pragma once

#include <string>
#include <functional>
#include <memory>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <mutex>
#include <random>
#include <bitset>

#ifdef _WINDOWS
	#include <Windows.h>
	#include <Shlwapi.h>
	#undef min
	#undef max
#endif