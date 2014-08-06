#ifndef DATASEPARATOR_HPP_INCLUDED
#define DATASEPARATOR_HPP_INCLUDED

class DataSeparator{
	uint32_t K;
	uint32_t N;

public:
	DataSeparator(uint32_t K, uint32_t N);

	vector<DataPart> separate(const vector<uint8_t> &data) const;
	vector<uint8_t> restore(const vector<DataPart> &parts) const;

};


#endif // DATASEPARATOR_HPP_INCLUDED
