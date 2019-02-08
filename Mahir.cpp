#include "Mahir.h"

MAHIR::MAHIR()
{
	CurrentRoot = 0;
}

MAHIR::MAHIR(vector<Piggy>*& p) : mybanks(p), CurrentRoot(0)
{
	real_roots.clear();
	cycle_roots.clear();
	roots.clear();
	opened.clear();
}

MAHIR::~MAHIR()
{
	if (mybanks)
		mybanks->clear();
	roots.clear();
	opened.clear();
	real_roots.clear();
	cycle_roots.clear();

}

MAHIR::MAHIR(const MAHIR & m)
{
	if (mybanks)
		mybanks->clear();
	mybanks = nullptr;
	mybanks = new vector<Piggy>(*m.mybanks);
	roots = m.roots;
	real_roots = m.real_roots;
	cycle_roots = m.cycle_roots;
	opened = m.opened;
	CurrentRoot = m.CurrentRoot;
}

MAHIR & MAHIR::operator=(const MAHIR & m)
{
	if (mybanks)
		mybanks->clear();
	mybanks = nullptr;
	mybanks = new vector<Piggy>(*m.mybanks);
	roots = m.roots;
	real_roots = m.real_roots;
	cycle_roots = m.cycle_roots;
	opened = m.opened;
	CurrentRoot = m.CurrentRoot;
	return *this;
}

MAHIR::MAHIR(MAHIR && m)
{
	mybanks = move(m.mybanks);
	roots = move(m.roots);
	real_roots = move(m.real_roots);
	cycle_roots = move(m.cycle_roots);
	opened = move(m.opened);
	CurrentRoot = move(m.CurrentRoot);
	m.mybanks = nullptr;
	m.roots.clear();
	m.opened.clear();
	m.CurrentRoot = 0;
}

MAHIR & MAHIR::operator=(MAHIR && m)
{
	mybanks = move(m.mybanks);
	roots = move(m.roots);
	real_roots = move(m.real_roots);
	cycle_roots = move(m.cycle_roots);
	opened = move(m.opened);
	CurrentRoot = move(m.CurrentRoot);
	m.mybanks = nullptr;
	m.roots.clear();
	m.opened.clear();
	m.CurrentRoot = 0;
	return *this;
}

void MAHIR::FindRoots()
{
	for (int i = 1; i < mybanks->size(); i++) {
		if ((*mybanks)[i].indegree == 0) {
			(*mybanks)[i].type = ROOT;
			real_roots.push_back(i);
			opened.push_back(i);
		}
	}
	for (int i = 0; i < opened.size(); i++) {
		int ind = opened[i];
		for (int j = 0; j < (*mybanks)[ind].children.size(); j++) {
			if ((*mybanks)[(*mybanks)[ind].children[j]].type == PASSED)
				continue;
			(*mybanks)[(*mybanks)[ind].children[j]].type = PASSED;
			opened.push_back((*mybanks)[ind].children[j]);
		}
	}

	for (int i = 1; i < mybanks->size(); i++) {
		if ((*mybanks)[i].type == 0) {
			(*mybanks)[i].type = PASSED;
			opened.push_back(i);
			CurrentRoot = i;
			int j = opened.size() - 1;
			for (; j < opened.size(); j++) {
				int ind = opened[j];
				for (int k = 0; k < (*mybanks)[ind].children.size(); k++) {
					if ((*mybanks)[(*mybanks)[ind].children[k]].type == PASSED) {
						if ((*mybanks)[(*mybanks)[ind].children[k]].index == CurrentRoot) {
							(*mybanks)[i].type = ROOT;
							cycle_roots.push_back(i);
							continue;
						}
						else
							continue;
					}
					(*mybanks)[(*mybanks)[ind].children[k]].type = PASSED;
					opened.push_back((*mybanks)[ind].children[k]);
				}
			}
		}
	}
	this->MergeRoots();
}

void MAHIR::MergeRoots() {

	int n = 0;
	int m = 0;

	roots.reserve(real_roots.size() + cycle_roots.size());
	for (; n<real_roots.size() && m<cycle_roots.size();) {
		if (real_roots[n]<cycle_roots[m])
			roots.push_back(real_roots[n++]);

		else
			roots.push_back(cycle_roots[m++]);
	}

	while (n<real_roots.size())
		roots.push_back(real_roots[n++]);

	while (m<cycle_roots.size())
		roots.push_back(cycle_roots[m++]);
}

Result MAHIR::GetResult()
{
	Result r;
	r.roots = &roots;
	r.root_number = roots.size();
	return r;
}
