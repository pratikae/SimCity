#include "fire.h"

#include <iostream>
#include <cstdlib>
#include <ctime>



using namespace std;

//initialize random number generator
Fire::Fire(vector<vector<int> > &copyVec, vector<vector<string> > &originalVec) : copyVec(copyVec), originalVec(originalVec) {
    srand(time(NULL));
}

//initiate the fire spreading process across the grid
void Fire::initiateFireSpread() {
    startFire(); // starts a single fire spread from a random location.
    spreadFire(); // Spreads fire from initial and subsequent locations.
    displayDamageReport(); // Outputs the total damage caused by the fire.
}

//function that randomly selects a starting point for the fire and its intensity
void Fire::startFire () {
    int fireRow = rand() % copyVec.size();
    int fireCol = rand() % copyVec[0].size();
    int fireLevel = rand() % 2 + 1; // Random fire level between 1 and 2
    spreadToCell(fireRow, fireCol, fireLevel);
}

//function that spreads the fire from cell to cell
void Fire::spreadFire () {
    //ASCII art representation of fire
    cout<<"Here comes fire!"<<endl;
    cout<<"            (  .      )"<<endl;
    cout<<"         )           (              )"<<endl;
    cout<<"               .  '   .   '  .  '  ."<<endl;
    cout<<"       (    , )       (.   )  (   ',    )"<<endl;
    cout<<"        .' ) ( . )    ,  ( ,     )   ( ."<<endl;
    cout<<"    ). , ( .   (  ) ( , ')  .' (  ,    )"<<endl;
    cout<<"   (_,) . ), ) _) _,')  (, ) '. )  ,. (' )"<<endl;
    cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
    vector<vector<int> > toSpread; // vector to keep track of cells that will spread fire next
    for (int row = 0; row < copyVec.size(); ++row) {
        for (int col = 0; col < copyVec[0].size(); ++col) {
            if (copyVec[row][col]>0) {
                for (int x=-1; x<=1; x++) {
                    for (int y=-1; y<=1; y++) {
                        if (x==0 && y==0) { //skip the current cell
                            continue;
                        }
                    int newRow = row+x;
                    int newCol= col+y;

                    if (newRow >= 0 && newRow < copyVec.size() && newCol >= 0 && newCol < copyVec[0].size()) {
                        vector<int> cell;
                        cell.push_back(newRow);
                        cell.push_back(newCol);
                        toSpread.push_back(cell); // add to cells that need to spread fire
                    }
                }
            }
        }
    }
}
    //spread fire to the next cells
    for (size_t i = 0; i < toSpread.size(); ++i) { 
        const vector<int>& cell = toSpread[i];
        int fireLevel = rand() % 2 + 1; // Assign a new random fire level for spreading.
        spreadToCell(cell[0], cell[1], fireLevel); // Use cell[0] for row and cell[1] for col.
    }
}

//function that applies the corresponding fire effect based on the region and population
void Fire::spreadToCell(int row, int col, int fireLevel) {
    //check if the cell is within the bounds
    if (row < 0 || row >= copyVec.size() || col < 0 || col >= copyVec[0].size()) {
        return;
    }
    
    int preFirePopulation = copyVec[row][col]; //population before the fire

    if (originalVec[row][col].find("I") != string::npos) { //for industrial regions
        if (preFirePopulation > 2) {
            fireLevel--; 
        }
        copyVec[row][col] = preFirePopulation - fireLevel;
        available_workers -= fireLevel;
        available_goods -= fireLevel;
    } else if (originalVec[row][col].find("R") != string::npos) {  //for residential regions
        if (preFirePopulation > 3){
            fireLevel--;
        }
        copyVec[row][col] = preFirePopulation - fireLevel;
        available_workers -= fireLevel;
    } else if (originalVec[row][col].find("C") != string::npos) { //for commercial regions
        if (preFirePopulation > 2) {
            fireLevel--;
        }
        copyVec[row][col] = preFirePopulation - fireLevel;
        available_workers -= fireLevel;
        available_goods -= fireLevel;
    }

    int postFirePopulation = copyVec[row][col]; //population after fire
    int populationReduction = preFirePopulation - postFirePopulation; //calculate population reduction

    if (populationReduction > 0) {
        totalCellsAffected++; //increment number of cells affected
        totalPopulationReduction += populationReduction;
        if (originalVec[row][col].find("C") != string::npos) {
            totalGoodsDestroyed += populationReduction;
        } else if (originalVec[row][col].find("I") != string::npos) {
            totalGoodsDestroyed += populationReduction;
        }
    }

}

//output the result to console after simulation
void Fire::displayDamageReport() {
    cout << "Fire Damage Report:" << endl;
    cout << "Total Cells Affected: " << totalCellsAffected << endl;
    cout << "Total Population Reduction: " << totalPopulationReduction << endl;
    cout << "Total Goods Destroyed: " << totalGoodsDestroyed << endl;
}
