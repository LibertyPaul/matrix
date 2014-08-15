#include <cstring>
#include <stdexcept>

using namespace std;
#include "Buffer.hpp"

Buffer::Buffer(): size(0), buffer(nullptr), readPos(0), writePos(0){}
Buffer::Buffer(uint64_t size): size(size), buffer(new uint8_t[size]), readPos(0), writePos(0){}

Buffer::Buffer(const string &src): size(src.length()), buffer(new uint8_t[size]), readPos(0), writePos(0){
	for(uint64_t i = 0; i < size; ++i)
		write<char>(src.at(i));
	dropPointers();
}

Buffer::Buffer(const Buffer &buffer): size(buffer.getSize()), buffer(new uint8_t[size]), readPos(buffer.readPos), writePos(buffer.writePos){
	memcpy(getPtr(), buffer.getPtr(), getSize());
}

Buffer::Buffer(Buffer &&buffer): size(buffer.getSize()), buffer(move(buffer.buffer)), readPos(buffer.readPos), writePos(buffer.writePos){}


const Buffer &Buffer::operator=(Buffer &&buffer){
	this->buffer = move(buffer.buffer);
	this->size = buffer.getSize();
	this->readPos = buffer.readPos;
	this->writePos = buffer.writePos;

	return *this;
}

const Buffer &Buffer::operator=(const Buffer &buffer){
	Buffer b(buffer);
	return *this = move(b);
}

uint8_t *Buffer::getPtr(){
	return buffer.get();
}

const uint8_t *Buffer::getPtr() const{
	return buffer.get();
}


void Buffer::lowLevelWrite(const void *data, uint64_t length, uint64_t from){
	if(getSize() - from + 1 < length)
		throw logic_error("Buffer out of range");

	memcpy(getPtr() + from, data, length);
}

void Buffer::lowLevelRead(void *dst, uint64_t length, uint64_t from) const{
	if(getSize() - from + 1 < length)
		throw logic_error("Buffer out of range");

	memcpy(dst, getPtr() + from, length);
}



bool Buffer::operator==(const Buffer &buffer) const{
	if(this->getSize() != buffer.getSize())
		return false;

	for(uint64_t i = 0; i < this->getSize(); ++i)
		if(this->get(i) != buffer.get(i))
			return false;

	return true;
}

void Buffer::fill(uint8_t value){
	for(uint64_t pos = 0; pos < size; ++pos)
		get(pos) = value;
}

void Buffer::fill(const function<uint8_t()> &getValue){
	for(uint64_t pos = 0; pos < size; ++pos)
		get(pos) = getValue();
}


void Buffer::append(const Buffer &buffer){
	uint64_t sumSize = this->getSize() + buffer.getSize();//для безопасости надо бы поставить ограничение макс. размера в 2^63

	unique_ptr<uint8_t> newBlock(new uint8_t[sumSize]);

	this->lowLevelRead(newBlock.get(), this->getSize());
	buffer.lowLevelRead(newBlock.get() + this->getSize(), buffer.getSize());

	this->buffer = move(newBlock);
	this->size = sumSize;

	if(this->getWriteSpace() > 0)
		this->dropPointers();//если в конце 1-го блока было не инициализированное место, то нарушается логика, поэтому просто сбрасываем поинтеры
	else
		this->writePos += buffer.writePos;//если инициализированное пространство не разделено, то можно продолжать его читать.
}




void Buffer::dropPointers(){
	readPos = 0;
	writePos = 0;
}


void Buffer::write(const void *data, uint64_t length){
	lowLevelWrite(data, length, writePos);
	writePos += length;
}

void Buffer::write(istream &i, uint64_t length){
	if(getWriteSpace() < length)
		throw logic_error("Buffer overflow");

	void *ptr = getPtr() + writePos;
	i.read(reinterpret_cast<char *>(ptr), length);
	writePos += length;
}


uint64_t Buffer::getWriteSpace() const{
	return getSize() - writePos;
}

uint64_t Buffer::getReadSpace() const{
	return getSize() - readPos;
}

void Buffer::read(void *dst, uint64_t length){
	lowLevelRead(dst, length, readPos);
	readPos += length;
}


void Buffer::read(ostream &o, uint64_t length){
	if(getReadSpace() < length)
		throw logic_error("Buffer reading overflow");

	void *ptr = getPtr() + readPos;
	o.write(reinterpret_cast<char *>(ptr), length);
	readPos += length;
}


uint64_t Buffer::getSize() const{
	return size;
}






string Buffer::toBitString() const{
	string res;
	for(size_t i = 0; i < size; ++i){
		uint8_t current = get<uint8_t>(i);
		for(int bitRank = 7; bitRank >= 0; --bitRank)
			res += current & 1 << bitRank ? "1" : "0";
		res += " ";
	}
	return res;
}

string Buffer::toCharString() const{
	string res;
	for(uint64_t i = 0; i < size; ++i)
		res += get<char>(i);
	return res;
}








