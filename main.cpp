#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <iterator>
#include <chrono>
#include <algorithm>

using namespace std;

#include "Mahir.h"




template <class Container>
void split1(const string& str, Container& cont)
{
	istringstream iss(str);
	copy(istream_iterator<string>(iss),
		istream_iterator<string>(),
		back_inserter(cont));
}

void PrintOut(Result& r, ofstream &o) {
	o << r.root_number << " ";
	for (int i = 0; i < r.roots->size(); i++)
		o << (*r.roots)[i] << " ";
}

void Print(Result &r) {
	cout << r.root_number;
	for (int i = 0; i < r.roots->size(); i++)
		cout << " " << (*r.roots)[i];
}

int main(int argc, char* argv[]) {

	auto begin = chrono::high_resolution_clock::now();

	ios_base::sync_with_stdio(false);

	if (argc != 3) {
		cout << "Run the code with the following command: ./project3 [input_file] [output_file]" << endl;
		return 1;
	}

	//cout << "input file: " << argv[1] << endl;
	//cout << "output file: " << argv[2] << endl;

	vector<Piggy>* banks = new vector<Piggy>;

	ifstream infile(argv[1]);
	string line;
	vector<string> input;
	getline(infile, line);

	int N = stoi(line);

	banks->reserve(N+1);
	Piggy a;
	a.index = 0;
	a.type = -1;
	a.indegree = -1;
	banks->push_back(a);
	for (int i = 1; i < N+1; i++) {
		Piggy p;
		p.indegree = 0;
		p.index = i;
		p.type = 0;
		banks->push_back(p);
	}

	for (int i = 1; i < N+1; i++) {
		int n;
		infile >> n;
		for (int j = 0; j < n; j++) {
			int c;
			infile >> c;
			(*banks)[i].children.push_back(c);
			(*banks)[c].indegree++;
		}
	}

	MAHIR* mahir = new MAHIR(banks);
	banks = nullptr;
	mahir->FindRoots();

	ofstream myfile;
	myfile.open(argv[2]);

	Result results = mahir->GetResult();


	//Print(results);
	PrintOut(results, myfile);
	myfile.close();

	delete mahir;
	mahir = nullptr;

	auto stop = chrono::high_resolution_clock::now();
	auto duration3 = chrono::duration_cast<chrono::microseconds>(stop - begin);
	//cout << endl << "Run time: " << duration3.count() << endl;

	return 0;

}