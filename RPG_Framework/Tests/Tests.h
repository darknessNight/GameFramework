#pragma once
#include "ArithmeticParserTest.h"
#define MIN_(a,b) (a>b?b:a)

const int funcsCount = 1;
std::string(*funcs[funcsCount])() = { Test1 };

std::string Tests(int start, int stop) {
	std::string ret;
	std::string results;
	for (int i = MIN_(start - 1, 0); i < MIN_(stop, funcsCount); i++) {
		ret = funcs[i]();
		if (ret.size() > 0)results += ret + '\n';
	}
	return results;
}