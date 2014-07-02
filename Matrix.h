#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED


using namespace std;



class Matrix{
	vector<vector<ZNumber>> matrix;
public:
	Matrix();
	Matrix(uint16_t rowNumber, uint16_t colNumber);
	Matrix(const vector<vector<ZNumber>> &matrix);


	void resize(uint16_t rowNumber, uint16_t colNumber);
	void randomize(int64_t maxValue = module);

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
	//vector<ZNumber> solveLinearEquasionSystem_MatrixMethod() const;

	vector<ZNumber> getFlatPolynomial() const;//уравнение плоскости

	Matrix operator*(const Matrix &matrix) const;//N^3. надо бы переписать под алгоритм Штрассена
	Matrix operator*=(const Matrix &m);
	Matrix operator*(const ZNumber val) const;
	Matrix operator/(const ZNumber val) const;
	Matrix operator*=(const ZNumber val);
	Matrix operator/=(const ZNumber val);


	friend ostream &operator<<(ostream &o, const Matrix &matrix);
};

ostream &operator<<(ostream &o, const Matrix &matrix);



ostream &operator<<(ostream &o, const vector<ZNumber> &v);
vector<ZNumber> operator*(const vector<ZNumber> &v1, const vector<ZNumber> &v2);
int64_t sum(const vector<ZNumber> &v);










#endif // MATRIX_H_INCLUDED
