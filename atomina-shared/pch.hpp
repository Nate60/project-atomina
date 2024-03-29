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
#include <cmath>
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
#include <spdlog/fmt/bundled/format.h>
#include "../deps/stb/stb_image.h"

#ifdef _WINDOWS
#    ifndef WIN32_LEAN_AND_MEAN
#        define WIN32_LEAN_AND_MEAN
#    endif
#    include <Windows.h>
#    include <Shlwapi.h>
#    undef min
#    undef max
#endif
#ifdef ATMA_USE_OPENGL
#    include <glad/glad.h>
#    include <GLFW/glfw3.h>
#endif