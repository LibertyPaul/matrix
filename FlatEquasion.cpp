#include <vector>
#include <ostream>
#include <stdexcept>


#include "Matrix.h"

#include "FlatEquasion.h"

FlatEquasion::FlatEquasion(){
}

FlatEquasion::FlatEquasion(const Matrix &matrix){
	getMatrix(matrix);
}

void FlatEquasion::getMatrix(const Matrix &matrix){
	if(matrix.isSquare() == false)
		throw logic_error("Matrix is not square.");

	size_t K = matrix.getRowCount();

	factors.resize(K + 1);
	factors.at(K) = 0;

	int sign = 1;
	for(uint16_t i = 0; i < K; ++i){
		factors.at(i) = sign * matrix.getSubMatrix(0, i).calcDeterminant();
		factors.at(K) -= matrix.getNumber(0, i) * factors.at(i);
		sign = -sign;
	}
}

vector<int64_t> FlatEquasion::getPolynomial() const{
	return factors;
}


ostream &operator<<(ostream &o, const FlatEquasion &fe){
	uint16_t K = fe.factors.size() - 1;
	for(uint16_t i = 0; i < K; ++i)
		o << abs(fe.factors.at(i)) << " * X" << i + 1 << (fe.factors.at(i + 1) >= 0 ? " + " : " - ");
	o << abs(fe.factors.at(K)) << " = 0";
	return o;
}

