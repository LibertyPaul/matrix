#include <stdexcept>

using namespace std;
#include "ClientDataPart.hpp"
const uint32_t ClientDataPart::magic;

ClientDataPart::ClientDataPart(const Matrix &matrix): linearEquasions(matrix){}
ClientDataPart::ClientDataPart(Matrix &&matrix): linearEquasions(matrix){}

ClientDataPart::ClientDataPart(const Buffer &binaryContainer): linearEquasions(){
	if(binaryContainer.getSize() < additionalInfoSize)
		throw runtime_error("Buffer size is less than additionalInfoSize");

	uint32_t pos = 0;
	if(binaryContainer.get<uint32_t>(pos++) != magic)
		throw runtime_error("Magic number does not match");


	uint32_t rowCount = binaryContainer.get<uint32_t>(pos++);
	uint32_t colCount = binaryContainer.get<uint32_t>(pos++);

	if(binaryContainer.getSize() < additionalInfoSize + sizeof(uint32_t) * colCount * rowCount)
		throw runtime_error("Container is broken...");

	linearEquasions.resize(rowCount, colCount);
	for(uint32_t row = 0; row < rowCount; ++row)
		for(uint32_t col = 0; col < colCount; ++col)
			linearEquasions.get(row, col) = binaryContainer.get<uint32_t>(pos++);
}


ClientDataPart::ClientDataPart(const ClientDataPart &cdp): linearEquasions(cdp.linearEquasions){}
ClientDataPart::ClientDataPart(ClientDataPart &&cdp): linearEquasions(move(cdp.linearEquasions)){}


Buffer ClientDataPart::toBinaryContainer() const{
	uint32_t rowCount = linearEquasions.getRowCount();
	uint32_t colCount = linearEquasions.getColumnCount();

	uint64_t bufferSize = additionalInfoSize + sizeof(uint32_t) * colCount * rowCount;
	//структура контейнера: количество уравнений, размер уравнений, коэффициенты.
	Buffer result(bufferSize);
	result.write<uint32_t>(magic);
	result.write<uint32_t>(rowCount);
	result.write<uint32_t>(colCount);


	for(uint32_t row = 0; row < rowCount; ++row)
		for(uint32_t col = 0; col < colCount; ++col)
			result.write<uint32_t>(linearEquasions.get(row, col).getValue());

	return result;
}


const Matrix &ClientDataPart::getLinearEquasions() const{
	return linearEquasions;
}
