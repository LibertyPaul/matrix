#include <stdexcept>
#include <chrono>
#include <random>



using namespace std;
#include "Matrix.hpp"

Matrix::Matrix(): matrix(){
}

Matrix::Matrix(const Matrix &matrix): matrix(matrix.matrix){
}

Matrix::Matrix(Matrix &&matrix): matrix(move(matrix.matrix)){
}

Matrix::Matrix(uint32_t rowNumber, uint32_t colNumber): matrix(){
	resize(rowNumber, colNumber);
}

Matrix::Matrix(const vector<vector<ZNumber>> &matrix): matrix(){
	uint32_t rowCount = matrix.size();
	uint32_t colCount;
	if(rowCount == 0)
		colCount = 0;//0 строк -> 0 столбцов
	else
		colCount = matrix.front().size();


	for(auto it = matrix.cbegin() + 1; it != matrix.cend(); ++it)//проверка на равенство длинн строк
		if(it->size() != colCount)
			throw logic_error("Row size differs");


	resize(rowCount, colCount);

	for(uint32_t row = 0; row < rowCount; ++row)
		for(uint32_t col = 0; col < colCount; ++col)
			get(row, col) = matrix.at(row).at(col);
}
/*
Matrix::Matrix(const initializer_list<vector<ZNumber>> &initList): matrix(initList){
	for(auto i = matrix.begin(); i != matrix.end() - 1; ++i)
		if(i->size() != (i + 1)->size())
			throw logic_error("Row size does not match");
}
*/


void Matrix::resize(uint32_t rowNumber, uint32_t colNumber){
	matrix.resize(rowNumber);
	for(auto &row : matrix)
		row.resize(colNumber);
}


uint32_t Matrix::getRowCount() const{
	return matrix.size();
}


uint32_t Matrix::getColumnCount() const{
	if(matrix.empty())
		return 0;
	return matrix.front().size();
}

ZNumber &Matrix::get(uint32_t row, uint32_t col){
	if(row >= getRowCount() || col >= getColumnCount())
		throw runtime_error("out of matrix");
	return matrix.at(row).at(col);
}

const ZNumber &Matrix::get(uint32_t row, uint32_t col) const{
	if(row >= getRowCount() || col >= getColumnCount())
		throw runtime_error("out of matrix");
	return matrix.at(row).at(col);
}


vector<ZNumber> Matrix::getRow(uint32_t rowNumber) const{
	uint32_t colCount = getColumnCount();
	vector<ZNumber> result(colCount);

	for(uint32_t col = 0; col < colCount; ++col)
		result.at(col) = get(rowNumber, col);

	return result;
}


vector<ZNumber> Matrix::getCol(uint32_t colNumber) const{
	uint32_t rowCount = getRowCount();
	vector<ZNumber> result(rowCount);

	for(uint32_t i = 0; i < rowCount; ++i)
		result.at(i) = get(i, colNumber);

	return result;
}


void Matrix::randomize(){
	unsigned seed1 = chrono::system_clock::now().time_since_epoch().count();
	mt19937 g1(seed1);
	for(uint32_t row = 0; row < getRowCount(); ++row)
		for(uint32_t col = 0; col < getColumnCount(); ++col)
			get(row, col) = g1();
}


void Matrix::replaceRow(uint32_t rowNumber, const vector<ZNumber> &row){
	uint32_t rowCount = getRowCount();
	uint32_t colCount = getColumnCount();

	if(rowNumber >= rowCount)
		throw logic_error("rowNumber is greater than max row index");

	if(matrix.empty() == false && colCount != row.size())
		throw logic_error("Row size doesn't match");

	for(uint32_t col = 0; col < colCount; ++col)
		get(rowNumber, col) = row.at(col);
}

void Matrix::replaceCol(uint32_t colNumber, const vector<ZNumber> &newCol){
	uint32_t rowCount = getRowCount();
	uint32_t colCount = getColumnCount();

	if(colNumber >= colCount)
		throw logic_error("colNumber is greater than max col index");

	if(matrix.empty() == false && rowCount != newCol.size())
		throw logic_error("col size does not match");


	for(uint32_t row = 0; row < rowCount; ++row)
		get(row, colNumber) = newCol.at(row);
}

