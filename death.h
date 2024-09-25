#include <iostream>
#include <vector>
#include <string>
#include "simulation.h"
using namespace std;

//function: initializing InjuredVec
void initializeInjuredVec(vector< vector<int> > &injuredVec);

//function: creates rat infestation and disease/calculates number of deaths and injured from disease
void death(vector< vector<int> > &copyVec, vector< vector<string> > &originalVec, vector< vector<int> > &pollutionVec, vector< vector<int> > &injuredVec, vector<string> &cemeteryVec);

//function: prints out cemetery vector at end of simulation
void printCemetery(vector<string> &cemeteryVec);
