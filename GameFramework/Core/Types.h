#pragma once
#include "../stdafx.h"
#include "MemGuard.hpp"
#include "Events.hpp"
#include "Timer.h"
#include <exception>
#include <vector>

namespace GF {
	namespace Core{
		__interface ObjectSerialize {
			std::vector<unsigned char> serialize();
			bool deserialize(std::vector<unsigned char>);
		};
	}
}

class NonImplementError :public std::runtime_error {
	using runtime_error::runtime_error;
};