void Matrix::insertRow(const vector<ZNumber> &newRow, uint32_t rowNumber){
	uint32_t rowCount = getRowCount();
	uint32_t colCount = getColumnCount();

	if(matrix.empty() == false && colCount != newRow.size())
		throw logic_error("row size doesn't match");

	if(rowNumber > rowCount)
		throw logic_error("rowNumber is more than rowCount");


	resize(rowCount + 1, newRow.size());
	rowCount = getRowCount();
	uint32_t lastRowIndex = rowCount - 1;

	for(uint32_t row = lastRowIndex; row > rowNumber + 1; --row)//сдвигаем все строки после rowNumber на 1 позицию вниз
		replaceRow(row, getRow(row - 1));
	replaceRow(rowNumber, newRow);
}

void Matrix::insertCol(const vector<ZNumber> &newCol, uint32_t colNumber){
	uint32_t rowCount = getRowCount();
	uint32_t colCount = getColumnCount();

	if(matrix.empty() == false && rowCount != newCol.size())
		throw logic_error("col size doesn't match");

	if(colNumber > colCount)
		throw logic_error("colNumber is more than colCount");

	resize(newCol.size(), colCount + 1);
	colCount = getColumnCount();
	uint32_t lastColIndex = colCount - 1;

	for(uint32_t col = lastColIndex; col > colNumber + 1; --col)//сдвигаем все строки после rowNumber на 1 позицию вниз
		replaceRow(col, getCol(col - 1));
	replaceRow(colNumber, newCol);
}

void Matrix::pushRowBack(const vector<ZNumber> &newRow){
	insertRow(newRow, getRowCount());
}

void Matrix::pushColBack(const vector<ZNumber> &newCol){
	insertCol(newCol, getColumnCount());
}


bool Matrix::isSquare() const{
	return getRowCount() == getColumnCount();
}

void Matrix::transposeOnPlace(){
	uint32_t oldRowCount = getRowCount();
	uint32_t newColCount = oldRowCount;
	uint32_t oldColCount = getColumnCount();
	uint32_t newRowCount = oldColCount;
	uint32_t maxSideSize = max(oldRowCount, oldColCount);//увеличиваем матрицу до квадратной формы
	resize(maxSideSize, maxSideSize);//если матрица была квадратной, то ничего не изменится

	uint32_t minSideSize = min(oldRowCount, oldColCount);

    for(uint32_t row = 0; row < maxSideSize; ++row)
		if(row < minSideSize)
			for(uint32_t col = 0; col < maxSideSize / 2; ++col)
				swap(get(row, col), get(col ,row));
		else
			for(uint32_t col = 0; col < min(minSideSize, maxSideSize / 2); ++col)
				swap(get(row, col), get(col ,row));
	resize(newRowCount, newColCount);
}

void Matrix::transposeWithCopy(){
	uint32_t oldRowCount = getRowCount();
	uint32_t newColCount = oldRowCount;
	uint32_t oldColCount = getColumnCount();
	uint32_t newRowCount = oldColCount;

	vector<vector<ZNumber>> matrixCopy(newRowCount);
	for(auto &row : matrixCopy)
		row.resize(newColCount);//A * B -> B * A

	for(uint32_t row = 0; row < oldRowCount; ++row)
		for(uint32_t col = 0; col < oldColCount; ++col)
			matrixCopy.at(col).at(row) = get(row, col);

	resize(newColCount, newRowCount);
	for(uint32_t row = 0; row < newRowCount; ++row)
		for(uint32_t col = 0; col < newColCount; ++col)
			get(row, col) = matrixCopy.at(row).at(col);
}

void Matrix::transpose(){
	int64_t rowCount = getRowCount();//int64_t для возможности вычитания большего из меньшего
	int64_t colCount = getColumnCount();

	if(min(rowCount, colCount) < abs(rowCount - colCount))
		transposeWithCopy();
	else
		transposeOnPlace();

}



void Matrix::toRowEchelonForm(){
	uint32_t K = getRowCount();

	//make sure that all number on main diagonal not zero
	for(uint32_t i = 0; i < K; ++i){
		if(get(i, i) == 0){//finding row with non zero value in column #i
			for(uint32_t row = 0; row < K; ++row)
				if(get(row, i) != 0){
					replaceRow(i, getRow(i) + getRow(row));
					break;
				}
			//if(getValue(i, i) == 0)//still == 0 => all numbers in column is zeroes
		}
	}

	for(uint32_t col = 0; col < K - 1; ++col){
		vector<ZNumber> subtrahend = getRow(col);
		if(subtrahend.at(col) == 0)
			continue;//all numbers in column == 0, nothing to change

		for(uint32_t row = col + 1; row < K; ++row)
			replaceRow(row, getRow(row) - (subtrahend * get(row, col) / subtrahend.at(col)));
	}
}



