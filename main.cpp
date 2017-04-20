#include "int4k.h"
#include <iostream>
using namespace std;

//void testASCIIAdditon();

int main() {
	/*int4k i1;
	int4k i2(12345);
	cout << i1 << endl;
	cout << i2 << endl;
	cout << "Input integer: ";
	cin >> i1;
	cout << i1 << endl;*/
	

	//int4k i1(1);
	//1999999999999999999
	int4k i1;
	int4k i2;
	cin >> i1;
	cin >> i2;
	i1 += i2;
	cout << i1 << endl;




	system("pause");
	return 0;
}


/*
void testASCIIAdditon() {
	// Test ASCII addition algorithm
	char lhs[4];
	char rhs[4];
	char sum[5];
	for (int i = 0; i < 4; i++) {
		lhs[i] = 0;
		rhs[i] = 0;
		sum[i] = 0;
	}
	sum[4] = 0;

	// OK, let's add 2 and 3.
	lhs[0] = 2;
	rhs[0] = 3;

	__asm {
		mov esi, 3;// esi is index;
		mov edi, 4;//
		mov ecx, 4;//
		mov bh, 0;// set carry value to zero;
	L1:;
		mov ah, 0;// clear ah before addition;
		mov al, lhs[esi];// get the MSD in al;
		add al, bh;// add the previous carry;
		aaa;// adjust the sum, ah = carry1;
		mov bh, ah;// save the carry in bh;
		or bh, 30h;// convert the carry in bh to ascii;

		add al, rhs[esi];// add the second digit;
		aaa;// adjust the sum, ah = carry;
		or bh, ah;// or the carry with carry1;
		; or bh, 30h;// convert carry to ascii;
		; or al, 30h;// convert carry1 back to ascii;
		mov sum[edi], al;// save it in sum;

		or bh, 30h;// convert carry to ascii;
		or al, 30h;// convert carry1 back to ascii;

		dec esi;// back up one digit;
		dec edi;
		loop L1;

		sub bh, 30h;// convert back to decimal;
		mov sum[edi], bh;//save last carry digit


	}
}
*/