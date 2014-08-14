#ifndef ZNUMBER_HPP_INCLUDED
#define ZNUMBER_HPP_INCLUDED

#include <vector>
#include <ostream>

class ZNumber{
	static const uint32_t module = 4294967291;//should be prime between 2^31 and 2^32
	uint32_t n;
public:
	ZNumber(int64_t n = 0);

	ZNumber operator+(const ZNumber &zn) const;
	ZNumber operator-() const;
	ZNumber operator-(const ZNumber &zn) const;
	ZNumber operator*(const ZNumber &zn) const;
	ZNumber getInverse() const;//вычисляет 1 / n (mod module). Расширенный алгоритм Эвклида.
	ZNumber operator/(const ZNumber &zn) const;
	ZNumber operator%(const ZNumber &zn) const;
	ZNumber operator^(const ZNumber &zn) const;

	const ZNumber &operator=(const ZNumber &zn);
	const ZNumber &operator+=(const ZNumber &zn);
	const ZNumber &operator-=(const ZNumber &zn);
	const ZNumber &operator*=(const ZNumber &zn);
	const ZNumber &operator/=(const ZNumber &zn);
	const ZNumber &operator%=(const ZNumber &zn);
	const ZNumber &operator^=(const ZNumber &zn);



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




	uint32_t getValue() const;
	string toString() const;
};




ostream &operator<<(ostream &o, const vector<ZNumber> &v);
vector<ZNumber> operator+(const vector<ZNumber> &v1, const vector<ZNumber> &v2);
const vector<ZNumber> &operator+=(vector<ZNumber> &v1, const vector<ZNumber> &v2);
vector<ZNumber> operator-(const vector<ZNumber> &v2);
vector<ZNumber> operator-(const vector<ZNumber> &v1, const vector<ZNumber> &v2);
const vector<ZNumber> &operator-=(vector<ZNumber> &zv1, const vector<ZNumber> &zv2);

vector<ZNumber> operator*(const vector<ZNumber> &v1, const vector<ZNumber> &v2);
vector<ZNumber> operator*(vector<ZNumber> v, const ZNumber &zn);
vector<ZNumber> operator/(vector<ZNumber> v, const ZNumber &zn);
ZNumber sum(const vector<ZNumber> &v);

#endif // ZNUMBER_HPP_INCLUDED
