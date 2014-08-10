#include <stdexcept>
#include <thread>

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
	//int64_t x, y;
	//GCD_ext(zn.n, module, x, y);//хз как, но оно работает
	int64_t x = GCD_ext(zn.n, module);
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


ZNumber &ZNumber::operator++(){
	*this += 1;
	return *this;
}

ZNumber ZNumber::operator++(int){
	ZNumber copy(*this);
	*this += 1;
	return copy;
}

ZNumber &ZNumber::operator--(){
	*this -= 1;
	return *this;
}

ZNumber ZNumber::operator--(int){
	ZNumber copy(*this);
	*this -= 1;
	return copy;
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

vector<ZNumber> operator-(const vector<ZNumber> &v2){
	vector<ZNumber> result(v2.size());
	for(size_t i = 0; i < v2.size(); ++i)
		result.at(i) = -v2.at(i);
	return result;
}

vector<ZNumber> operator-(const vector<ZNumber> &v1, const vector<ZNumber> &v2){
	return v1 + (-v2);
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
	zv1 = zv1 - zv2;
	return zv1;
}


ZNumber sum(const vector<ZNumber> &v){
	ZNumber res = 0;
	for(auto &value : v)
		res = res + value;
	return res;
}


inline int64_t GCD_ext(int64_t n, int64_t module){
	int64_t t = 0, new_t = 1;
	int64_t r = module, new_r = n;

	int64_t temp;
	while(new_r != 0){
		uint64_t quotient = r / new_r;

		temp = t;
		t = new_t;
		new_t = temp - quotient * new_t;

		temp = r;
		r = new_r;
		new_r = temp - quotient * new_r;
	}
	if(r > 1)
		throw logic_error("N is not invertible");
	if(t < 0)
		t = t + module;

	return t;
}





