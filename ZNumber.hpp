#ifndef ZNUMBER_HPP_INCLUDED
#define ZNUMBER_HPP_INCLUDED


class ZNumber{
	uint64_t n;
public:
	explicit ZNumber(int64_t n = 0){
		if(n >= module)
			this->n = n % module;
		if(n < 0)
			this->n = module - (n % module);
	}


	ZNumber operator+(const ZNumber &zn) const{
		uint64_t res = this->n + zn.n;
		if(res >= module)
			res %= module;

		return ZNumber(res);
	}

	ZNumber operator+(const uint32_t &n) const{
		uint64_t res = this->n + n;
		if(res >= module)
			res %= module;

		return ZNumber(res);
	}

	ZNumber operator-(const ZNumber &zn) const{
		int64_t res = this->n - zn.n;
		if(res >= module)
			res %= module;
		if(res < 0)
			res = module - (res % module);

		return ZNumber(res);
	}

	ZNumber operator-(const uint32_t &n) const{
		uint64_t res = this->n - n;
		if(res >= module)
			res %= module;
		if(res < 0)
			res = module - (res % module);

		return ZNumber(res);
	}

	ZNumber operator*(const ZNumber &zn) const{
		uint64_t res = this->n * zn.n;
		if(res >= module)
			res %= module;

		return ZNumber(res);
	}

	ZNumber operator*(const uint32_t &n) const{
		uint64_t res = this->n * n;
		if(res >= module)
			res %= module;

		return ZNumber(res);
	}

	ZNumber operator/(const ZNumber &zn) const{
		return ZNumber(this->n / zn.n);
	}

	ZNumber operator/(const uint32_t &n) const{
		return ZNumber(this->n / n);
	}

	ZNumber operator%(const ZNumber &zn) const{
		return ZNumber(this->n % zn.n);
	}

	ZNumber operator%(const uint32_t &n) const{
		return ZNumber(this->n % n);
	}



	ZNumber &operator=(const ZNumber &zn){
		this->n = zn.n;
		return *this;
	}

	ZNumber &operator=(uint32_t n){
		this->n = n % module;
		return *this;
	}

	ZNumber operator+=(const ZNumber &zn){
		*this = *this + zn;
		return *this;
	}

	ZNumber operator+=(const uint32_t &n){
		*this = this->n + n;
		return *this;
	}

	ZNumber operator-=(const ZNumber &zn){
		*this = *this - zn;
		return *this;
	}

	ZNumber operator*=(const ZNumber &zn){
		*this = *this * zn;
		return *this;
	}

	ZNumber operator/=(const ZNumber &zn){
		*this = *this / zn;
		return *this;
	}

	ZNumber operator%=(const ZNumber &zn){
		*this = *this % zn;
		return *this;
	}


	ZNumber operator++(){
		return ZNumber(this->n++);
	}

	ZNumber operator++(int){
		return ZNumber(++this->n);
	}

	ZNumber operator--(){
		return ZNumber(this->n--);
	}

	ZNumber operator--(int){
		return ZNumber(--this->n);
	}





	bool operator==(const ZNumber &zn) const{
		return this->n == zn.n;
	}

	bool operator!=(const ZNumber &zn) const{
		return !(*this == zn);
	}

	bool operator>(const ZNumber &zn) const{
		return this->n < zn.n;
	}

	bool operator<(const ZNumber &zn) const{
		return this->n < zn.n;
	}

	bool operator<=(const ZNumber &zn) const{
		return !(*this > zn);
	}

	bool operator>=(const ZNumber &zn) const{
		return !(*this < zn);
	}

	bool operator!() const{
		return !this->n;
	}

	bool operator&&(const ZNumber &zn) const{
		if(!this->n)
			return false;
		else
			return zn.n;
	}

	bool operator||(const ZNumber &zn) const{
		if(this->n)
			return true;
		else
			return zn.n;
	}



	operator uint32_t() const{
		return this->n;
	}
};





#endif // ZNUMBER_HPP_INCLUDED
