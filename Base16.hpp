#ifndef BASE16_HPP_INCLUDED
#define BASE16_HPP_INCLUDED

#include <string>
#include "Buffer.hpp"

class Base16{
	const string keys = "0123456789ABCDEF";

	char getKey(const uint8_t i) const;
	uint8_t getCode(const char c) const;

	pair<char, char> encode(const uint8_t src) const;
	uint8_t decode(const pair<char, char> &src) const;

public:
	string encode(const Buffer &src) const;
	Buffer decode(const string &src) const;
};

#endif // BASE16_HPP_INCLUDED
