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

int4k& int4k::operator+= (const int4k& rhs) {
	char* lhsDigits = this->digits;
	const char* rhsDigits = rhs.digits;
	__asm {
		mov esi, lhsDigits;
		mov edi, rhsDigits;
		mov ecx, 4096;
		clc;
	L1:;
		mov al, [esi]; // al = lhs[i]
		adc al, [edi]; // al = lhs[i] + rhs[i] + CF
		aaa;
		mov[esi], al;  // lhs[i] = al
		inc esi;
inc edi;
loop L1
	}
	return *this;
}

int4k int4k::operator+ (const int4k& rhs) const {
	int4k result(*this);
	result += rhs;
	return result;
}

int4k& int4k::operator*= (const int4k& rhs) {
	const char* rhsDigits = rhs.digits;
	int4k result;
	for (int i = 0; i < 4096; i++) {
		if (rhsDigits[i] != 0)
			result += this->multiplyByChar(rhsDigits[i], i);
	}
	for (int i = 0; i < 4096; i++)
		this->digits[i] = result.digits[i];
	return *this;
}

int4k int4k::multiplyByChar(char c, int shift) {
	char* lhsDigits = this->digits;
	int4k result;
	char* resultDigits = result.digits;
	__asm {
		mov esi, lhsDigits;
		mov edi, resultDigits;
		add edi, shift;
		mov bl, c;
		mov bh, 0;     // prevCarry = 0
		mov ecx, 4096;
		sub ecx, shift;
	L1:
		mov al, [esi]; // al = lhsDigits[i]
		mul bl;        // ax = lhsDigits[i] * c
		aam;           // ah = carry from multiplication, al = product
		mov dh, ah;    // tempCarry
		mov ah, 0;     // ah needs to be clear for aaa
		add al, bh;    // add carry
		aaa;           // ah = carry from addition, al = sum
		mov[edi], al;  // resultDigits[i] = sum
		mov bh, ah;    // carry = carry from addition
		add bh, dh;    // carry += carry from multiplication
		inc esi;
		inc edi;
		loop L1;
	}
	return result;
}

int4k int4k::operator* (const int4k& val) const {
	int4k result(*this);
	result *= val;
	return result;
}

int4k& int4k::operator-= (const int4k& rhs) {
	char* lhsDigits = this->digits;
	const char* rhsDigits = rhs.digits;
	__asm {
		mov esi, lhsDigits;
		mov edi, rhsDigits;
		mov ecx, 4096;
		clc;
	L1:;
		mov al, [esi]; // al = lhs[i]
		sbb al, [edi]; // al = result of sub
		aas;           // ah = adjusted difference
		mov[esi], al;  // lhs[i] = al
		inc esi;
		inc edi;
		loop L1
	}
	return *this;
}

int4k int4k::operator- (const int4k& rhs) const {
	int4k result(*this);
	result -= rhs;
	return result;
}

int4k& int4k::operator/= (const int4k& rhs) {
	int4k result (*this / rhs);
	for (int i = 0; i < 4096; i++)
		this->digits[i] = result.digits[i];
	return *this;
}

int4k int4k::operator/ (const int4k& rhs) const {
	int4k tmp(*this);
	int4k quotient;
	while (tmp >= rhs) {
		tmp -= rhs;
		++quotient;
	}
	return quotient;
	
}

bool int4k::operator> (const int4k& rhs) {
	for (int i = 4095; i >= 0; i--) {
		if (this->digits[i] > rhs.digits[i])
			return true;
		else if (this->digits[i] < rhs.digits[i])
			return false;
	}
	return false;
}

bool int4k::operator>= (const int4k& rhs) {
	bool result;
	for (int i = 4095; i >= 0; i--) {
		if (this->digits[i] > rhs.digits[i])
			return true;
		else if (this->digits[i] < rhs.digits[i])
			return false;
	}
	return true;
}

// prefix ++: no parameter, returns a reference
int4k& int4k::operator++ () {
	*this += 1;
	return *this;
}

// postfix ++: dummy parameter, returns a value
int4k int4k::operator++ (int) {
	int4k result(*this);
	++(*this);
	return result;
}