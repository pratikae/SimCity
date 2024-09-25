#include "residential.h"
#include "simulation.h"
#include "classism.h"
#include <iostream>
#include <vector>

Residential::Residential(vector<vector<string> > &ogVec, vector<vector<int> > &copyVec){}

void Residential::addNumWorkers(int i) {
    switch(i) { // check population of cell, add to proper adjCellWorkers
        case 0:
            break;
        case 1:
            adjCellWorkers1++;
            break;
        case 2:
            adjCellWorkers2++;
            break;
        case 3:
            adjCellWorkers3++;
            break;
        default:
            break;
    }

    if (i >= 4) {
        adjCellWorkers4++;
    }
}

void Residential::checkPowerLines(string i) {
    if (i == "T" || i == "#") {
        //cout << "YES" << endl; 
        numPowerlines++;
    }
    //else { cout << "NO" << endl; }
}

void Residential::checkAdjCells(vector<vector<int> > &vec, vector<vector<string> > &ogVec, int i, int j) {

    for (int m = i-1; m < i+2; m++) { //iterating through adjacent cells
        for (int n = j-1; n < j+2; n++) {
            //cout << "   checking " << i << " " << j << endl; 
            if (m < vecRows && n < vecCols && m >= 0 && n >= 0) { // making sure to not check nonexistent cells (negative)
                addNumWorkers(vec[m][n]);
                //cout << "    power lines? "; 
                checkPowerLines(ogVec[m][n]);
            }
            //else { cout << "    out of bound cell: continue" << endl;}
        }
    }
}

void Residential::runResidential(vector<vector<string> > &ogVec, vector<vector<int> > &copyVec) {
    
    // all changes need to first happen in the tempvec and then be added in the copyvec at the end of runResidential
    vector<vector<int> > tempVec = copyVec; // create a temp vec that is originally equal to the copyVec
    int row_i = 0;
    int col_i = 0;
    
    for (int i = 0; i < vecRows; i++) {
        for (int j = 0; j < vecCols; j++) {
            
            if (ogVec[i][j] == "R") { // checks if cell is residential

                //cout << "RESIDENTIAL CELL: " << i << " " << j << endl; 

                switch (copyVec[i][j]) { 
                    case 0: 

                        //cout << "   0" << endl;
                        //cout << "   checking adjacent cells..." << endl; 

                        checkAdjCells(copyVec, ogVec, i, j); // check cells of copyVec

                        if (numPowerlines >= 1) { // increase population and available_workers accordingly
                            copyVec[i][j]++;
                            classism(i, j, copyVec, ogVec); 
                            available_workers++;
                        } else if (adjCellWorkers1 >= 1) {
                            copyVec[i][j]++;
                            classism(i, j, copyVec, ogVec); 
                            available_workers++;
                        }
                        break;
                    case 1:

                        //cout << "   1" << endl;

                        checkAdjCells(copyVec, ogVec, i, j);
                        if (adjCellWorkers1 >= 1 ) {
                            copyVec[i][j]++;
                            classism(i, j, copyVec, ogVec); 
                            available_workers++;
                        }
                        break;
                    case 2:

                        //cout << "   2" << endl;

                        checkAdjCells(copyVec, ogVec, i, j);
                        if (adjCellWorkers2 >= 4 ) {
                            copyVec[i][j]++;
                            classism(i, j, copyVec, ogVec); 
                            available_workers++;
                        }
                        break;
                    case 3:

                        //cout << "   3" << endl;

                        checkAdjCells(copyVec, ogVec, i, j);
                        if (adjCellWorkers3 >= 6 ) {
                            copyVec[i][j]++;
                            classism(i, j, copyVec, ogVec); 
                            available_workers++;
                        }
                        break;
                    case 4:

                        //cout << "   4" << endl;

                        checkAdjCells(copyVec, ogVec, i, j);
                        if (adjCellWorkers4 >= 8 ) {
                            copyVec[i][j]++;
                            classism(i, j, copyVec, ogVec); 
                            available_workers++;
                        }
                        break;
                    default:
                        break;
                }
            }
        }
    }

}
