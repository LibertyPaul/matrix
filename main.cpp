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
using namespace std;


bool checkSecret(const vector<ZNumber> &secret){
	for(auto &coord : secret)
		if(coord != 0)
			return true;
	return false;
}


bool fullIteration(){
	unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	mt19937 g1(seed1);
	const uint16_t K = 3;


	vector<ZNumber> secret(K);
	do{
		for(auto &coord : secret)
			coord = g1();
	}while(checkSecret(secret) == false);


	vector<Matrix> matrix(K);
	for(size_t i = 0; i < K; ++i){
		matrix.at(i).resize(K, K);
		do{
			matrix.at(i).randomize();
			matrix.at(i).replaceRow(0, secret);
		}while(matrix.at(i).calcDeterminant() == 0);
	}


	Matrix res;
	for(const auto &m : matrix)
		res.insertRow(m.getFlatPolynomial());


	vector<ZNumber> coords = res.solveLinearEquasionSystem_Gauss();
	cout << "Secret: " << endl << secret << endl << "Result:" << endl << coords << endl << endl;
	return coords == secret;
}


int main(){
	uint16_t i = 1;
	while(true){
		cout << i++ << ":" << endl;
		fullIteration();
	}


}
