#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

#include <initializer_list>
#include <vector>
#include "ZNumber.hpp"

class Matrix{
	vector<vector<ZNumber>> matrix;


	void transposeOnPlace();//иногда, эффективнее(по памяти) транспонировать матрицу прямо на месте
	void transposeWithCopy();//иногда, эффективнее создать копию и из нее переписывать
public:
	Matrix();
	Matrix(const Matrix &matrix);
	Matrix(Matrix &&matrix);
	Matrix(uint32_t rowNumber, uint32_t colNumber);
	Matrix(const vector<vector<ZNumber>> &matrix);
	//Matrix(const initializer_list<vector<ZNumber>> &initList);//TODO переделать через get(uint32_t row, uint32_t col)


	uint32_t getRowCount() const;
	uint32_t getColumnCount() const;
	bool isSquare() const;

	void resize(uint32_t rowNumber, uint32_t colNumber);
	void randomize();

	ZNumber &get(uint32_t row, uint32_t col);
	const ZNumber &get(uint32_t row, uint32_t col) const;

	vector<ZNumber> getRow(uint32_t rowNumber) const;
	vector<ZNumber> getCol(uint32_t colNumber) const;

	void replaceRow(uint32_t rowNumber, const vector<ZNumber> &newRow);
	void replaceCol(uint32_t colNumber, const vector<ZNumber> &newCol);

	void insertRow(const vector<ZNumber> &newRow, uint32_t rowNumber);
	void insertCol(const vector<ZNumber> &newCol, uint32_t colNumber);
	void pushRowBack(const vector<ZNumber> &newRow);
	void pushColBack(const vector<ZNumber> &newCol);

	void transpose();

	void toRowEchelonForm();//приведение к ступенчатому виду
	ZNumber calcDeterminant() const;//метод Гаусса
	vector<ZNumber> solveLinearEquasionSystem() const;//метод Гаусса

	vector<ZNumber> getFlatPolynomial() const;//уравнение плоскости

	Matrix operator*(const Matrix &matrix) const;//N^3. надо бы переписать под алгоритм Штрассена
	Matrix operator*=(const Matrix &m);
	Matrix operator*(const ZNumber &val) const;
	Matrix operator/(const ZNumber &val) const;
	Matrix operator*=(const ZNumber &val);
	Matrix operator/=(const ZNumber &val);

	Matrix operator+(const ZNumber &val) const;
	Matrix operator-(const ZNumber &val) const;
	Matrix operator+=(const ZNumber &val);
	Matrix operator-=(const ZNumber &val);



	const Matrix &operator=(const Matrix &matrix);
	const Matrix &operator=(Matrix &&matrix);
	const Matrix &operator=(const vector<vector<ZNumber>> &matrix);



	string toString() const;
};






#endif // MATRIX_HPP_INCLUDED
