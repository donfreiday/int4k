#include "int4k.h"
#include <iostream>
using namespace std;

int main() {
	cout << "Input 2 integers: ";

	// 9999999999999999999 is 1 away from overflow
	int4k i1;
	int4k i2;
	cin >> i1;
	cin >> i2;

	cout << i1 << " + " << i2 << " = ";
	i1 += i2;
	cout << i1 << endl;

	int4k i3 = i1 + i2;
	cout <<i1<<" + "<<i2<< " = " << i3 <<endl;


	system("pause");
	return 0;
}

