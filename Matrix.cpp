#include <vector>
#include <stdexcept>
#include <istream>
#include <ostream>
#include <sstream>
#include <chrono>
#include <random>
#include <initializer_list>

#include <iostream>

using namespace std;
#include "ZNumber.hpp"
#include "Matrix.hpp"

Matrix::Matrix(){
}

Matrix::Matrix(uint32_t rowNumber, uint32_t colNumber){
	resize(rowNumber, colNumber);
}

Matrix::Matrix(const vector<vector<ZNumber>> &matrix){
	for(auto i = matrix.begin(); i != matrix.end() - 1; ++i)
		if(i->size() != (i + 1)->size())
			throw logic_error("Row size does not match");
	this->matrix = matrix;
}

Matrix::Matrix(const initializer_list<vector<ZNumber>> &initList): matrix(initList){
	for(auto i = matrix.begin(); i != matrix.end() - 1; ++i)
		if(i->size() != (i + 1)->size())
			throw logic_error("Row size does not match");
}



void Matrix::resize(uint32_t rowNumber, uint32_t colNumber){
	matrix.resize(rowNumber);
	for(auto &row : matrix)
		row.resize(colNumber);
}

void Matrix::randomize(){
	unsigned seed1 = std::chrono::system_clock::now().time_since_epoch().count();
	mt19937 g1(seed1);
	for(auto &row : matrix)
		for(auto &coord : row)
			coord = g1();

}

void Matrix::insertRow(const vector<ZNumber> &row){
	if(matrix.empty() == false)
		if(matrix.front().size() != row.size())
			throw logic_error("row size doesn't match");

	vector<ZNumber> newRow;
	newRow.reserve(row.size());
	for(auto n : row)
		newRow.push_back(n);

	matrix.push_back(move(newRow));
}

vector<ZNumber> &Matrix::getRow(uint32_t rowNumber){
	return matrix.at(rowNumber);
}

const vector<ZNumber> &Matrix::getRow(uint32_t rowNumber) const{
	return matrix.at(rowNumber);
}

void Matrix::replaceRow(uint32_t rowNumber, const vector<ZNumber> &row){
	if(matrix.empty())
		throw runtime_error("Matrix is empty");

	if(matrix.size() <= rowNumber)
		throw logic_error("Row number is too high");

	if(rowNumber > 0 && matrix.at(0).size() != row.size())
		throw logic_error("row size doesn't match");

	if(rowNumber < matrix.size() - 1 && matrix.back().size() != row.size())
		throw logic_error("row size doesn't match");

	matrix.at(rowNumber) = row;
}

ZNumber &Matrix::getValue(uint32_t row, uint32_t col){
	return matrix.at(row).at(col);
}


uint32_t Matrix::getRowCount() const{
	return matrix.size();
}


uint32_t Matrix::getColumnCount() const{
	if(matrix.empty())
		return 0;
	return matrix.front().size();
}


bool Matrix::isSquare() const{
	if(matrix.empty())
		throw runtime_error("Matrix is empty");
	return matrix.size() == matrix.front().size();
}

void Matrix::transpose(){
	vector<vector<ZNumber>> mCopy = matrix;
	matrix.clear();
	matrix.resize(mCopy.front().size());
	for(auto &row : matrix)
		row.resize(mCopy.size());

	for(uint32_t i = 0; i < mCopy.size(); ++i)
		for(uint32_t j = 0; j < mCopy.at(i).size(); ++j)
			matrix.at(j).at(i) = mCopy.at(i).at(j);
}

void Matrix::replaceCol(uint32_t colNumber, const vector<ZNumber> &col){
	if(matrix.empty())
		throw runtime_error("Matrix is empty");
	if(matrix.size() != col.size())
		throw logic_error("col size does not match");

	for(uint32_t i = 0; i < matrix.size(); ++i)
		matrix.at(i).at(colNumber) = col.at(i);
}

vector<ZNumber> Matrix::getCol(uint32_t colNumber) const{
	if(matrix.empty())
		throw runtime_error("Matrix is empty");
	if(colNumber >= matrix.front().size())
		throw runtime_error("colNumber is too high");

	vector<ZNumber> col(matrix.size());
	for(uint32_t i = 0; i < matrix.size(); ++i)
		col.at(i) = matrix.at(i).at(colNumber);
	return col;
}


