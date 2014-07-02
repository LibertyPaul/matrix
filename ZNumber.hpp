#ifndef ZNUMBER_HPP_INCLUDED
#define ZNUMBER_HPP_INCLUDED



class ZNumber{
	uint32_t n;
public:
	ZNumber(int64_t n = 0);

	ZNumber operator+(const ZNumber &zn) const;
	ZNumber operator-(const ZNumber &zn) const;
	ZNumber operator*(const ZNumber &zn) const;
	ZNumber operator/(const ZNumber &zn) const;
	ZNumber operator%(const ZNumber &zn) const;

	ZNumber &operator=(const ZNumber &zn);
	ZNumber operator+=(const ZNumber &zn);
	ZNumber operator-=(const ZNumber &zn);
	ZNumber operator*=(const ZNumber &zn);
	ZNumber operator/=(const ZNumber &zn);
	ZNumber operator%=(const ZNumber &zn);


	ZNumber operator++();
	ZNumber operator++(int);
	ZNumber operator--();
	ZNumber operator--(int);



	bool operator==(const ZNumber &zn) const;
	bool operator!=(const ZNumber &zn) const;
	bool operator>(const ZNumber &zn) const;
	bool operator<(const ZNumber &zn) const;
	bool operator<=(const ZNumber &zn) const;
	bool operator>=(const ZNumber &zn) const;
	bool operator!() const;
	bool operator&&(const ZNumber &zn) const;
	bool operator||(const ZNumber &zn) const;


	friend ZNumber operator-(const ZNumber &zn);

	friend int64_t operator+(const int64_t &n, const ZNumber &zn);
	friend int64_t operator-(const int64_t &n, const ZNumber &zn);
	friend int64_t operator*(const int64_t &n, const ZNumber &zn);
	friend int64_t operator/(const int64_t &n, const ZNumber &zn);
	friend int64_t operator%(const int64_t &n, const ZNumber &zn);

	friend ostream &operator<<(ostream &o, const ZNumber &zn);
	friend istream &operator>>(istream &i, const ZNumber &zn);
};

ZNumber operator-(const ZNumber &zn);

int64_t operator+(const int64_t &n, const ZNumber &zn);
int64_t operator-(const int64_t &n, const ZNumber &zn);
int64_t operator*(const int64_t &n, const ZNumber &zn);
int64_t operator/(const int64_t &n, const ZNumber &zn);
int64_t operator%(const int64_t &n, const ZNumber &zn);

ostream &operator<<(ostream &o, const ZNumber &zn);
istream &operator>>(istream &i, const ZNumber &zn);


#endif // ZNUMBER_HPP_INCLUDED
