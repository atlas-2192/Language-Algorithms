
//##########################################
// -Author: Brandon Schaefer
// -Created: 5/08/11
// -File Name: lib.cpp 
//##########################################
#include "lib.h"
#include "gramIO.h"
#include <vector>


using namespace std;

// Set Functions ------- Member, Union, Intersection, Difference
bool member(set<char*> mySet, char* data){

	set<char*>::iterator it;

	for( it = mySet.begin(); it != mySet.end(); it++){
		if( strcmp( *it, data) == 0 ){
			return 1;
		}
	}
	return 0;

}

void unionSet(set<char*>& setA, set<char*> setB){
	
	set<char*>::iterator it;
	
	for( it = setB.begin(); it != setB.end(); it++){
		setA.insert(*it);
	}

}


void interSet(set<char*>& setA, set<char*> setB){

	set<char*>::iterator it;
	set<char*>::iterator tmp;

	it = setA.begin();
	
	while( it != setA.end() ){
		if( !(member(setB, *it)) ){
			tmp = it;
			++it;
			setA.erase(tmp);
		}
		else{
			++it;
		}
	}
}

void diffSet(set<char*>& setA, set<char*> setB){
	
	set<char*>::iterator it;
	set<char*>::iterator tmp;

	it = setA.begin();

	while( it != setA.end()){
		if( member( setB, *it) ){
			tmp = it;
			++it;
			setA.erase(tmp);
		}
		else{
			++it;
		}
		
	}
}

// ---- End of Set Functions





char* insertVariable( std::set<char*>& variables, char* production){


	char* newVar = new char[MAX_VAR_SIZE+1];
	int varSize = isVariable(production);
	strncpy(newVar, production, varSize);
	*(newVar+varSize) = '\0';	
	if( !(member(variables, newVar)) ){
		variables.insert(newVar);
	}
	else{
		delete(newVar);
		return NULL;
	}
	
	return newVar;
}


// Takes a set and checks if the new data is already in the set
void insertIntoSet(std::set<char*>& set, char* data){
	
	if( !(member(set, data)) ){
		set.insert(data);
	}
	else{
		delete(data);
	}

}


bool compareSets( set<char*> setA, set<char*> setB ){

        // check size of each first, its faster that way
        if( setA.size() == setB.size()){

                set<char*>::iterator itA;
                set<char*>::iterator itB;

                for( itA = setA.begin(); itA != setA.end(); itA++){
                        if( member( setB, *itA ) == 0 ){
                                return false;
                        }
                }
                return true;
        }
        return false;
}


void displayGrammer(set<char*>* grammer){
	for( int i = 0; i < 4; i++){

		switch(i){
			case(0):
				cout << "*-*-*-Variables-*-*-*" << endl;
			break;
			case(1):
				cout << "*-*-*-Alphabet-*-*-*" << endl;
			break;
			case(2):
				cout << "*-*-Production Rules-*-*" << endl;
			break;
			case(3):
				cout << "*-*-*-Start Symbol-*-*-*" << endl;
			break;
		}
		displaySet(grammer[i]);
		cout << "\n" << endl;
	}

}
	
void displaySet(set<char*> setA){

	set<char*>::iterator it;
	
	for( it = setA.begin(); it != setA.end(); it++){
		cout << *it << endl;
	}

}

// Takes a production and returns a pointer to the start of the rule
// Eample: input with "S Aab" returns "Aab"
char* getRulePtr(char* production){
	while(*(production) && *(production++) != ' ');
	return production;
}


// takes a var and sees if its the same as a production  var
int varEqual(char* var, char* proVar){
	int varSize = strlen(var);
	int ruleSize = variableLen(proVar);	

	if( ruleSize == varSize && strncmp(var,proVar, ruleSize) == 0){
		return 1;
	}
	
	return 0;
}

// Returns the size of the variable, so you can copy it into
// another char*
int variableLen( char* rule ){
	int size = 0;

	while(*rule && *rule != ' '){
		rule++;
		size++;
	}

	return size;
}

bool isDigit( char digit ){
	int ascii = (int)digit;
	if( ascii >= 48 && ascii <= 57 )
		return true;
	return false;
}

bool isUppChar( char letter ){
	int ascii = (int)letter;
	if( ascii >= 65 && ascii <= 90 )
		return true;
	return false;
}

bool isLowChar( char letter ){
	int ascii = (int)letter;
	if( ascii >= 97 && ascii <= 122)
		return true;
	return false;
}

// return the size of the term or 0 if its false
int isTerminal(char* term){
        //checks if the first char is a letter
        int termSize = 0;
        if( isLowChar( *term ) || strcmp(term, NULL_CHAR) == 0 ){
                termSize++;
                while( isDigit( *term++ ) ){
                        termSize++;
                }
                return termSize;
        }
        return termSize;
}


// returns the size of the var in char*.
// If it cannot it returns 0 ( varSize == 0 )
int isVariable(char* var){
	int varSize = 0;
	if( isUppChar( *var++ ) ){
		varSize++;
		while( isDigit( *var++ )){
			varSize++;
		}
		return varSize;
	}
	return varSize;
}





vector<char*> splitProduction(char* production){

	vector<char*> proVec;
	char* newEntry;// = new char[MAX_RULE_SIZE+1];
	int size;
/*
	size = isVariable(production);
	strncpy(newEntry, prodction, size);
	*(newEntry+size) = '\0';
	ruleSplit	
*/		
	// Skips the space in production


	while( (size = isVariable(production)) || (size = isTerminal(production)) ){
		newEntry = new char[MAX_RULE_SIZE+1];
		strncpy(newEntry, production, size);
		*(newEntry+size) = '\0';
		proVec.push_back(newEntry);
		production += size;
		while( *production == ' ' ){
			production++;
		}
	}
	

	return proVec;
}



