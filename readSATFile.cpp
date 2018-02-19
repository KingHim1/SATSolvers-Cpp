#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include "readSATFile.h"
using namespace std;

typedef std::vector<std::vector<int> > Clauses;



Clauses readSATFile::getClauses(char* fileName){
	// std::cout << fileName;
	
	ifstream satFile;
	satFile.open(fileName);
	Clauses clauses;
	if(satFile.is_open()){
		string line;
		while(getline(satFile, line)){
			if(line.compare(0,1,"c") ==0){
				//do nothing
			}
			else{
				std::istringstream iss(line);
				std::vector<std::string> results((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
				if(results[0].compare(0,1, "p") ==0){
					nbvar = std::stoi(results[2]);
					nbclause = std::stoi(results[3]);
					// std::cout << nbvar << '\n' << nbclause;
				}
				else{
					std::vector<int> clause;
					for(int i=0; i<results.size(); i++){
						clause.push_back(std::stoi(results[i]));
					}
					clauses.push_back(clause);
				}
			}
		}
		satFile.close();
	}
	return clauses;
};