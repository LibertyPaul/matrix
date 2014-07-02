#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED


using namespace std;

const uint64_t module = 42;


class Matrix{
	vector<vector<int64_t>> matrix;
public:
	Matrix();
	Matrix(uint16_t rowNumber, uint16_t colNumber);
	Matrix(const vector<vector<int64_t>> &matrix);

	void normalize();// % module

	void resize(uint16_t rowNumber, uint16_t colNumber);
	void randomize(int64_t maxValue = module);

	void insertRow(const vector<int64_t> &row);
	vector<int64_t> getCol(uint16_t colNumber) const;
	vector<int64_t> getRow(uint16_t rowNumber) const;
	void replaceCol(uint16_t colNumber, const vector<int64_t> &col);
	void replaceRow(uint16_t rowNumber, const vector<int64_t> &row);
	int64_t getNumber(uint16_t row, uint16_t col) const;
	uint16_t getRowCount() const;
	uint16_t getColumnCount() const;
	bool isSquare() const;
	void transpose();

	Matrix getSubMatrix(uint16_t rowNumber, uint16_t colNumber) const;
	int64_t calcDeterminant() const;
	vector<int64_t> solveLinearEquasionSystem_Kramer() const;
	vector<int64_t> solveLinearEquasionSystem_MatrixMethod() const;

	vector<int64_t> getFlatPolynomial() const;//уравнение плоскости

	Matrix operator*(const Matrix &matrix) const;//N^3. надо бы переписать под алгоритм Штрассена
	Matrix operator*=(const Matrix &m);
	Matrix operator*(const int64_t val) const;
	Matrix operator/(const int64_t val) const;
	Matrix operator*=(const int64_t val);
	Matrix operator/=(const int64_t val);


	friend ostream &operator<<(ostream &o, const Matrix &matrix);
};

ostream &operator<<(ostream &o, const Matrix &matrix);



ostream &operator<<(ostream &o, const vector<int64_t> &v);
vector<int64_t> operator*(const vector<int64_t> &v1, const vector<int64_t> &v2);
int64_t sum(const vector<int64_t> &v);










#endif // MATRIX_H_INCLUDED
