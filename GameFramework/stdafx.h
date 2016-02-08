#pragma once

#include <iostream>
#include <tchar.h>
#include <cmath>
#include <string>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>

#include "MemGuard.h"

//#define TEST_ALL

#ifdef TEST_ALL
#define TESTS_START 0
#define TESTS_STOP 32000
#else
#define TESTS_START 32000
#define TESTS_STOP 32000
#endif

typedef unsigned char byte;