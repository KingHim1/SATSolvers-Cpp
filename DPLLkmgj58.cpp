#include <algorithm>
#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
#include <numeric>
#include <random>
#include <vector>
#include "readSATFile.h"
using namespace std;

class dpllSolver{
	public:
		int getNewLiteral(Clauses &clauses, std::vector<int> &untestedLiterals, int nbvar);
		int unitPropagation(Clauses &clauses, std::vector<int> &untestedLiterals, std::vector<int> &literals, int nbvar);
		int dplAlgorithm(Clauses &clauses, std::vector<int> &untestedLiterals, std::vector<int> &literals, int nbvar);
};

int main(int argc, char* argv[]){
	char* fileName = argv[1];
	readSATFile file;
	Clauses clauses;
	clauses = file.getClauses(argv[1]);
	// std::cout << '\n' << file.nbvar << '\n' << file.nbclause << '\n';
	dpllSolver solver;
	std::vector<int> untestedLiterals(file.nbvar);
	std::iota (std::begin(untestedLiterals), std::end(untestedLiterals), 1);
	std::vector<int> literals;
	int ans = solver.dplAlgorithm(clauses, untestedLiterals, literals, file.nbvar);
	if(ans == 0){
		std::cout << "unsatisfied";
	}
	else{
		for(int x =0; x<literals.size(); x++){
			std::cout << literals[x] << ',';
		}
	}

}

	int dpllSolver::getNewLiteral(Clauses &clauses, std::vector<int> &untestedLiterals, int nbvar){
		int size = untestedLiterals.size();
		if(size > 1){
			std::srand(std::time(0));
			int index = std::rand() % size;
			return untestedLiterals[index];
		}
		else if (size == 1){
			return untestedLiterals[0];
		}
		else{
			return nbvar + 1;
		}
	};

	int dpllSolver::unitPropagation(Clauses &clauses, std::vector<int> &untestedLiterals, std::vector<int> &literals, int nbvar){
		Clauses clauseCopy = clauses;
		int numOfUnitClauses = 1;
    	while (numOfUnitClauses > 0){
        numOfUnitClauses = 0;
        for(int x = 0; x < clauses.size(); x++){
            if (clauses[x].size() == 1){
                return 0;
            }
            else if (clauses[x].size() == 2){
                if (std::find(untestedLiterals.begin(), untestedLiterals.end(), std::abs(clauses[x][0])) != untestedLiterals.end()){
                    literals.push_back(clauses[x][0]);
					untestedLiterals.erase( std::remove( untestedLiterals.begin(), untestedLiterals.end(), std::abs(clauses[x][0]) ), untestedLiterals.end() ); 
                    numOfUnitClauses += 1;
                    for(int y = 0; y< clauses.size(); y++){
                    	if (std::find(clauses[y].begin(), clauses[y].end(), -clauses[x][0]) != clauses[y].end()) {
                    		clauses[y].erase(std::remove(clauses[y].begin(), clauses[y].end(), -clauses[x][0]), clauses[y].end());
                    	}
                    	if (std::find(clauses[y].begin(), clauses[y].end(), clauses[x][0]) != clauses[y].end()) {
                    		clauses.erase(clauses.begin()+y);
                    		y = y - 1;
                    	}                	
                    }
                }
            }
        }
                        
		}
		return 1;
	};

	int dpllSolver::dplAlgorithm(Clauses &clauses, std::vector<int> &untestedLiterals, std::vector<int> &literals, int nbvar){
		int hasConflict = unitPropagation(clauses, untestedLiterals, literals, nbvar);
		if (hasConflict == 0){
			return 0;
		}
		else{
			if(clauses.size() == 0){
				return 1;
			}
			int literal = getNewLiteral(clauses, untestedLiterals, nbvar);
			if(literal <= nbvar){
				int newClauseArray[] = {literal, 0};
				std::vector<int> newClauseVector (newClauseArray, newClauseArray + sizeof(newClauseArray) / sizeof(int) );
				clauses.push_back(newClauseVector);
			}
			else{
				return 0;
			}
			vector<int> untestedLiteralsCopy = untestedLiterals;
			Clauses clausesCopy = clauses;

			// vector<int> literalsCopy = literals;
			hasConflict = dplAlgorithm(clausesCopy, untestedLiteralsCopy, literals, nbvar);
			if(hasConflict == 0){
				clausesCopy = clauses;
				untestedLiteralsCopy = untestedLiterals;
				for(int x = 0; x < clausesCopy.size(); x ++){
					if(std::find(clauses[x].begin(), clauses[x].end(), clauses[x][0] ) != clauses[x].end()){
						clauses.erase(clauses.begin()+x);
						x = x - 1;
					}
				}
				int newClauseArray[] = {-literal, 0};
				std::vector<int> newClauseVector (newClauseArray, newClauseArray + sizeof(newClauseArray) / sizeof(int) );
				clausesCopy.push_back(newClauseVector);
				hasConflict = dplAlgorithm(clausesCopy, untestedLiteralsCopy, literals, nbvar);
				if(hasConflict == 0){
					return 0;
				}
			}
		}
		return 1;
	};




