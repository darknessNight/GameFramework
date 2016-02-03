#include "stdafx.h"
#include "Tests\Tests.h"

int main()
{
#ifdef DEBUG
	std::clog << Tests(TESTS_START, TESTS_STOP) << "\n\n\n" << std::endl;
	system("pause");
#endif // DEBUG

	return 0;
}