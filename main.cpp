#include "int4k.h"
#include <iostream>
using namespace std;

int main() {
	int4k i1;
	int4k i2(12345);
	cout << i1 << endl;
	cout << i2 << endl;
	cout << "Input integer: ";
	cin >> i1;
	cout << i1 << endl;
	system("pause");
	return 0;
}