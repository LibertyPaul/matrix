#ifndef MATRIX_HPP_INCLUDED
#define MATRIX_HPP_INCLUDED

class Matrix{
	vector<vector<ZNumber>> matrix;

public:
	Matrix();
	Matrix(const Matrix &matrix);
	Matrix(Matrix &&matrix);
	Matrix(uint32_t rowNumber, uint32_t colNumber);
	Matrix(const vector<vector<ZNumber>> &matrix);
	Matrix(const initializer_list<vector<ZNumber>> &initList);



	void resize(uint32_t rowNumber, uint32_t colNumber);
	void randomize();

	void insertRow(const vector<ZNumber> &row);
	vector<ZNumber> getCol(uint32_t colNumber) const;
	vector<ZNumber> &getRow(uint32_t rowNumber);
	const vector<ZNumber> &getRow(uint32_t rowNumber) const;
	void replaceCol(uint32_t colNumber, const vector<ZNumber> &col);
	void replaceRow(uint32_t rowNumber, const vector<ZNumber> &row);
	ZNumber &getValue(uint32_t row, uint32_t col);
	uint32_t getRowCount() const;
	uint32_t getColumnCount() const;
	bool isSquare() const;
	void transpose();

	void toRowEchelonForm();//приведение к ступенчатому виду
	Matrix getSubMatrix(uint32_t rowNumber, uint32_t colNumber) const;
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
	Matrix &operator=(const vector<vector<ZNumber>> &matrix);



	string toString() const;
	friend ostream &operator<<(ostream &o, const Matrix &matrix);
};

ostream &operator<<(ostream &o, const Matrix &matrix);





#endif // MATRIX_HPP_INCLUDED
