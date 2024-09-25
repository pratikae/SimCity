#ifndef CLASSISM_H
#define CLASSISM_H

#include "simulation.h"
#include <map>  
#include <stdlib.h>

struct ClassDetail{
    double mortality; // mortality rate 
    double salary; // average salary per region 
    double insurance; // % of hospital bills covered by insurance 
};

extern map<int, pair<int, int> > indexOrder; 
extern map<int, ClassDetail> classStructs; 

void initializeMaps(vector< vector<string> > &originalVec); 
void classism(int i, int j, vector< vector<int> > &copyVec, vector< vector<string> > &originalVec);
void printClassResults(vector< vector<string> > &originalVec); 
int promptDeath(vector< vector<int> > &copyVec); 

#endif 
