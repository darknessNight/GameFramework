#pragma once
#include "../stdafx.h"
#include "MemGuard.hpp"
#include "Events.hpp"
#include "Timer.h"
#include <exception>

namespace GF {
	namespace Core{
	}
}

class NonImplementError :public std::runtime_error {
	using runtime_error::runtime_error;
};