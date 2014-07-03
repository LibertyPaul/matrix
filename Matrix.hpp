#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

class Matrix{
	vector<vector<ZNumber>> matrix;
public:
	Matrix();
	Matrix(uint16_t rowNumber, uint16_t colNumber);
	Matrix(const vector<vector<ZNumber>> &matrix);
	Matrix(const initializer_list<vector<ZNumber>> &initList);


	void resize(uint16_t rowNumber, uint16_t colNumber);
	void randomize();

	void insertRow(const vector<ZNumber> &row);
	vector<ZNumber> getCol(uint16_t colNumber) const;
	vector<ZNumber> getRow(uint16_t rowNumber) const;
	void replaceCol(uint16_t colNumber, const vector<ZNumber> &col);
	void replaceRow(uint16_t rowNumber, const vector<ZNumber> &row);
	ZNumber getNumber(uint16_t row, uint16_t col) const;
	uint16_t getRowCount() const;
	uint16_t getColumnCount() const;
	bool isSquare() const;
	void transpose();

	Matrix getSubMatrix(uint16_t rowNumber, uint16_t colNumber) const;
	ZNumber calcDeterminant() const;
	vector<ZNumber> solveLinearEquasionSystem_Kramer() const;
	vector<ZNumber> solveLinearEquasionSystem_MatrixMethod() const;

	vector<ZNumber> getFlatPolynomial() const;//уравнение плоскости

	Matrix operator*(const Matrix &matrix) const;//N^3. надо бы переписать под алгоритм Штрассена
	Matrix operator*=(const Matrix &m);
	Matrix operator*(const ZNumber val) const;
	Matrix operator/(const ZNumber val) const;
	Matrix operator*=(const ZNumber val);
	Matrix operator/=(const ZNumber val);


	const Matrix &operator=(const Matrix &matrix);
	const vector<vector<ZNumber>> &operator=(const vector<vector<ZNumber>> &matrix);

	friend ostream &operator<<(ostream &o, const Matrix &matrix);
};

ostream &operator<<(ostream &o, const Matrix &matrix);





#endif // MATRIX_HPP_INCLUDED
