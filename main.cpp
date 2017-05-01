#include "int4k.h"
#include <iostream>
using namespace std;

int main() {
	//int4k i1(1000);
	//for (int i = 999; i > 0; i--)
	//	i1 *= i;
	//cout << i1 << endl;

	int4k i1;
	int4k i2;
	cin >> i1 >> i2;
	i1 /= i2;
	cout << i1 << endl;
	//cout << i1 << endl;
	//if (i1 == i2) {
	//	cout << i1 << " == " << i2<<endl;
	//}


	/*int4k i1;
	int4k i2;
	cin >> i1 >> i2;
	cout << i1 * i2 << endl;*/

	system("pause");
	return 0;
}

