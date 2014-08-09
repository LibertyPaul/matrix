#include <iostream>
#include <vector>
#include <chrono>



#include "stuff.h"
using namespace std;
#include "ZNumber.hpp"
#include "Matrix.hpp"
#include "DataSplitter.hpp"
#include "Buffer.hpp"
#include "DataSeparator.hpp"


const uint16_t K = 10, N = 15;
const uint64_t secretLength = 1024;

bool iter(mt19937 &randomGenerator){
	vector<uint8_t> rawData(secretLength);
	for(auto &n : rawData){
		n = randomGenerator();
	}
	Buffer src(rawData);

	DataSeparator dataSeparator(K, N);
	vector<vector<uint32_t>> dst = dataSeparator.separate(src);//формируем векторы секрета

	DataSplitter dataSplitter(K, N);






	Buffer result = dataSeparator.restore(dst);
	return result == src;
}



int main(){
	size_t seed = chrono::system_clock::now().time_since_epoch().count();
	mt19937 randomGenerator(seed);
	size_t successes = 0;

	for(size_t i = 0; i < 10; ++i)
		if(iter(randomGenerator))
			++successes;

	cout << successes << endl;

}
