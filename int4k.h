#pragma once

#include <iostream>

class int4k {
	friend std::ostream& operator<< (std::ostream& os, const int4k& val);
	friend std::istream& operator>> (std::istream& is, int4k& val);
protected:
	char digits[4096]; // 4095 digits, plus 1 for overflow
	void init_digits();
public:
	int4k();
	int4k(int val);

	int4k operator+ (const int4k& val) const;
	int4k operator- (const int4k& val) const;
	int4k operator* (const int4k& val) const;

	int4k& operator+= (const int4k& val);
	int4k& operator-= (const int4k& val);
	int4k& operator*= (const int4k& val);
};


