#include <iostream>
#include <vector>
#include <ostream>
#include <algorithm>

#include <chrono>
#include <random>

#include "Matrix.h"
#include "FlatEquasion.h"

using namespace std;


bool checkSecret(const vector<int64_t> &secret){
	for(auto &coord : secret)
		if(coord != 0)
			return true;
	return false;
}


int main(){
	unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	mt19937 g1(seed1);
	const uint16_t N = 7, K = 3;



	vector<int64_t> secret(K);
	do{
		for(auto &coord : secret)
			coord = g1() % module;
	}while(checkSecret(secret) == false);



	vector<Matrix> matrix(K);
	for(size_t i = 0; i < K; ++i){
		matrix.at(i).resize(K, K);
		do{
			matrix.at(i).randomize();
			matrix.at(i).replaceRow(0, secret);
		}while(matrix.at(i).calcDeterminant() == 0);
		cout << matrix.at(i) << endl;
	}



	Matrix res;
	for(auto &m : matrix)
		res.insertRow(m.getFlatPolynomial());


	cout << res << endl;
	vector<int64_t> coords = res.solveLinearEquasionSystem_MatrixMethod();


	if(coords == secret)
		cout << "success" << endl;
	else
		cout << "fail: " << secret << " != " << coords << endl;


}
