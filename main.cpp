#include "int4k.h"
#include <iostream>
using namespace std;

int main() {
	int4k i1(1000);

	for (int i = 999; i > 0; i--)
		i1 *= i;
	cout << i1 << endl;


	//i1 *= i2;
	//cout << " * " << i2 << " = " << i1 << endl;

	/*// Test +=
	cout << i1 << " + " << i2 << " = ";
	i1 += i2;
	cout << i1 << endl;

	// Test +
	int4k i3 = i1 + i2;
	cout <<i1<<" + "<<i2<< " = " << i3 <<endl;*/

	system("pause");
	return 0;
}

