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
	return *this;
}