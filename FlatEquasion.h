#ifndef FLATEQUASION_H_INCLUDED
#define FLATEQUASION_H_INCLUDED

using namespace std;

class FlatEquasion{
	vector<int64_t> factors;

	void getMatrix(const Matrix &matrix);
public:

	FlatEquasion();
	FlatEquasion(const Matrix &matrix);

	vector<int64_t> getPolynomial() const;


	friend ostream &operator<<(ostream &o, const FlatEquasion &fe);
};

ostream &operator<<(ostream &o, const FlatEquasion &fe);

#endif // FLATEQUASION_H_INCLUDED
