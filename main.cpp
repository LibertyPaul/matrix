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
	unsigned seed1 = chrono::system_clock::now().time_since_epoch().count();
	mt19937 g1(seed1);
	const uint16_t K = 10;


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


	vector<ZNumber> coords = res.solveLinearEquasionSystem();
	if(coords != secret){
		cout << "\n\n\n\nSecret: " << endl << secret << endl << "Result:" << endl << coords << endl << endl;
		for(const auto &m : matrix)
			cout << m << endl << endl;
		return false;
	}
	else
		return true;
}


int main(){
	uint32_t success = 0;
	for(size_t i = 0; i < 100; ++i){
		if(fullIteration())
			++success;
	}
	cout << success << endl;


}
