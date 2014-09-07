#include <chrono>
#include <stdexcept>


#include "stuff.hpp"
using namespace std;
#include "ZNumber.hpp"
#include "DataSplitter.hpp"

DataSplitter::DataSplitter():
	randomGenerator(chrono::system_clock::now().time_since_epoch().count()){
}



inline void DataSplitter::randomizeHigherBitsOfSecret(vector<ZNumber> &secret) const{
	for(auto &zn : secret){
		uint32_t mask = randomGenerator() % 2 << bitCapacity;
		zn ^= mask;
	}
}


Matrix DataSplitter::split(const vector<uint32_t> &data, const uint32_t K, const uint32_t N) const{
	if(K > N)
		throw logic_error("N must be >= K");

	if(data.size() != K)
		throw runtime_error("secret size must be == K");

	vector<ZNumber> secret(data.size());
	for(size_t i = 0; i < data.size(); ++i){
		if(data.at(i) >> bitCapacity != 0)
			throw logic_error("Data containers must not contain more than " + to_string(bitCapacity) + " meaning bits. It will cause data loss.");
		secret.at(i) = data.at(i);
	}


	vector<Matrix> matrices(N);
	for(auto &matrix : matrices){
		matrix.resize(K, K);
		matrix.randomize();

		size_t secretRowNumber = randomGenerator() % matrix.getRowCount();//выбираем случайную строку для вставки секрета
		matrix.replaceRow(secretRowNumber, secret);

		while(matrix.calcDeterminant() == 0){
			matrix.randomize();
			randomizeHigherBitsOfSecret(secret);
			matrix.replaceRow(secretRowNumber, secret);
		}
	}


	Matrix linearEquasion;//если N > K, то уравнение избыточно.

	for(size_t i = 0; i < N; ++i)
		linearEquasion.pushRowBack(matrices.at(i).getFlatPolynomial());
	return linearEquasion;
}


vector<uint32_t> DataSplitter::restore(const Matrix &linearEquasion, const uint32_t K) const{
	vector<ZNumber> coords = linearEquasion.solveLinearEquasionSystem();
	if(coords.size() != K)
		throw runtime_error("secret size != K");

	vector<uint32_t> data(K);
	for(size_t i = 0; i < K; ++i)
		data.at(i) = coords.at(i).getValue() & ~(1 << bitCapacity);

	return data;
}












