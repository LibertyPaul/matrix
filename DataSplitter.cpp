#include <vector>
#include <chrono>
#include <random>
#include <initializer_list>
#include <stdexcept>

#include <istream>
#include <ostream>

using namespace std;
#include "ZNumber.hpp"
#include "Matrix.hpp"
#include "DataSplitter.hpp"

DataSplitter::DataSplitter(uint32_t K, uint32_t N): K(K), N(N), randomGenerator(chrono::system_clock::now().time_since_epoch().count()){
	if(N < K)
		throw logic_error("N must be larger or equal to K");
}

bool DataSplitter::checkSecret(const vector<ZNumber> &secret) const{
	for(auto &coord : secret)
		if(coord != 0)
			return true;
	return false;
}


Matrix DataSplitter::split(const vector<uint32_t> &data) const{
	vector<ZNumber> secret;
	for(const auto &n : data){
		if(n & (0x00000001U << 31))
			throw logic_error("Data containers must not contain more than 31 meaning bit. It will cause data loss.");
		secret.push_back(n);
	}

	vector<Matrix> matrix(N);
	for(size_t i = 0; i < N; ++i){
		matrix.at(i).resize(K, K);
		do{
			matrix.at(i).randomize();
			matrix.at(i).replaceRow(0, secret);
		}while(matrix.at(i).calcDeterminant() == 0);
	}

	Matrix linearEquasion;//если N > K, то уравнение избыточно.

	for(size_t i = 0; i < N; ++i)
		linearEquasion.insertRow(matrix.at(i).getFlatPolynomial());
	return linearEquasion;
}


vector<uint32_t> DataSplitter::restore(const Matrix &linearEquasion) const{//TODO: add checks
	if(linearEquasion.getRowCount() > K)
		throw logic_error("Equasion system is redundant");
	if(linearEquasion.getRowCount() < K)
		throw logic_error("Equasion system is insufficient");

	vector<ZNumber> coords = linearEquasion.solveLinearEquasionSystem();

	vector<uint32_t> data;
	for(const auto &ZN : coords)
		data.push_back(ZN.getValue());

	return data;
}












