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
		mov esi, lhs;
		mov edi, rhs;
		mov ecx, 0;          // Counter
		mov bh, 0;           // Clear carry
	L1:;
		mov ah, 0;           // Clear ah for ascii addition
		mov al, [esi + ecx]; // al = lhs[i]
		add al, bh;          // add the carry from last addition
		aaa;              
		mov bh, ah;	         // save the carry from adding the previous carry
		add al, [edi + ecx]; // al = lhs[i] + rhs[i]
		aaa;
		or bh, ah;           // See if either addition generated a carry
		mov[esi + ecx], al;  // lhs[i] = al
		inc ecx;
		cmp ecx, 4096;
		jl L1;
	}
	return *this;
}

int4k int4k::operator+ (const int4k& val) const {
	int4k result(*this);
	result += val;
	return result;
}

int4k& int4k::operator*= (const int4k& val) {
	const char* rhs = val.digits;
	int4k result;
	for (int i = 0; i < 4096; i++) {
		result+= this->multiplyByChar(rhs[i], i);
	}
	for (int i = 0; i < 4096; i++)
		this->digits[i] = result.digits[i];
	return *this;
}


int4k int4k::multiplyByChar(char c, int shift) {
	int4k result;
	char* digits = this->digits;
	char* resultDigits = result.digits;
	int loops = 4096 - shift;
	__asm {
		mov esi, digits;
		mov edi, resultDigits;
		add edi, shift;
		mov ecx, 0;
		mov bh, 0; // clear carry
	L1:;
		mov bl, [esi + ecx]; // bl = digits[i]
		mov al, c;           // al = c
		mul bl;              // ax = digits[i] * c
		aam;
		add al, bh;          // Add in the carry
		mov[edi + ecx], al;  // result[i] = al
		mov bh, ah;          // Save the carry

		inc ecx;
		cmp ecx, loops;
		jl L1;
	}
	return result;
}