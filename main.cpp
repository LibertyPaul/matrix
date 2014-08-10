#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>


#include "stuff.h"
using namespace std;
#include "ZNumber.hpp"
#include "Matrix.hpp"
#include "DataSplitter.hpp"
#include "Buffer.hpp"
#include "DataSeparator.hpp"
#include "ClientDataPart.hpp"


const uint16_t K = 10, N = 15;
const uint64_t secretLength = 512;

string getFileName(uint32_t id){
	return "parts/dataPart #" + to_string(id) + ".dat";
}

void createKeys(const Buffer &secret){
	DataSeparator dataSeparator(K, N);
	vector<vector<uint32_t>> separatedSecret = dataSeparator.separate(secret);

	DataSplitter dataSplitter(K, N);


	vector<Matrix> splittedSecret;
	for(const auto &secretPart : separatedSecret){
		Matrix equasions = dataSplitter.split(secretPart);
		splittedSecret.push_back(move(equasions));
	}

	vector<ClientDataPart> clients;
	for(uint32_t client = 0; client < N; ++client){
		Matrix currentClientMatrix;
		for(const auto &equasion : splittedSecret)
			currentClientMatrix.pushRowBack(equasion.getRow(client));

		ClientDataPart currentCDP(currentClientMatrix);
		clients.push_back(move(currentCDP));
	}

	for(uint32_t client = 0; client < N; ++client){
		Buffer currentRawInfo = move(clients.at(client).toBinaryContainer());

		ofstream key_file(getFileName(client), ios_base::trunc);
		if(!key_file)
			throw runtime_error("Can't access file");

		currentRawInfo.dropPointers();
		currentRawInfo.read(key_file, currentRawInfo.getSize());
		key_file.close();
	}
}

Buffer restore(){
	vector<ClientDataPart> clients;
	for(uint32_t client = 0; client < K; ++client){
		ifstream key_file(getFileName(client));
		if(!key_file)
			throw runtime_error("Can't access file");

		key_file.seekg(0, key_file.end);
		size_t fSize = key_file.tellg();
		key_file.seekg(0, key_file.beg);

		Buffer currentRawInfo(fSize);
		currentRawInfo.write(key_file, fSize);
		key_file.close();

		clients.push_back(move(ClientDataPart(currentRawInfo)));
	}

	vector<Matrix> splittedSecret;
	uint32_t partCount = clients.front().getLinearEquasions().getRowCount();
	for(uint32_t part = 0; part < partCount; ++part){
		Matrix currentLESystem;
		for(uint32_t client = 0; client < K; ++client)
			currentLESystem.pushRowBack(clients.at(client).getLinearEquasions().getRow(part));

		splittedSecret.push_back(move(currentLESystem));
	}

	DataSplitter dataSplitter(K, N);

	vector<vector<uint32_t>> restored;
	for(const auto &matrix : splittedSecret){
		vector<uint32_t> secretPart = dataSplitter.restore(matrix);
		restored.push_back(secretPart);
	}

	DataSeparator dataSeparator(K, N);

	Buffer result = move(dataSeparator.restore(restored));
	return result;
}




int main(){
	size_t seed = chrono::system_clock::now().time_since_epoch().count();
	mt19937 randomGenerator(seed);

	Buffer secret(secretLength);
	secret.fill(randomGenerator);

	createKeys(secret);
	Buffer restored = move(restore());

	cout << (secret == restored ? "+" : "-") << endl;

}
