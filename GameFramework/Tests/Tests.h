#pragma once
#include "Test1.h"
#include "Test2.h"
#include "Test3.h"
#include "Test4.h"
#include "Test5.h"

const int funcsCount = 5;
std::string(*funcs[funcsCount])() = { Test1, Test2, Test3, Test4, Test5 };

std::string Tests(int start, int stop) {
	std::string ret;
	std::string results;
	for (int i = __max(start - 1, 0); i < __min(stop, funcsCount); i++) {
		ret = funcs[i]();
		results += "\n Test " + std::to_string(i + 1) + " result: ";
		if (ret.size() > 0)results += '\n'+ret;
		else results += "OK";
	}
	return results;
}