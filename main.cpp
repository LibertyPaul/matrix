#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>


#include "stuff.h"
using namespace std;
#include "ZNumber.hpp"
#include "Matrix.hpp"
#include "DataSplitter.hpp"
#include "Buffer.hpp"
#include "DataSeparator.hpp"
#include "ClientDataPart.hpp"
#include "Base16.hpp"



vector<ClientDataPart> separate(const Buffer &secret, const uint16_t K, const uint16_t N){
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

	return clients;
}

Buffer restore(const vector<ClientDataPart> &clients){
	if(clients.size() == 0)
		throw runtime_error("empty input");

	uint16_t K = clients.size();

	uint32_t partCount = clients.front().getLinearEquasions().getRowCount();
	vector<Matrix> splittedSecret(partCount);
	for(uint32_t part = 0; part < partCount; ++part)
		for(uint32_t client = 0; client < K; ++client)
			splittedSecret.at(part).pushRowBack(clients.at(client).getLinearEquasions().getRow(part));

	uint16_t N = 42;//N ни на что не влияет при восстановлении. надо бы подпраить классы чтоб не требовали ее когда не нужно
	DataSplitter dataSplitter(K, N);

	vector<vector<uint32_t>> restored;
	for(const auto &matrix : splittedSecret){
		vector<uint32_t> secretPart = move(dataSplitter.restore(matrix));
		restored.push_back(secretPart);
	}

	DataSeparator dataSeparator(K, N);
	Buffer result = move(dataSeparator.restore(restored));
	return result;
}

void man(const string &progName){
	cout << "Usage: " << endl;
	cout << progName << " <-separate N K secret>|<-restore part1 part2 ... partK>" << endl;
}

int main(int argc, char **argv){//./progName <-separate N K key>|<-restore part1 part2 ...>
	const string progName(argv[0]);
	Base16 base16;

	if(argc < 2){
		man(progName);
		return -1;
	}

	const string action(argv[1]);
	if(action == "-separate"){
		if(argc < 5){
			man(progName);
			return -1;
		}
		const string Nstr(argv[2]);
		const string Kstr(argv[3]);


		uint16_t N = stoi(Nstr);
		uint16_t K = stoi(Kstr);

		const string key(argv[4]);

		vector<ClientDataPart> parts;

		try{
			parts = move(separate(key, K, N));
		}catch(runtime_error &re){
			cout << "Ошибка: " << re.what() << endl;
		}catch(logic_error &le){
			cout << "Ошибка: " << le.what() << endl;
		}

		size_t i = 0;
		for(const auto &part : parts){
			Buffer bc = move(part.toBinaryContainer());
			string bc16 = base16.encode(bc);
			cout << ++i << " : " << bc16 << endl << endl;
		}
	}
	else if(action == "-restore"){
		if(argc < 3){
			man(progName);
			return -1;
		}


		vector<ClientDataPart> parts;
		for(uint16_t i = 2; i < argc; ++i){
			string bc16(argv[i]);
			Buffer bc = base16.decode(bc16);
			ClientDataPart cdp(bc);
			parts.push_back(move(cdp));
		}

		Buffer result;
		try{
			result = move(restore(parts));
		}catch(runtime_error &re){
			cout << "Ошибка: " << re.what() << endl;
		}catch(logic_error &le){
			cout << "Ошибка: " << le.what() << endl;
		}

		cout << result.toCharString() << endl;


	}

}









