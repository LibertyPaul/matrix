#include <iostream>
#include <vector>
#include <istream>
#include <ostream>
#include <algorithm>

#include <chrono>
#include <random>
#include <initializer_list>


using namespace std;
#include "ZNumber.hpp"
#include "Matrix.hpp"
#include "DataSplitter.hpp"





int main(){
	DataSplitter dataSplitter(10, 20);
	vector<uint32_t> data = {42, 42, 42, 42, 42, 42, 42, 42, 42, 42};
	Matrix splittedData = dataSplitter.split(data);
	splittedData.resize(10, 11);

	vector<uint32_t> result = dataSplitter.restore(splittedData);

	if(data == result)
		cout << "Success!" << endl;
	else{
		cout << "Fault((" << endl;
		for(const auto &n : result)
			cout << n << ' ';
		cout << endl;
	}
}
