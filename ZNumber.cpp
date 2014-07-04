#include <istream>
#include <ostream>
#include <vector>
#include <stdexcept>

using namespace std;
#include "ZNumber.hpp"


ZNumber::ZNumber(int64_t n){
	if(n >= module)
		 n %= module;
	if(n < 0)
		n = module - (-n % module);

	this->n = n;
}

ZNumber ZNumber::operator+(const ZNumber &zn) const{
	uint64_t res = this->n + zn.n;
	if(res >= module)
		res %= module;
	return res;
}

ZNumber ZNumber::operator-(const ZNumber &zn) const{
	return *this + (-zn);
}

ZNumber ZNumber::operator*(const ZNumber &zn) const{
	uint64_t res = this->n * zn.n;
	if(res >= module)
		res %= module;

	return res;
}

ZNumber ZNumber::operator/(const ZNumber &zn) const{
	int32_t d, x, y;
	GCD_ext(zn.n, module, d, x, y);//хз как, но оно работает
	return *this * x;
}

ZNumber ZNumber::operator%(const ZNumber &zn) const{
	return this->n % zn.n;
}

const ZNumber &ZNumber::operator=(const ZNumber &zn){
	this->n = zn.n;
	return *this;
}

const ZNumber &ZNumber::operator+=(const ZNumber &zn){
	*this = *this + zn;
	return *this;
}


const ZNumber &ZNumber::operator-=(const ZNumber &zn){
	*this = *this - zn;
	return *this;
}

const ZNumber &ZNumber::operator*=(const ZNumber &zn){
	*this = *this * zn;
	return *this;
}

const ZNumber &ZNumber::operator/=(const ZNumber &zn){
	*this = *this / zn;
	return *this;
}

const ZNumber &ZNumber::operator%=(const ZNumber &zn){
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


ZNumber ZNumber::operator-() const{
	return ZNumber(module - (n % module));
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






ostream &operator<<(ostream &o, const vector<ZNumber> &v){
	for(auto &n : v)
		o << n << " ";
	return o;
}


vector<ZNumber> operator*(const vector<ZNumber> &v1, const vector<ZNumber> &v2){
	if(v1.size() != v2.size())
		throw logic_error("Vector size does not match");

	vector<ZNumber> res(v1.size());
	for(uint16_t i = 0; i < res.size(); ++i)
		res.at(i) = v1.at(i) * v2.at(i);
	return res;
}

ZNumber sum(const vector<ZNumber> &v){
	ZNumber res = 0;
	for(auto &value : v)
		res = res + value;
	return res;
}



void GCD_ext(int32_t a, int32_t b, int32_t &d, int32_t &x, int32_t &y){
	if(b == 0){
		d = a;
		x = 1;
		y = 0;
		return;
	}
	GCD_ext(b, a % b, d, x, y);
	uint32_t t = y;
	y = x - (a / b) * y;
	x = t;
}