Matrix Matrix::getSubMatrix(uint32_t rowNumber, uint32_t colNumber) const{
	uint16_t rowCount = getRowCount();
	uint16_t colCount = getColumnCount();
	if(colNumber >= colCount)
		throw logic_error("colNumber is too high");
	if(rowNumber >= rowCount)
		throw logic_error("rowNumber is too high");

	Matrix newMatrix;

	for(uint16_t row = 0; row < rowCount; ++row){
		if(row != rowNumber){
			vector<ZNumber> currentRow;
			currentRow.reserve(rowCount - 1);
			for(uint16_t col = 0; col < colCount; ++col)
				if(col != colNumber)
					currentRow.push_back(matrix.at(row).at(col));
			newMatrix.insertRow(currentRow);
		}
	}
	return newMatrix;
}

ZNumber Matrix::calcDeterminant() const{
	if(matrix.empty())
		throw runtime_error("Matrix is empty");
	if(isSquare() == false)
		throw logic_error("Matrix is not square");

	return calcDeterminant_Gauss();
}

Matrix Matrix::getRowEchelonForm() const{
	Matrix res(*this);
	uint32_t K = res.getRowCount();
	for(uint32_t col = 0; col < K - 1; ++col){
		vector<ZNumber> subtrahend = res.getRow(col);
		for(uint32_t row = col + 1; row < K; ++row)
			res.matrix.at(row) -= subtrahend * res.matrix.at(row).at(col) / subtrahend.at(col);
	}
	return res;
}


ZNumber Matrix::calcDeterminant_Laplace() const{
	switch(getRowCount()){
		case 1: return matrix.at(0).at(0);
		case 2: return matrix.at(0).at(0) * matrix.at(1).at(1) - matrix.at(0).at(1) * matrix.at(1).at(0);

		default: {
			ZNumber res(0);
			int sign = 1;
			uint16_t colCount = getColumnCount();
			for(uint16_t col = 0; col < colCount; ++col){
				res += sign * matrix.front().at(col) * getSubMatrix(0, col).calcDeterminant();//heavy call
				sign = -sign;
			}
			return res;
		}
	}
}


ZNumber Matrix::calcDeterminant_Gauss() const{
	Matrix mCopy = this->getRowEchelonForm();
	ZNumber result = 1;
	uint32_t K = mCopy.getRowCount();
	for(uint32_t i = 0; i < K; ++i)
		result *= mCopy.matrix.at(i).at(i);

	return result;
}


vector<ZNumber> Matrix::solveLinearEquasionSystem_Gauss() const{
	Matrix mCopy = this->getRowEchelonForm();
	cout << mCopy << endl;
	uint32_t K = mCopy.getRowCount();
	for(uint32_t col = K - 1; col >= 1; --col){
		vector<ZNumber> subtrahend = mCopy.getRow(col);
		for(int64_t row = col - 1; row >= 0; --row)
			mCopy.getRow(row) -= subtrahend * mCopy.getValue(row, col) / subtrahend.at(col);
	}
	cout << mCopy << endl;

	vector<ZNumber> res(K);
	for(uint32_t i = 0; i < K; ++i)
		res.at(i) = mCopy.getValue(i, i) / mCopy.getValue(i, K);

	return res;
}


vector<ZNumber> Matrix::solveLinearEquasionSystem_Kramer() const{
	if(matrix.empty())
		throw runtime_error("Matrix is empty");
	if(matrix.size() < getColumnCount() - 1)
		throw logic_error("Not enough equasions");

	vector<ZNumber> coords(getColumnCount() - 1);

	Matrix mCopy(*this);
	mCopy.resize(this->getColumnCount() - 1, this->getColumnCount() - 1);//отбрасываем лишние уравнения

	ZNumber dividerDet = mCopy.calcDeterminant();
	if(dividerDet == 0)
		throw logic_error("divider == 0");



	vector<ZNumber> lastCol = this->getCol(this->getColumnCount() - 1);
	lastCol.resize(mCopy.getRowCount());
	for(auto &lastN : lastCol)
		lastN = -lastN;

	for(uint32_t i = 0; i < mCopy.getColumnCount(); ++i){
		vector<ZNumber> temp = mCopy.getCol(i);
		mCopy.replaceCol(i, lastCol);
		coords.at(i) = mCopy.calcDeterminant() / dividerDet;
		mCopy.replaceCol(i, temp);
	}
	return coords;
}


