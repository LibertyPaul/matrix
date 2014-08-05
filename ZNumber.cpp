#include <istream>
#include <ostream>
#include <vector>
#include <stdexcept>
#include <string>

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
	uint64_t res = static_cast<uint64_t>(this->n) + zn.n;
	if(res >= module)
		res %= module;
	return res;
}

ZNumber ZNumber::operator-(const ZNumber &zn) const{
	return *this + (-zn);
}

ZNumber ZNumber::operator*(const ZNumber &zn) const{
	uint64_t res = static_cast<uint64_t>(this->n) * zn.n;
	if(res >= module)
		res %= module;

	return res;
}

ZNumber ZNumber::operator/(const ZNumber &zn) const{
	if(zn == 0)
		throw logic_error("Division by 0");
	int64_t d, x, y;
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


const ZNumber &ZNumber::operator++(){
	return ZNumber(this->n++);
}

ZNumber ZNumber::operator++(int){
	return ZNumber(++this->n);
}

const ZNumber &ZNumber::operator--(){
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

bool ZNumber::operator<(const ZNumber &zn) const{
	return this->n < zn.n;
}

bool ZNumber::operator>(const ZNumber &zn) const{
	return this->n > zn.n;
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
	return this->n && zn.n;
}

bool ZNumber::operator||(const ZNumber &zn) const{
	return this->n || zn.n;
}


ZNumber ZNumber::operator-() const{
	return ZNumber(module - (n % module));
}


uint32_t ZNumber::getValue() const{
	return n;
}

string ZNumber::toString() const{
	string res;
	res = to_string(n);
	return res;
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

vector<ZNumber> operator+(const vector<ZNumber> &v1, const vector<ZNumber> &v2){
	if(v1.size() != v2.size())
		throw logic_error("Vector size does not match");

	vector<ZNumber> res(v1.size());
	for(uint16_t i = 0; i < res.size(); ++i)
		res.at(i) = v1.at(i) + v2.at(i);
	return res;
}

vector<ZNumber> operator+=(vector<ZNumber> &v1, const vector<ZNumber> &v2){
	v1 = v1 + v2;
	return v1;
}

vector<ZNumber> operator*(const vector<ZNumber> &v1, const vector<ZNumber> &v2){
	if(v1.size() != v2.size())
		throw logic_error("Vector size does not match");

	vector<ZNumber> res(v1.size());
	for(uint16_t i = 0; i < res.size(); ++i)
		res.at(i) = v1.at(i) * v2.at(i);
	return res;
}

vector<ZNumber> operator*(vector<ZNumber> v, const ZNumber &zn){
	for(auto &n : v)
		n *= zn;
	return v;
}

vector<ZNumber> operator/(vector<ZNumber> v, const ZNumber &zn){
	for(auto &n : v)
		n /= zn;
	return v;
}


vector<ZNumber> operator-=(vector<ZNumber> &zv1, const vector<ZNumber> &zv2){
	if(zv1.size() != zv2.size())
		throw logic_error("Vector size does not match");
	uint32_t K = zv1.size();
	for(uint32_t i = 0; i < K; ++i)
		zv1.at(i) -= zv2.at(i);

	return zv1;
}


ZNumber sum(const vector<ZNumber> &v){
	ZNumber res = 0;
	for(auto &value : v)
		res = res + value;
	return res;
}



void GCD_ext(int64_t a, int64_t b, int64_t &d, int64_t &x, int64_t &y){
	if(b == 0){
		d = a;
		x = 1;
		y = 0;
		return;
	}
	GCD_ext(b, a % b, d, x, y);
	int64_t t = y;
	y = x - (a / b) * y;
	x = t;
}





