#ifndef ZNUMBER_HPP_INCLUDED
#define ZNUMBER_HPP_INCLUDED


class ZNumber{
	static const uint32_t module = 7;
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


	ZNumber operator++();
	ZNumber operator++(int);
	ZNumber operator--();
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

	friend int64_t operator+(const int64_t &n, const ZNumber &zn);
	friend int64_t operator-(const int64_t &n, const ZNumber &zn);
	friend int64_t operator*(const int64_t &n, const ZNumber &zn);
	friend int64_t operator/(const int64_t &n, const ZNumber &zn);
	friend int64_t operator%(const int64_t &n, const ZNumber &zn);

	friend ostream &operator<<(ostream &o, const ZNumber &zn);
	friend istream &operator>>(istream &i, const ZNumber &zn);
};

//ZNumber operator-(const ZNumber &zn);

int64_t operator+(const int64_t &n, const ZNumber &zn);
int64_t operator-(const int64_t &n, const ZNumber &zn);
int64_t operator*(const int64_t &n, const ZNumber &zn);
int64_t operator/(const int64_t &n, const ZNumber &zn);
int64_t operator%(const int64_t &n, const ZNumber &zn);

ostream &operator<<(ostream &o, const ZNumber &zn);
istream &operator>>(istream &i, const ZNumber &zn);



ostream &operator<<(ostream &o, const vector<ZNumber> &v);
vector<ZNumber> operator*(const vector<ZNumber> &v1, const vector<ZNumber> &v2);
vector<ZNumber> operator*(vector<ZNumber> v, const ZNumber &zn);
vector<ZNumber> operator/(vector<ZNumber> v, const ZNumber &zn);
vector<ZNumber> operator-=(vector<ZNumber> &zv1, const vector<ZNumber> &zv2);
ZNumber sum(const vector<ZNumber> &v);

void GCD_ext(int32_t a, int32_t b, int32_t &d, int32_t &x, int32_t &y);


#endif // ZNUMBER_HPP_INCLUDED