vector<ZNumber> Matrix::solveLinearEquasionSystem_MatrixMethod() const{
	if(matrix.empty())
		throw runtime_error("Matrix is empty");

	uint32_t K = getColumnCount() - 1;
	if(matrix.size() < K)
		throw logic_error("Not enough equasions");

	vector<ZNumber> coords(K);
	vector<ZNumber> lastCol = this->getCol(K);

	Matrix mCopy(*this);
	mCopy.resize(K, K);
	ZNumber mainDeterminant = mCopy.calcDeterminant();
	if(mainDeterminant == 0)
		throw logic_error("Determinant == 0");


	Matrix cofactors;
	for(uint32_t rowNumber = 0; rowNumber < K; ++rowNumber){
		vector<ZNumber> cofactorRow(K);
		for(uint16_t colNumber = 0; colNumber < K; ++colNumber){
			int sign = 1;
			if((rowNumber + colNumber) % 2 != 0)
				sign = -1;
			cofactorRow.at(colNumber) = mCopy.getSubMatrix(rowNumber, colNumber).calcDeterminant() * sign;
		}
		cofactors.insertRow(cofactorRow);
	}

	cofactors.transpose();

	Matrix lastColMatrix;
	lastColMatrix.insertRow(lastCol);
	lastColMatrix.transpose();

	Matrix result = (cofactors * lastColMatrix) / mainDeterminant;

	result *= -1;

	return result.getCol(0);
}


vector<ZNumber> Matrix::getFlatPolynomial() const{
	if(isSquare() == false)
		throw logic_error("Matrix is not square.");

	size_t K = getRowCount();
	Matrix mCopy(*this);
	for(size_t col = 0; col < K; ++col)
		for(size_t row = 1; row < K; ++row)
			mCopy.matrix.at(row).at(col) -= mCopy.matrix.at(0).at(col);

	vector<ZNumber> factors(K + 1);
	factors.back() = 0;

	int sign = 1;
	for(uint32_t i = 0; i < K; ++i){
		factors.at(i) = sign * mCopy.getSubMatrix(0, i).calcDeterminant();
		factors.back() -= mCopy.getValue(0, i) * factors.at(i);//??sign *
		sign = -sign;
	}
	return factors;
}




Matrix Matrix::operator*(const Matrix &m) const{
	Matrix result;
	for(uint32_t rowNumber = 0; rowNumber < this->getRowCount(); ++rowNumber){
		vector<ZNumber> row(m.getColumnCount());
		for(uint32_t colNumber = 0; colNumber < m.getColumnCount(); ++colNumber)
			row.at(colNumber) = sum(this->getRow(rowNumber) * m.getCol(colNumber));
		result.insertRow(row);
	}
	return result;
}

Matrix Matrix::operator*=(const Matrix &m){
	*this = *this * m;
	return *this;
}


Matrix Matrix::operator*(const ZNumber &val) const{
	Matrix mCopy(*this);
	for(auto &row : mCopy.matrix)
		for(auto &coord : row)
			coord = val * coord;
	return mCopy;
}

Matrix Matrix::operator/(const ZNumber &val) const{
	Matrix mCopy(*this);
	for(auto &row : mCopy.matrix)
		for(auto &coord : row)
			coord = coord / val;
	return mCopy;
}

Matrix Matrix::operator*=(const ZNumber &val){
	*this = *this * val;
	return *this;
}

Matrix Matrix::operator/=(const ZNumber &val){
	*this = *this / val;
	return *this;
}


const Matrix &Matrix::operator=(const Matrix &matrix){
	this->matrix = matrix.matrix;
	return *this;
}

Matrix &Matrix::operator=(const vector<vector<ZNumber>> &matrix){
	this->matrix = matrix;
	return *this;
}


Matrix Matrix::operator+(const ZNumber &val) const{
	Matrix t(*this);
	for(auto &row : t.matrix)
		for(auto &zn : row)
			zn += val;
	return t;
}


Matrix Matrix::operator-(const ZNumber &val)const{
	return Matrix(*this) + (-val);
}


Matrix Matrix::operator+=(const ZNumber &val){
	*this = *this + val;
	return *this;
}


Matrix Matrix::operator-=(const ZNumber &val){
	*this += -val;
	return *this;
}


ostream &operator<<(ostream &o, const Matrix &matrix){
	for(auto &row : matrix.matrix)
		o << row << endl;
	return o;
}










