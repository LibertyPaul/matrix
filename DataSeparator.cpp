#include <vector>
#include <istream>
#include <ostream>
#include <random>
#include <stdexcept>


using namespace std;
#include "ZNumber.hpp"
#include "Matrix.hpp"
#include "DataPart.hpp"
#include "DataSplitter.hpp"
#include "DataSeparator.hpp"


DataSeparator::DataSeparator(uint32_t K, uint32_t N): K(K), N(N){
	if(N < K)
		throw logic_error("N must be larger or equal to K");
}



vector<DataPart> DataSeparator::separate(const vector<uint8_t> &data) const{
	size_t length = data.size();
	size_t splitterCount = length * 8 / bitCapacity + ((length * 8) % bitCapacity != 0) ? 1 : 0;
	vector<DataPart> result(splitterCount);

	for(uint32_t i = 0; i < splitterCount; ++i){
		vector<uint8_t> separatedData(K);
		}
		}




vector<uint8_t> DataSeparator::restore(const vector<DataPart> &parts) const{}
