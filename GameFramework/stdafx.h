#pragma once

//#include "MemGuard.h"

#include <iostream>
#include <tchar.h>
#include <cmath>
#include <string>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <time.h>

//#define TEST_ALL
//#define #include <functional>
#ifdef TEST_ALL
#define TESTS_START 0
#define TESTS_STOP 32000
#else
#define TESTS_START 32768
#define TESTS_STOP 32768
#endif

#ifdef EXPORTS
#define EXPORT_API __declspec(dllexport)
#else
#define EXPORT_API __declspec(dllimport)
#endif

typedef unsigned char byte;