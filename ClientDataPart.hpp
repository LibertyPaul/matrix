#ifndef CLIENTDATAPART_HPP_INCLUDED
#define CLIENTDATAPART_HPP_INCLUDED

#include "Matrix.hpp"
#include "Buffer.hpp"

class ClientDataPart{
	static const uint32_t magic = 42424242;
	static const uint64_t additionalInfoSize = sizeof(magic) + sizeof(uint32_t) * 2;
	Matrix linearEquasions;

public:
	ClientDataPart(const Matrix &matrix);
	ClientDataPart(Matrix &&matrix);
	ClientDataPart(const Buffer &binaryContainer);

	ClientDataPart(const ClientDataPart &cdp);
	ClientDataPart(ClientDataPart &&cdp);

	Buffer toBinaryContainer() const;
	const Matrix &getLinearEquasions() const;
};

#endif // CLIENTDATAPART_HPP_INCLUDED
