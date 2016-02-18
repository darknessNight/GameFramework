#include "stdafx.h"
#include "Tests\Tests.h"



int main()
{
	std::clog << Tests(TESTS_START, TESTS_STOP) << "\n\n\n" << std::endl;
	//std::clog << Tests(0, TESTS_STOP) << "\n\n\n" << std::endl;
	system("pause");
	return 0;
}