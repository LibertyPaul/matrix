using namespace std;

#include "Base16.hpp"


char Base16::getKey(const uint8_t i) const{
	return keys.at(i);
}

uint8_t Base16::getCode(const char c) const{
	size_t pos = keys.find(c);
	if(pos == string::npos)
		throw runtime_error("Invalid base16 character");

	return pos;
}

pair<char, char> Base16::encode(const uint8_t src) const{
	uint8_t greater = (src & 0xF0) >> 4;
	uint8_t lower = src & 0x0F;

	return pair<char, char>(getKey(greater), getKey(lower));
}


uint8_t Base16::decode(const pair<char, char> &src) const{
	uint8_t res = 0;
	res |= getCode(src.first) << 4;
	res |= getCode(src.second);

	return res;
}


string Base16::encode(const Buffer &src) const{
	string res;
	for(size_t i = 0; i < src.getSize(); ++i){
		pair<char, char> keys = encode(src[i]);

		res += keys.first;
		res += keys.second;
	}
	return res;
}




Buffer Base16::decode(const string &src) const{
	if(src.length() % 2)
		throw runtime_error("src length is not even");

	Buffer res(src.length() / 2);

	for(size_t i = 0; i < src.length(); i += 2){
		char greater = src.at(i);
		char lower = src.at(i + 1);

		pair<char, char> current(greater, lower);

		uint8_t val = decode(current);
		res[i / 2] = val;
	}

	return res;
}



