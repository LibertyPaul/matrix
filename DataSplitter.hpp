#ifndef DATASPLITTER_HPP_INCLUDED
#define DATASPLITTER_HPP_INCLUDED

const uint16_t bitCapacity = 30;//32 - 1 из за того, что простое число меньше чем 2^32, поэтому мы можем гарантировать сохранность только 31 бита
								//31 - 1 - 1 бит используется во избежание исходной матрицы с нулевым определителем.

class DataSplitter{
	uint32_t K;
	uint32_t N;

	mutable mt19937 randomGenerator;

	void randomizeHigherBitsOfSecret(vector<ZNumber> &secret) const;
public:
	DataSplitter(uint32_t K, uint32_t N);
	Matrix split(const vector<uint32_t> &data) const;
	vector<uint32_t> restore(const Matrix &linearEquasion) const;
};

#endif // DATASPLITTER_HPP_INCLUDED
