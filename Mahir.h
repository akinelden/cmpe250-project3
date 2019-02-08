#ifndef Mahir_h
#define Mahir_h

#include <vector>

#define ROOT 2
#define PASSED 1

using namespace std;


struct Piggy 
{
	int index;
	int indegree;
	int type;
	vector<int> children;
};

struct Result
{
	int root_number;
	vector<int>* roots;
};


class MAHIR {
	vector<Piggy>* mybanks;
	vector<int> real_roots;
	vector<int> cycle_roots;
	vector<int> roots;
	vector<int> opened;
	int CurrentRoot;
public:
	MAHIR();
	MAHIR(vector<Piggy>*& p);
	~MAHIR();
	MAHIR(const MAHIR& m);
	MAHIR &operator=(const MAHIR& m);
	MAHIR(MAHIR&& m);
	MAHIR &operator=(MAHIR&& m);
	void FindRoots();
	void MergeRoots();
	Result GetResult();
};


#endif // !Mahir_h

