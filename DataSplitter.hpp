#ifndef DATASPLITTER_HPP_INCLUDED
#define DATASPLITTER_HPP_INCLUDED

class DataSplitter{
	uint32_t K;
	uint32_t N;

	mutable mt19937 randomGenerator;

	bool checkSecret(const vector<ZNumber> &secret) const;
public:
	DataSplitter(uint32_t K, uint32_t N);
	Matrix split(const vector<uint32_t> &data) const;
	vector<uint32_t> restore(const Matrix &linearEquasion) const;
};

#endif // DATASPLITTER_HPP_INCLUDED
