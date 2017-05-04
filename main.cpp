#include "int4k.h"
#include <iostream>

int main() {
	int4k i1(1000);
	for (int i = 999; i > 0; i--)
		i1 *= i;
	std::cout << i1 << std::endl;
#ifdef WIN32
	system("pause");
#endif
	return 0;
}