ZNumber Matrix::calcDeterminant() const{
	if(isSquare() == false)
		throw logic_error("Matrix is not square");

	Matrix mCopy(*this);
	mCopy.toRowEchelonForm();

	ZNumber result = 1;
	uint32_t K = mCopy.getRowCount();
	for(uint32_t i = 0; i < K; ++i)
		result *= mCopy.get(i, i);

	return result;
}


vector<ZNumber> Matrix::solveLinearEquasionSystem() const{
	uint32_t K = this->getRowCount();

	if(this->getColumnCount() > K + 1)
		throw logic_error("Equasion system is redundant: \n" + this->toString());
	if(this->getColumnCount() < K + 1)
		throw logic_error("Equasion system is insufficient: \n" + this->toString());



	Matrix t(*this);
	t.resize(K, K);
	if(t.calcDeterminant() == 0)
		throw logic_error("Equasion system has no solution(determinant == 0): \n" + t.toString());




	Matrix mCopy(*this);
	mCopy.toRowEchelonForm();

	for(uint32_t col = K - 1; col >= 1; --col){
		vector<ZNumber> subtrahend = mCopy.getRow(col);
		if(subtrahend.at(col) == 0)
			continue;
		for(int64_t row = col - 1; row >= 0; --row)
			mCopy.replaceRow(row, mCopy.getRow(row) - (subtrahend * mCopy.get(row, col) / subtrahend.at(col)));
	}


	vector<ZNumber> res(K);
	for(uint32_t i = 0; i < K; ++i)
		res.at(i) = -(mCopy.get(i, K) / mCopy.get(i, i));


	return res;
}




vector<ZNumber> Matrix::getFlatPolynomial() const{
	if(isSquare() == false)
		throw logic_error("Matrix is not square.");

	uint32_t K = getRowCount();
	Matrix mCopy(*this);

	vector<ZNumber> polynomial(K + 1);
	for(uint32_t i = 0; i < K; ++i){
		Matrix mCopy(*this);
		vector<ZNumber> replacement(K, 1);//1 1 1 1 1 1 1 1... k times
		mCopy.replaceCol(i, replacement);
		polynomial.at(i) = mCopy.calcDeterminant();
	}

	polynomial.back() = -this->calcDeterminant();

	return polynomial;
}






Matrix Matrix::operator*(const Matrix &m) const{
	Matrix result;
	for(uint32_t rowNumber = 0; rowNumber < this->getRowCount(); ++rowNumber){
		vector<ZNumber> row(m.getColumnCount());
		for(uint32_t colNumber = 0; colNumber < m.getColumnCount(); ++colNumber)
			row.at(colNumber) = sum(this->getRow(rowNumber) * m.getCol(colNumber));
		result.pushRowBack(row);
	}
	return result;
}

Matrix Matrix::operator*=(const Matrix &m){
	*this = *this * m;
	return *this;
}


Matrix Matrix::operator*(const ZNumber &val) const{
	Matrix mCopy(*this);
	uint32_t rowCount = mCopy.getRowCount();
	uint32_t colCount = mCopy.getColumnCount();

	for(uint32_t row = 0; row < rowCount; ++row)
		for(uint32_t col = 0; col < colCount; ++col)
			mCopy.get(row, col) *= val;

	return mCopy;
}

Matrix Matrix::operator/(const ZNumber &val) const{
	Matrix mCopy(*this);
	uint32_t rowCount = mCopy.getRowCount();
	uint32_t colCount = mCopy.getColumnCount();

	for(uint32_t row = 0; row < rowCount; ++row)
		for(uint32_t col = 0; col < colCount; ++col)
			mCopy.get(row, col) /= val;

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
	*this = move(Matrix(matrix));
	return *this;
}

const Matrix &Matrix::operator=(Matrix &&matrix){
	this->matrix = move(matrix.matrix);
	return *this;
}

const Matrix &Matrix::operator=(const vector<vector<ZNumber>> &matrix){
	*this = move(Matrix(matrix));
	return *this;
}


Matrix Matrix::operator+(const ZNumber &val) const{
	Matrix t(*this);
	uint32_t rowCount = t.getRowCount();
	uint32_t colCount = t.getColumnCount();

	for(uint32_t row = 0; row < rowCount; ++row)
		for(uint32_t col = 0; col < colCount; ++col)
			t.get(row, col) += val;
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



string Matrix::toString() const{
	string result;
	uint32_t rowCount = getRowCount();
	uint32_t colCount = getColumnCount();

	for(uint32_t row = 0; row < rowCount; ++row){
		for(uint32_t col = 0; col < colCount; ++col){
			result += get(row, col).toString();
			result += ' ';
		}
		result += '\n';
	}
	return result;
}










