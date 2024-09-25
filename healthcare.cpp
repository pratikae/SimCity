#include "healthcare.h"
#include "classism.h"
#include "simulation.h"
#include "death.h"
#include <iostream>
#include <cstdlib>
#include <map>
#include <cmath>
using namespace std;

/* to do and questions:
- incorporate classism functionalities 
    - a little unclear on how the classism maps work, if the classStructs map index aligns with position in the orginal vector ??
    - are the lower indexes in the map higher classes? were they the first to populate? like more insurance and salary and stuff
- 
*/

struct InjuredCell{
    int index[2]; // xy-coordinates
    string cellType; // type of cell from ogVec
    int population; // cell population
    int injured; // taken from injuredVec in death 
    int classLevel; // higher class = better, from classism maps
    double mortality; // mortality rate from classism
    double salary; // from classism
    double insurance; // insurance coverage percent from classism
};


double calculateSeverity(string cellType) {

    double s;

    if (cellType == "I" || cellType == " I") {
        int n = (rand() % 18) + 3;
        s = n;
    } else {
        int n = (rand() % 20) + 1;
    }

    if (s > 20) {
        return 20.0;
    }

    return s;

}

double calculateCost(double severity, double insurance, double income) {

    double flatCost = severity * 5000; 
    double cost = flatCost * ((100-insurance)/100);
    return cost;

}

void healthcare(vector< vector<string> > &ogVec, vector< vector<int> > &copyVec, vector< vector<int> > &injuredVec) {
    
    vector<InjuredCell> cells;

    for (int i = 0; i < vecRows; i++) { 
        for (int j = 0; j < vecCols; j++) {
            if (copyVec[i][j] != -1){

                // find the index of the cell in classism
                int classLevel;
                pair<int, int> coords = make_pair(i, j);
                for (auto i = indexOrder.begin(); i != indexOrder.end(); i++) {
                    if (i->second == coords) {
                        classLevel = i->first;
                    }
                }
                 
                InjuredCell temp = {{i, j}, ogVec[i][j], copyVec[i][j], injuredVec[i][j], classLevel, classStructs[classLevel].mortality, classStructs[classLevel].salary, classStructs[classLevel].insurance}; //creating temporary Cell object
                cells.push_back(temp); //adding cell to vector
            }
        }
    }

    // random workplace injuries for industrial cells, everyday injuries for residential and commercial cells
    for (int i = 0; i < cells.size(); i++) {
        if (cells[i].cellType == "I" || cells[i].cellType == " I") {
            int random = (rand() % 20) + 1;
            if (random <= 5) { // 25% chance of workplace injuries 
                cells[i].injured++;
            }
        } 
        if (cells[i].cellType == "R" || cells[i].cellType == " R" || cells[i].cellType == "C" || cells[i].cellType == " C") {
            int random = (rand() % 20) + 1;
            if (random <= 1) { // 5% chance of workplace injuries 
                cells[i].injured++;
            }
        }
    }

    // treatment of each injury in each cell
    for (int i = 0; i < cells.size(); i++) {
        InjuredCell temp = cells[i];
        int deadPop = 0;
        int recoveredPop = 0;

        for (int j = 0; j < cells[i].injured; j++) {
            
            double severity = calculateSeverity(temp.cellType);
            double cost = calculateCost(severity, temp.insurance, temp.salary);

            if (cost > temp.salary) { // recieve no treatment if cost of treatment is more than their salary
                if (severity >= 15) { // death!! no impact on cemeteries, just get stored in hospital morgue or used for transplants (trust)
                    deadPop++;
                    continue;
                } else { // leave injured, increase mortality rate of cell
                    temp.mortality = temp.mortality + (severity / 2);
                    continue;
                }
            }

            int treatment = (rand() % (20-(temp.classLevel/2))); // calculate treatment, higher class as higher chance of good treatment
            double fullRecovery = severity * 0.75; // recovery rate min 25%
            double survival = severity * 0.5; // survival rate min 50%
            if (treatment >= fullRecovery) { 
                recoveredPop++;
            } else if (treatment >= survival) {
                temp.mortality = temp.mortality + (severity / 4);
            } else {
                deadPop++;
            }
        }

        // updating cell injured and population, along with global vars for total deaths and injuries
        num_deaths += deadPop;
        num_injured -= (recoveredPop + deadPop);
        temp.injured -= (recoveredPop + deadPop);
        temp.population -= deadPop;

    }

    // update injuredVec and copyVec 
     for (int i = 0; i < cells.size(); i++){
        int row = cells[i].index[0];
        int col = cells[i].index[1];
        injuredVec[row][col] = cells[i].injured;

        copyVec[row][col] = cells[i].population;
       
    }

    return;

}


