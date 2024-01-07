#pragma once

#include <span>
#include <string>
#include <array>
#include <functional>
#include <memory>
#include <execution>
#include <vector>
#include <tuple>
#include <set>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <mutex>
#include <regex>
#include <random>
#define _USE_MATH_DEFINES
#include <cmath>
#include <math.h>
#include <bitset>
#include <cstdarg>
#include <thread>
#include <future>
#include <chrono>
#include <optional>
#include <variant>
#include <stdexcept>
#include <filesystem>
#include <type_traits>
#include <any>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/fmt/ostr.h>

#ifdef _WINDOWS
#    ifndef WIN32_LEAN_AND_MEAN
#        define WIN32_LEAN_AND_MEAN
#    endif
#    include <gl/glew.h>
#    include <gl/wglew.h>
#    include <Windows.h>
#    include <Shlwapi.h>
#    undef min // windows defines min and max which collides with math.min/max
#    undef max
#elif linux
#    include <X11/Xlib.h>
#    include <X11/Xutil.h>
#    include <GL/glew.h>
#    include <GL/glxew.h>
#    undef None // X11 defines None as a macro for 0L which can collide with enums
#    undef Bool // another macro from X11 that interferes with gtest
#endif