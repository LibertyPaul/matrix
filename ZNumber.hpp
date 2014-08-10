#ifndef ZNUMBER_HPP_INCLUDED
#define ZNUMBER_HPP_INCLUDED

#include <vector>
#include <istream>
#include <ostream>

class ZNumber{
	static const uint32_t module = 4294967291;//should be prime which is: 2^31 < P < 2^32
	uint32_t n;
public:
	ZNumber(int64_t n = 0);

	ZNumber operator+(const ZNumber &zn) const;
	ZNumber operator-(const ZNumber &zn) const;
	ZNumber operator*(const ZNumber &zn) const;
	ZNumber operator/(const ZNumber &zn) const;
	ZNumber operator%(const ZNumber &zn) const;

	const ZNumber &operator=(const ZNumber &zn);
	const ZNumber &operator+=(const ZNumber &zn);
	const ZNumber &operator-=(const ZNumber &zn);
	const ZNumber &operator*=(const ZNumber &zn);
	const ZNumber &operator/=(const ZNumber &zn);
	const ZNumber &operator%=(const ZNumber &zn);


	ZNumber &operator++();
	ZNumber operator++(int);
	ZNumber &operator--();
	ZNumber operator--(int);



	bool operator==(const ZNumber &zn) const;
	bool operator!=(const ZNumber &zn) const;
	bool operator<(const ZNumber &zn) const;
	bool operator>(const ZNumber &zn) const;
	bool operator<=(const ZNumber &zn) const;
	bool operator>=(const ZNumber &zn) const;
	bool operator!() const;
	bool operator&&(const ZNumber &zn) const;
	bool operator||(const ZNumber &zn) const;


	ZNumber operator-() const;


	uint32_t getValue() const;
	string toString() const;
	friend ostream &operator<<(ostream &o, const ZNumber &zn);
	friend istream &operator>>(istream &i, const ZNumber &zn);
};

ostream &operator<<(ostream &o, const ZNumber &zn);
istream &operator>>(istream &i, const ZNumber &zn);



ostream &operator<<(ostream &o, const vector<ZNumber> &v);
vector<ZNumber> operator+(const vector<ZNumber> &v1, const vector<ZNumber> &v2);
vector<ZNumber> operator+=(vector<ZNumber> &v1, const vector<ZNumber> &v2);
vector<ZNumber> operator-(const vector<ZNumber> &v2);
vector<ZNumber> operator-(const vector<ZNumber> &v1, const vector<ZNumber> &v2);
vector<ZNumber> operator-=(vector<ZNumber> &zv1, const vector<ZNumber> &zv2);

vector<ZNumber> operator*(const vector<ZNumber> &v1, const vector<ZNumber> &v2);
vector<ZNumber> operator*(vector<ZNumber> v, const ZNumber &zn);
vector<ZNumber> operator/(vector<ZNumber> v, const ZNumber &zn);
ZNumber sum(const vector<ZNumber> &v);

inline int64_t GCD_ext(int64_t n, int64_t module);
#endif // ZNUMBER_HPP_INCLUDED
