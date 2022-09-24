#pragma once

#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <functional>

#include <string>
#include <string_view>
#include <sstream>
#include <vector>
#include <array>
#include <unordered_map>
#include <unordered_set>

#include "Mawar/Core/Log.hpp"
#include "Mawar/Debug/Instrumentor.hpp"

#ifdef M_PLATFORM_W10
	#include <Windows.h>
#endif // M_PLATFORM_W10
