#ifndef DATASPLITTER_HPP_INCLUDED
#define DATASPLITTER_HPP_INCLUDED

#include <random>
#include <vector>
#include "ZNumber.hpp"
#include "Matrix.hpp"

class DataSplitter{
	mutable mt19937 randomGenerator;

	void randomizeHigherBitsOfSecret(vector<ZNumber> &secret) const;//нужно зашумлять некоторые(зарезервированные и неиспользуемые) биты во избежание создания нулевых векторов
public:
	DataSplitter();
	Matrix split(const vector<uint32_t> &data, const uint32_t K, const uint32_t N) const;
	vector<uint32_t> restore(const Matrix &linearEquasion, const uint32_t K) const;
};

#endif // DATASPLITTER_HPP_INCLUDED
