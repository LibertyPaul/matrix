#ifndef DATASEPARATOR_HPP_INCLUDED
#define DATASEPARATOR_HPP_INCLUDED

#include <random>
#include <vector>
#include "Buffer.hpp"


struct DataContainer{
	uint32_t dataLength;//mb 16 or 64??
};



class DataSeparator{
	uint32_t K;
	uint32_t N;



	mutable mt19937 randomGenerator;

	const size_t serviceInformation = sizeof(DataContainer);
	const size_t serviceInformation_bits = serviceInformation * 8;
	size_t effectiveSingleStorageSize;





	vector<uint32_t> raw2container(const Buffer &src, size_t length) const;//src - буффер с полезной инфой
	Buffer container2raw(const vector<uint32_t> &src) const;
public:
	DataSeparator(uint32_t K, uint32_t N);

	vector<vector<uint32_t>> separate(const Buffer &data) const;
	Buffer restore(const vector<vector<uint32_t>> &parts) const;

};


#endif // DATASEPARATOR_HPP_INCLUDED
