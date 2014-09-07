#include <chrono>
#include <stdexcept>


#include "stuff.hpp"
using namespace std;
#include "DataSeparator.hpp"


DataSeparator::DataSeparator(const uint32_t K):
	K(K),
	randomGenerator(chrono::system_clock::now().time_since_epoch().count()),
	effectiveSingleStorageSize((K * bitCapacity - serviceInformation_bits) / 8){


	if(K * bitCapacity < sizeof(DataContainer))
		throw logic_error("K is so small, that even container info can't be emplaced in container");

}


vector<uint32_t> DataSeparator::raw2container(const Buffer &src, size_t srcLength) const{
	const size_t dcLength = sizeof(DataContainer);
	const size_t dcLength_bits = dcLength * 8;

	size_t srcLength_bits = srcLength * 8;

	size_t length = srcLength + dcLength;
	size_t length_bits = length * 8;

	size_t requiredContainerLength = length_bits / bitCapacity + (length_bits % bitCapacity != 0 ? 1 : 0);
	if(requiredContainerLength > K)
		throw runtime_error("requiredContainerLength is greater than K");


	DataContainer dc;
	dc.dataLength = srcLength;

	Buffer dcBuffer(sizeof(dc));
	dcBuffer.write<DataContainer>(dc);

	Buffer dst_buf(K * sizeof(uint32_t));
	dst_buf.fill(0);
	for(size_t i = 0; i < dcLength_bits; ++i){
		bool bit = dcBuffer.getBit(i);
		dst_buf.setBit<uint32_t, bitCapacity>(bit, i);
	}


	for(size_t i = 0; i < srcLength_bits; ++i){
		bool bit = src.getBit(i);
		dst_buf.setBit<uint32_t, bitCapacity>(bit, i + dcLength_bits);
	}


	vector<uint32_t> dst(K);
	for(auto &n : dst){
		n = randomGenerator();//зашумляем
		n &= ~(uint32_t(0x03) << bitCapacity);
	}

	dst_buf.read(&dst[0], K * sizeof(uint32_t));


	return dst;

}

Buffer DataSeparator::container2raw(const vector<uint32_t> &src) const{
	if(src.size() != K)
		throw runtime_error("Wrong container size");

	Buffer src_buf(src);

	Buffer dataContainerBuffer(sizeof(DataContainer));
	const size_t dcLength_bits = sizeof(DataContainer) * 8;

	for(size_t i = 0; i < dcLength_bits; ++i){//считываем структурку с длинной записи
		bool bit = src_buf.getBit<uint32_t, bitCapacity>(i);
		dataContainerBuffer.setBit(bit, i);
	}

	DataContainer dc = dataContainerBuffer.read<DataContainer>();

	Buffer rawDataBuffer(dc.dataLength);
	size_t dataLength_bits = dc.dataLength * 8;

	for(size_t i = dcLength_bits; i < dataLength_bits + dcLength_bits; ++i){//считываем полезную информацию
		bool bit = src_buf.getBit<uint32_t, bitCapacity>(i);
		rawDataBuffer.setBit(bit, i - dcLength_bits);
	}

	return rawDataBuffer;
}






vector<vector<uint32_t>> DataSeparator::separate(const Buffer &data) const{
	size_t length = data.getSize();


	size_t storagesCount = length / effectiveSingleStorageSize + (length % effectiveSingleStorageSize != 0 ? 1 : 0);

	vector<vector<uint32_t>> result;

	size_t pos = 0;
	for(size_t storageIndex = 0; storageIndex < storagesCount; ++storageIndex){
		size_t currentBlockSize = min(effectiveSingleStorageSize, length - pos);
		Buffer buffer(currentBlockSize);

		for(size_t i = 0; i < currentBlockSize; ++i)
			buffer.write<uint8_t>(data.get(pos++));//записываем полезную информацию


		vector<uint32_t> container = raw2container(buffer, currentBlockSize);//теперь это можно засунуть в матрицу
		result.push_back(container);

	}

	return result;
}





Buffer DataSeparator::restore(const vector<vector<uint32_t>> &parts) const{
	Buffer result;

	for(const auto &part : parts){
		Buffer partBuffer = container2raw(part);
		result.append(partBuffer);//можно оптимизировать. но лень.
	}

	return result;
}
















