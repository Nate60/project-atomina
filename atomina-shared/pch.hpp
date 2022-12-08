#pragma once

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
#include <bitset>
#include <thread>
#include <future>
#include <chrono>
#include <optional>
#include <variant>
#include <stdexcept>
#include <filesystem>
#include <any>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/ostream_sink.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/fmt/bundled/format.h>

#ifdef _WINDOWS
#    include <Windows.h>
#    include <Shlwapi.h>
#    undef min
#    undef max
#endif