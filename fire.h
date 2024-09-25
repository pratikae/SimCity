#ifndef FIRE_H
#define FIRE_H

#include "simulation.h"
#include <vector>
#include <string>

class Fire
{

public:
    Fire(vector< vector<int> > &copyVec, vector< vector<string> > &originalVec);
    void initiateFireSpread();

    

private:
    vector<vector<int> > &copyVec;
    vector<vector<string> > &originalVec;    
    void spreadFire ();
    void startFire();
    void spreadToCell(int row, int col, int fireLevel);
    void displayDamageReport();
    int totalCellsAffected;
    int totalPopulationReduction;
    int totalGoodsDestroyed;
};

#endif
