#ifndef FLATEQUASION_H_INCLUDED
#define FLATEQUASION_H_INCLUDED

using namespace std;

class FlatEquasion{
	vector<ZNumber> factors;

	void getMatrix(const Matrix &matrix);
public:

	FlatEquasion();
	FlatEquasion(const Matrix &matrix);

	vector<ZNumber> getPolynomial() const;


	friend ostream &operator<<(ostream &o, const FlatEquasion &fe);
};

ostream &operator<<(ostream &o, const FlatEquasion &fe);

#endif // FLATEQUASION_H_INCLUDED
