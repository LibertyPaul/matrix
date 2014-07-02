#include <istream>
#include <ostream>

using namespace std;
#include "config.hpp"
#include "ZNumber.hpp"


ZNumber::ZNumber(int64_t n){
	if(n >= module)
		 n %= module;
	if(n < 0)
		n = module - (n % module);

	this->n = n;
}

ZNumber ZNumber::operator+(const ZNumber &zn) const{
	uint64_t res = this->n + zn.n;
	if(res >= module)
		res %= module;
	return res;
}

ZNumber ZNumber::operator-(const ZNumber &zn) const{
	int64_t res = this->n - zn.n;
	if(res >= module)
		res %= module;
	if(res < 0)
		res = module - res;

	return res;
}

ZNumber ZNumber::operator*(const ZNumber &zn) const{
	uint64_t res = this->n * zn.n;
	if(res >= module)
		res %= module;

	return res;
}

ZNumber ZNumber::operator/(const ZNumber &zn) const{
	return this->n / zn.n;
}

ZNumber ZNumber::operator%(const ZNumber &zn) const{
	return this->n % zn.n;
}

ZNumber &ZNumber::operator=(const ZNumber &zn){
	this->n = zn.n;
	return *this;
}

ZNumber ZNumber::operator+=(const ZNumber &zn){
	*this = *this + zn;
	return *this;
}


ZNumber ZNumber::operator-=(const ZNumber &zn){
	*this = *this - zn;
	return *this;
}

ZNumber ZNumber::operator*=(const ZNumber &zn){
	*this = *this * zn;
	return *this;
}

ZNumber ZNumber::operator/=(const ZNumber &zn){
	*this = *this / zn;
	return *this;
}

ZNumber ZNumber::operator%=(const ZNumber &zn){
	*this = *this % zn;
	return *this;
}


ZNumber ZNumber::operator++(){
	return ZNumber(this->n++);
}

ZNumber ZNumber::operator++(int){
	return ZNumber(++this->n);
}

ZNumber ZNumber::operator--(){
	return ZNumber(this->n--);
}

ZNumber ZNumber::operator--(int){
	return ZNumber(--this->n);
}





bool ZNumber::operator==(const ZNumber &zn) const{
	return this->n == zn.n;
}

bool ZNumber::operator!=(const ZNumber &zn) const{
	return !(*this == zn);
}

bool ZNumber::operator>(const ZNumber &zn) const{
	return this->n < zn.n;
}

bool ZNumber::operator<(const ZNumber &zn) const{
	return this->n < zn.n;
}

bool ZNumber::operator<=(const ZNumber &zn) const{
	return !(*this > zn);
}

bool ZNumber::operator>=(const ZNumber &zn) const{
	return !(*this < zn);
}

bool ZNumber::operator!() const{
	return !this->n;
}

bool ZNumber::operator&&(const ZNumber &zn) const{
	if(this->n)
		return zn.n;
	else
		return false;
}

bool ZNumber::operator||(const ZNumber &zn) const{
	if(this->n)
		return true;
	else
		return zn.n;
}




ZNumber operator-(const ZNumber &zn){
	return ZNumber(-zn.n);
}




int64_t operator+(const int64_t &n, const ZNumber &zn){
	return n + zn.n;
}

int64_t operator-(const int64_t &n, const ZNumber &zn){
	return n - zn.n;
}

int64_t operator*(const int64_t &n, const ZNumber &zn){
	return n * zn.n;
}

int64_t operator/(const int64_t &n, const ZNumber &zn){
	return n / zn.n;
}

int64_t operator%(const int64_t &n, const ZNumber &zn){
	return n % zn.n;
}

ostream &operator<<(ostream &o, const ZNumber &zn){
	o << zn.n;
	return o;
}

istream &operator>>(istream &i, const ZNumber &zn){
	i >> zn.n;
	return i;
}







