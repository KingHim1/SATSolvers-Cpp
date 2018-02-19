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
typedef std::vector<std::vector<std::vector<int>>> WatchedLiterals;

enum clauseStatus{UNIT, UNSAT, SAT, UNRES};
enum literalStatus{T, F, U};


class CDCLSolver{
	int unitPropagation(Clauses &clauses, std::vector<int> &untestedLiterals, std::vector<int> &literals, int nbvar);
	clauseStatus getClauseStatus(std::vector<int> &clause, std::vector<int> &variableVals);
	literalStatus getLiteralStatus(int clauseLiteral, int variableValue);	
	int createWatchedLiterals(Clauses &clauses, int nbvar);
	int watchedLitsAdd(WatchedLiterals &watchedLiterals, std::vector<int> &clause, int clauseIndex);
	int updateWatchedLits(WatchedLiterals &watchedLiterals, int literal, int variableValue);

}

int CDCLSolver::updateWatchedLits(WatchedLiterals &watchedLiterals, int literal, int variableValue, Clauses, &clauses){
	//When variable is assigned a value, watched literals of negative literals require updating
	if(variableValue == 1){
		clauseNumbers = watchedLiterals[abs(literal)-1][0]
		for(int i = 0; i < clauseNumbers.size(), i++){
			clause = clauses[clauseNumbers[i]]
			int previousIndex;
			if clause[0] == -abs(literal){
				previousIndex = 0;
			}
			else if(clause[1] == -abs(literal)){
				previousIndex = 1;
			}
			else{
				previousIndex = 2;
			}
			Boolean swapped = false;
			if(previousIndex < 2){
				for(int j = 2;  j < clause.size(), j++){
					if (variableVals[abs(clause[j])-1] == -1 or getLiteralStatus(clause[y], variableVals[abs(clause[y])-1]) == literalStatus::True) and clause[y]!=0{
						swapped = true;
						watchedLiterals[abs(literal)-1][0].erase(std::remove(watchedLiterals[abs(literal)-1][0].begin(), watchedLiterals[abs(literal)-1][0].end(), clauseNumbers[i]), watchedLiterals[abs(literal)-1][0].end());
						if clause[j] < 0{
							watchedLiterals[abs(clause[j])-1][0].append(i);
						}
                        else{
                        	watchedLiterals[abs(clause[j])-1][1].append(i);	
                        }
                        std::swap(clause[j], clause[previousIndex]);
					}
				}
			}
		}
	}
	else{
		clauseNumbers = watchedLiterals[abs(literal)-1][1];
		for(int i = 0; i < clauseNumbers.size(), i++){
			clause = clauses[clauseNumbers[i]];
			Boolean swapped = false;
			int previousIndex = std::find(clause.begin(), clause.end(), std::abs(literal)) - clause.begin();
			if(previousIndex < 2){
				for(int j = 2;  j < clause.size(), j++){
					if (variableVals[abs(clause[j])-1] == -1 or getLiteralStatus(clause[y], variableVals[abs(clause[y])-1]) == literalStatus::True) and clause[y]!=0{
						swapped = true;
						watchedLiterals[abs(literal)-1][0].erase(std::remove(watchedLiterals[abs(literal)-1][0].begin(), watchedLiterals[abs(literal)-1][0].end(), clauseNumbers[i]), watchedLiterals[abs(literal)-1][0].end());
						if clause[j] < 0{
							watchedLiterals[abs(clause[j])-1][0].append(i);
						}
                        else{
                        	watchedLiterals[abs(clause[j])-1][1].append(i);	
                        }
                        std::swap(clause[j], clause[previousIndex]);
					}
				}
			}
		}
	}
}

int CDCLSolver::watchedLitsAdd(WatchedLiterals &watchedLiterals, std::vector<int> &clause, int clauseIndex){
	clause.erase(std::remove(clause.begin(), clause.end(), 0), clause.end());
	clause.push_back(0);
	if clause[0] < 0{
        watchedLiterals[abs(clause[0])-1][0].push_back(clauseIndex -1)
	}
    else{
        watchedLiterals[abs(clause[0])-1][1].push_back(clauseIndex -1)
    }
    if clause[1] < 0{
        watchedLiterals[abs(clause[1])-1][0].push_back(clauseIndex -1)
    }
    else{
        watchedLiterals[abs(clause[1])-1][1].push_back(clauseIndex -1)
    }
}

int CDCLSolver::createWatchedLiterals(Clauses &clauses, int nbvar){
	WatchedLiterals watchedLiterals;
	for(int i = 0; i < nbvar; i++){
		//Instantiate watched literals matrix
		variableWL = std::vector<std::vector<int>>();
		watchedLiterals.push_back(variableWL);
		posLiterals = std::vector<int>();
		negLiterals = std::vector<int>();
		watchedLiterals[i].push_back(negLiterals)
		watchedLiterals[i].push_back(posLiterals)
	}
	for(int i = 0; i < clauses.size(), i++){
		firstLit = clauses[x][0]
        secondLit = clauses[x][1]
        if(firstLit<0):
            watchedLiterals[abs(firstLit)-1][0].append(x)
        else if(firstLit > 0):
            watchedLiterals[abs(firstLit)-1][1].append(x)
        if(secondLit < 0):
            watchedLiterals[abs(secondLit)-1][0].append(x)
        else if(secondLit > 0):
            watchedLiterals[abs(secondLit)-1][1].append(x)
	}
}

