// hashtable1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <map>
#include <string> 
#include <sstream>

using namespace std;

/* kod do interpretera */

enum class Commands {
	SIZE,
	ADD,
	PRINT,
	STOP,
	NOT_FOUND
};

map<string, Commands> castToCommand = {
	{ "size", Commands::SIZE},
	{ "add", Commands::ADD },
	{ "print", Commands::PRINT },
	{ "stop", Commands::STOP }
};


 /* Kod do hashtable */
struct dane {
	long key;
	string ddane;
};

const long EMPTY = -1;

struct hashtable {
	dane* array;
	unsigned int size;

	hashtable(unsigned int size)
	{
		this->size = size;
		this->array = new dane[size];
		for (unsigned int i = 0; i < size; i++)
			this->array[i].key = EMPTY;
	}

	~hashtable()
	{
		delete[](array);
	}

	long hash(long key)
	{
		return key % this->size;
	}

	void add(dane d)
	{
		// policzyc hash daty
		long h = this->hash(d.key);
		// wstawiamy do kubelka wyniku hash
		if (this->array[h].key == EMPTY)
		{
			this->array[h] = d;
		}
		// jesli zajety to w pierwsze wolne miejsce
		else
		{
			int i = 1;
			while (this->array[ (h + i) % this->size ].key != EMPTY) {
				i++;
			}
			// TODO possible infinite loop
			this->array[h + i] = d;
		}
	}

	void print()
	{
		for (unsigned int i = 0; i < this->size; i++)
		{
			cout << "i:"<<i<<"{";
			if (this->array[i].key != EMPTY)
			{
				cout << this->array[i].key << " -> " << this->array[i].ddane;
			}
			cout << "}\n";
		}
	}

};
std::istream & getline(std::istream & in, std::string & out) {
	char c;
	while (in.get(c).good()) {
		if (c == '\n') {
			c = in.peek();
			if (in.good()) {
				if (c == '\r') {
					in.ignore();
				}
			}
			break;
		}
		out.append(1, c);
	}
	return in;
}

int string2Int(string s)
{
	stringstream ss;
	ss << s;
	int i;
	ss >> i;
	return i;
}

void string2Dane(string s, long& key, char dane[])
{
	stringstream ss;
	int pos = s.find_first_of(' ');
	ss << s.substr(0, pos);
	ss >> key;
	for (int i = 0; i < 8; i++) {
		dane[i] = (char) s[pos+1+i];
	}
	dane[7] = '\0';
}

int main()
{
	unsigned int noTestCases;
	cin >> noTestCases;
	string line;
	string comm;
	string param;
	Commands current;
	int pos;
	bool isStoped;
	cerr << "1";
	hashtable * a;
	for (unsigned int no = 0; no < noTestCases; ++no)
	{
		cerr << "2";
		isStoped = false;
		while (!isStoped) {
			cerr << "3";
			line = "";
			getline(cin, line);
			if (line.size() == 0) continue;
			if (line[line.size() - 1] == '\r')
				line.resize(line.size() - 1);
			cerr << "\nWczytano " << line;
			pos = line.find_first_of(' ');
			param = line.substr(pos + 1),
				comm = line.substr(0, pos);
			cerr << "\nKomenda " << comm;
			if (castToCommand.count(comm) > 0) {
				current = castToCommand.at(comm);
				cerr << "FOUND!!";
			}
			else
			{
				cerr << "NOT FOUND";
				current = Commands::NOT_FOUND;
			}
			switch (current)
			{
			case Commands::SIZE:
				
				a = new hashtable(string2Int(param));
				break;
			case Commands::ADD:
				long key;
				char ddane[8];
				string2Dane(param, key, ddane);
				a->add(dane{ key,ddane });
				break;
			case Commands::PRINT:
				a->print();
				break;
			case Commands::STOP:
				isStoped = true;
				break;
			}
		}
	}
    return 0;
}

