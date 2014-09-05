#include <stdexcept>

using namespace std;
#include "ZNumber.hpp"



ZNumber ZNumber::operator+(const ZNumber &zn) const{
	uint64_t res = static_cast<uint64_t>(this->getValue()) + zn.getValue();
	if(res >= module)
		res %= module;
	return res;
}

ZNumber ZNumber::operator-(const ZNumber &zn) const{
	return *this + (-zn);
}

ZNumber ZNumber::operator*(const ZNumber &zn) const{
	uint64_t res = static_cast<uint64_t>(this->getValue()) * zn.getValue();
	if(res >= module)
		res %= module;

	return res;
}

inline ZNumber ZNumber::getInverse() const{
	if(this->n == 0)
		throw logic_error("0 is not invertible");

	int64_t t = 0, new_t = 1;
	int64_t r = module, new_r = this->getValue();

	register int64_t temp;
	register int64_t quotient;
	while(new_r != 0){
		quotient = r / new_r;

		temp = t;
		t = new_t;
		new_t = temp - quotient * new_t;

		temp = r;
		r = new_r;
		new_r = temp - quotient * new_r;
	}
	if(r > 1)
		throw logic_error("N is not invertible");

	return ZNumber(t);
}




ZNumber ZNumber::operator/(const ZNumber &zn) const{
	return *this * zn.getInverse();
}

ZNumber ZNumber::operator%(const ZNumber &zn) const{
	return this->getValue() % zn.getValue();
}

ZNumber ZNumber::operator^(const ZNumber &zn) const{
	return this->getValue() ^ zn.getValue();
}

const ZNumber &ZNumber::operator=(const ZNumber &zn){
	this->n = zn.getValue();
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

const ZNumber &ZNumber::operator^=(const ZNumber &zn){
	*this = *this ^ zn;
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
	return this->getValue() == zn.getValue();
}

bool ZNumber::operator!=(const ZNumber &zn) const{
	return !(*this == zn);
}

bool ZNumber::operator<(const ZNumber &zn) const{
	return this->getValue() < zn.getValue();
}

bool ZNumber::operator>(const ZNumber &zn) const{
	return this->getValue() > zn.getValue();
}

bool ZNumber::operator<=(const ZNumber &zn) const{
	return !(*this > zn);
}

bool ZNumber::operator>=(const ZNumber &zn) const{
	return !(*this < zn);
}

bool ZNumber::operator!() const{
	return !this->getValue();
}

bool ZNumber::operator&&(const ZNumber &zn) const{
	return this->getValue() && zn.getValue();
}

bool ZNumber::operator||(const ZNumber &zn) const{
	return this->getValue() || zn.getValue();
}


ZNumber ZNumber::operator-() const{
	int64_t n_ = this->getValue();
	return ZNumber(-n_);
}


string ZNumber::toString() const{
	string res;
	res = to_string(this->getValue());
	return res;
}








ostream &operator<<(ostream &o, const vector<ZNumber> &v){
	for(const auto &n : v)
		o << n.toString() << " ";
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

const vector<ZNumber> &operator+=(vector<ZNumber> &v1, const vector<ZNumber> &v2){
	v1 = move(v1 + v2);
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


const vector<ZNumber> &operator-=(vector<ZNumber> &zv1, const vector<ZNumber> &zv2){
	zv1 = move(zv1 - zv2);
	return zv1;
}


ZNumber sum(const vector<ZNumber> &v){
	ZNumber res = 0;
	for(auto &value : v)
		res = res + value;
	return res;
}






