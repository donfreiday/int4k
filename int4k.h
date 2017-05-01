#pragma once

#include <iostream>

class int4k {
	friend std::ostream& operator<< (std::ostream& os, const int4k& val);
	friend std::istream& operator>> (std::istream& is, int4k& val);
protected:
	char digits[4096]; // 4095 digits, plus 1 for overflow
	void init_digits();
	int4k multiplyByChar(char c, int shift);
public:
	int4k();
	int4k(int val);

	int4k operator+ (const int4k& rhs) const;
	int4k operator- (const int4k& rhs) const;
	int4k operator* (const int4k& rhs) const;
	int4k operator/ (const int4k& rhs) const;

	int4k& operator+= (const int4k& rhs);
	int4k& operator-= (const int4k& rhs);
	int4k& operator*= (const int4k& rhs);
	int4k& operator/= (const int4k& rhs);

	int4k& operator++ (); // prefix ++: no parameter, returns a reference
	int4k operator++ (int); // postfix ++: dummy parameter, returns a value
	int4k& operator-- (); // prefix --: no parameter, returns a reference
	int4k operator-- (int); // postfix --: dummy parameter, returns a value

	bool operator> (const int4k& rhs);
	bool operator< (const int4k& rhs);
	bool operator>= (const int4k& rhs);
	bool operator<= (const int4k& rhs);
	bool operator== (const int4k& rhs) const;
};


