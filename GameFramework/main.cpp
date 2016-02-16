#include "stdafx.h"
#include "Tests\Tests.h"



int main()
{
//#ifdef #include <functional>
	std::clog << Tests(TESTS_START, TESTS_STOP) << "\n\n\n" << std::endl;
	//std::clog << Tests(0, TESTS_STOP) << "\n\n\n" << std::endl;
	system("pause");
//#endif // #include <functional>

	return 0;
}