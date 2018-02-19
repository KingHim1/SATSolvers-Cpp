#ifndef __READSATFILE_H_INCLUDED__
#define __READSATFILE_H_INCLUDED__

using namespace std;

typedef std::vector<std::vector<int> > Clauses;

class readSATFile{
	public: 
		Clauses getClauses(char* fileName);
		int nbvar;
		int nbclause;
};

#endif