literalStatus CDCL::getLiteralStatus(int clauseLiteral, int variableValue){
	if(clauseLiteral < 0){
		switch(variableValue){
			case 0: return literalStatus::T;
			case 1: return literalStatus::F;
			default: return literalStatus::U;
		}
	}
	else{
		switch(variableValue){
			case 0: return literalStatus::F;
			case 1: return literalStatus::T;
			default: return literalStatus::U;
		}
	}
}

clauseStatus CDCL::getClauseStatus(std::vector<int> &clause, std::vector<int> &variableVals){
	watchedLit0 =  getLiteralStatus(clause[0], variableVals[abs(clause[0])-1]);
	if(clause[1] == 0 and variableVals[std::abs(clause[0])-1] == -1){
		return clauseStatus::UNIT
	}
	watchedLit1 = litValue(clause[1], variableVals[std::abs(clause[1])-1]);
	if(watchedLit0 == literalStatus::T or watchedLit1 == literalStatus::T){
		return clauseStatus::SAT
	}
	else if(watchedLit0 == literalStatus::F and watchedLit1 == literalStatus::F){
		return clauseStatus::UNSAT
	}
	else if(watchedLit0 == literalStatus::U or watchedLit1 == literalStatus::U){
		return clauseStatus::UNRES
	}
}


int CDCLSolver::unitPropagation(Clauses &clauses, std::vector<int> &untestedLiterals, std::vector<int> &literals, int nbvar, std::vector<std::vector<int>> &variableAntecedents, std::vector<int> variableDecisionLevels, int decisionLevel){
	Clauses clauseCopy = clauses;
	int numOfUnitClauses = 1;
    while (numOfUnitClauses > 0){
    	numOfUnitClauses = 0;
    	for(int x = 0; x < clauses.size(); x++){
    		clstatus = getClauseStatus(clauses[x], variableVals);
    		if(clstatus == UNSATISFIED){
    			variableAntecedents[nbvar] = clauses[x];
    			return 0;		
    		}
    		else if(clstatus == UNIT){
    			numOfUnitClauses += 1;
    			if clauses[x][0] < 0 and variableVals[abs(clauses[x][0])-1] == -1{
    				variableAntecedents[std::abs(clauses[x][0])-1] = clauses[x]
                    variableVals[abs(clauses[x][0])-1] = 0
                    unassignedVariables.erase(std::remove(unassignedVariables.begin(), unassignedVariables.end(), std::abs(clauses[x][0])), unassignedVariables.end())
                    updateWatchedLits(watched)
    			}
    		}





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



def unitPropCDCL(clauses, variableVals, variableAntecedents, variableDecisionLevels, nbvar, nbclause, unassignedVariables, watchedLiterals, decisionLevel):
    clauseCopy = copy.deepcopy(clauses)
    numOfUnitClauses = 1
    while numOfUnitClauses > 0:
        numOfUnitClauses = 0
        for clause in clauses:
            clstatus = clauseStatus(clause)
            if clstatus == "UNSATISFIED":
                variableAntecedents[nbvar] = clause
                return False
            elif clstatus == "UNIT":
                numOfUnitClauses += 1
                if clause[0] < 0 and variableVals [abs(clause[0])-1] == "u":
                    variableAntecedents[abs(clause[0])-1] = clauses.index(clause)
                    variableVals[abs(clause[0])-1] = 0
                    unassignedVariables.remove(abs(clause[0]))
                    updateWatchedLits(watchedLiterals, 0, clause[0])
                    variableDecisionLevels[abs(clause[0])-1] = decisionLevel
                elif clause[0] > 0 and variableVals[abs(clause[0])-1] == "u":
                    variableAntecedents[abs(clause[0])-1] = clauses.index(clause)
                    variableVals[abs(clause[0])-1] = 1
                    unassignedVariables.remove(abs(clause[0]))
                    updateWatchedLits(watchedLiterals, 1, clause[0])
                    variableDecisionLevels[abs(clause[0])-1] = decisionLevel
                elif clause[1] < 0:
                    variableAntecedents[abs(clause[1])-1] = clauses.index(clause)
                    variableVals[abs(clause[1])-1] = 0
                    unassignedVariables.remove(abs(clause[1]))
                    updateWatchedLits(watchedLiterals, 0, clause[1])
                    variableDecisionLevels[abs(clause[1])-1] = decisionLevel
             	else:
                    variableAntecedents[abs(clause[1])-1] = clauses.index(clause)
                    variableVals[abs(clause[1])-1] = 1
                    unassignedVariables.remove(abs(clause[1]))
                    updateWatchedLits(watchedLiterals, 1, clause[1])
                    variableDecisionLevels[abs(clause[1])-1] = decisionLevel
