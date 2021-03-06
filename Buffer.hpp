#ifndef BUFFER_HPP_INCLUDED
#define BUFFER_HPP_INCLUDED

#include <memory>
#include <istream>
#include <ostream>
#include <vector>


class Buffer{
	uint64_t size;
	unique_ptr<uint8_t> buffer;

	uint64_t readPos, writePos;

	uint8_t *getPtr();
	const uint8_t *getPtr() const;

	void lowLevelWrite(const void *data, uint64_t length, uint64_t from = 0);//lowLevel операции не затрагивают readPos и writePos
	void lowLevelRead(void *dst, uint64_t length, uint64_t from = 0) const;
public:
	Buffer();
	Buffer(uint64_t size);
	Buffer(const string &src);

	template<typename T>
	Buffer(const vector<T> &src): size(src.size() * sizeof(T)), buffer(new uint8_t[size]), readPos(0), writePos(size){
		lowLevelWrite(&src[0], this->size);
	}


	Buffer(const Buffer &buffer);
	Buffer(Buffer &&buffer);

	const Buffer &operator=(Buffer &&buffer);
	const Buffer &operator=(const Buffer &buffer);


	bool operator==(const Buffer &buffer) const;

	void fill(uint8_t value);
	void fill(const function<uint8_t()> &getValue);


	void append(const Buffer &buffer);

	template<typename T>
	void push_back(const T &t){
		Buffer t_buf(sizeof(t));
		t_buf.write<T>(t);
		this->append(t_buf);
	}

	void write(const void *data, uint64_t length);
	void write(istream &i, uint64_t length);
	void read(void *dst, uint64_t length);
	void read(ostream &o, uint64_t length);


	template<typename T = uint8_t>
	inline void write(const T &t){
		write(&t, sizeof(T));
	}

	template<typename T = uint8_t>
	inline T read(){
		T t;
		read(&t, sizeof(t));
		return t;
	}


	template<typename unit = uint8_t, uint16_t unitBitCapacity = sizeof(unit) * 8>//unit - тип элементов, содержащихся в буффере, unitBitCapacity - кол-во доступных для чтения/записи разрядов
	bool getBit(size_t pos) const{
		const size_t unitSize = sizeof(unit) * 8;
		if(unitSize < unitBitCapacity)
			throw runtime_error("bitCapacity can't be greater than actual size of unit");

		size_t i = pos / unitBitCapacity;
		unit mask = unit(1) << pos % unitBitCapacity;
		return (get<unit>(i) & mask) != 0;
	}


	template<typename unit = uint8_t, uint16_t unitBitCapacity = sizeof(unit) * 8>
	void setBit(bool value, size_t pos){
		const size_t unitSize = sizeof(unit) * 8;
		if(unitSize < unitBitCapacity)
			throw runtime_error("bitCapacity can't be greater than actual size of unit");

		size_t i = pos / unitBitCapacity;
		unit mask = unit(1) << pos % unitBitCapacity;
		if(value)
			get<unit>(i) |= mask;
		else
			get<unit>(i) &= ~mask;
	}




	void dropPointers();

	uint64_t getWriteSpace() const;
	uint64_t getReadSpace() const;



	template<typename T = uint8_t>
	T &get(uint64_t pos){
		if(writePos - sizeof(T) < pos * sizeof(T))
			throw runtime_error("Out of buffer");

		T *ptr = reinterpret_cast<T *>(getPtr() + pos * sizeof(T));
		return *ptr;
	}

	template<typename T = uint8_t>
	const T &get(uint64_t pos) const{
		if(writePos - sizeof(T) < pos * sizeof(T))
			throw runtime_error("Out of buffer");

		const T *ptr = reinterpret_cast<const T *>(getPtr() + pos * sizeof(T));
		return *ptr;
	}

	uint8_t &operator[](uint64_t pos){
		return get(pos);
	}

	const uint8_t &operator[](uint64_t pos) const{
		return get(pos);
	}


	uint64_t getSize() const;

	string toBitString() const;
	string toCharString() const;
};



#endif // BUFFER_HPP_INCLUDED
