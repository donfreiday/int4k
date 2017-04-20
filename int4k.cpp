#include "int4k.h"
#include <iostream>
#include <cctype>

int4k::int4k() {
	init_digits();
}

int4k::int4k(int val) {
	init_digits();
	for (int i = 0; val; i++, val /= 10)
		digits[i] = val % 10;
}

void int4k::init_digits() {
	char* p = digits;
	__asm {
		mov al, 0;
		mov edi, p;
		mov ecx, 4096;
		cld;
		rep stosb;
	}
}

std::ostream& operator<< (std::ostream& os, const int4k& val) {
	// Find the most significant digit
	int msd = 0;
	for (int i = 0; i < 4095; i++) {
		if (val.digits[i])
			msd = i;
	}
	// Create C-string of ASCII digits
	static char s[4096];
	for (int i = 0, j = msd; i < msd + 1; i++, j--)
		s[i] = val.digits[j] | 0x30;
	s[msd + 1] = 0;
	// Output the string
	os << s;
	return os;
}

std::istream& operator>> (std::istream& is, int4k& val) {
	static char s[4096];
	// Skip over spaces
	while (std::isspace(is.peek()))
		is.get();
	// Ensure next character in input stream is a digit
	if (!std::isdigit(is.peek()))
		is.setstate(std::ios::failbit);
	else {
		// Initialize digits
		val.init_digits();
		// Read one digit at a time until non-digit reached
		int size = 0;
		while (std::isdigit(is.peek()))
			s[size++] = is.get() & 0x0f;
		for (int i = 0; i < size; i++)
			val.digits[i] = s[size - i - 1];
	}
	return is;
}

int4k& int4k::operator+= (const int4k& val) {
	char* lhs = this->digits;
	const char* rhs = val.digits;

	__asm {
		mov esi, 4095;      
		mov edi, 4096;
		mov ecx, 4096;
		mov bh, 0;       // set carry value to zero;
	L1:;
		mov ah, 0;       // clear ah before addition;
		mov edx,lhs
		mov al, byte ptr [edx+esi];// get the MSD in al;
		add al, bh;      // add the previous carry;
		aaa;             // adjust the sum, ah = carry1;
		mov bh, ah;      // save the carry in bh;
		or bh, 30h;      // convert the carry in bh to ascii;

		mov edx, rhs
		add al, byte ptr [edx+esi];// add the second digit;
		aaa;             // adjust the sum, ah = carry;
		or bh, ah;       // or the carry with carry1;
		; // or bh, 30h; convert carry to ascii;
		; // or al, 30h; convert carry1 back to ascii;
		;// mov sum[edi], al; save it in sum;
		mov edx, lhs;
		mov byte ptr[edx + esi], al;//save result


		or bh, 30h;// convert carry to ascii;
		or al, 30h;// convert carry1 back to ascii;

		dec esi;// back up one digit;
		dec edi;
		loop L1;
		; // we'll ignore the final carry, behavior on overflow is undefined
		; // sub bh, 30h; convert back to decimal;
		; // mov sum[edi], bh; save last carry digit;
	}


	return *this;
}