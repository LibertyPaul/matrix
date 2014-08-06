#ifndef DATAPART_HPP_INCLUDED
#define DATAPART_HPP_INCLUDED

class DataPart{
	vector<vector<ZNumber>> linearEquasions;

public:
	DataPart();
	DataPart(const vector<vector<ZNumber>> &equasions);
	vector<vector<ZNumber>> &get();
	const vector<vector<ZNumber>> &get() const;
};

#endif // DATAPART_HPP_INCLUDED
