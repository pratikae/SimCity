#include "industrial.h"
#include "classism.h"
#include "pollution.h"

void conditionMet(vector< vector<int> > &copyVec, int i, int j, vector< vector<int> > &pollutionVec) {

  //cout << "CONDITION MET" << endl;
  copyVec[i][j]++;
  available_workers -= 2;
  spreadPollution(copyVec, pollutionVec, i, j, copyVec[i][j], vecRows, vecCols);

}

void industrial(vector< vector<int> > &copyVec, vector< vector<string> > &originalVec, vector< vector<int> > &pollutionVec){
    for (int i = 0; i < vecRows; i++) { //iterating through vector
        for (int j = 0; j < vecCols; j++) {
            if (originalVec[i][j] == "I"){

              if (i>=0 && i<vecRows && j>=0 && j<vecCols) {

                available_goods += copyVec[i][j]; // Produce goods

                //cout << "INDUSTRIAL CELL: " << i << " " << j << endl; 

                if (copyVec[i][j] == 0 && available_workers >= 2) {

                  //cout << " has population of 0" << endl; 
                  
                  bool adjPowerLine = false; 

                  for (int m = i-1; m <= i+1; m++){ //iterating through adjacent cells
                    for (int n = j-1; n <= j+1; n++){
                      if (m>=0 && m < vecRows && n>=0 && n < vecCols && !(m==i && n==j)){
                        if (originalVec[m][n] == "T" || originalVec[m][n] == "#") {
                          adjPowerLine = true; break; 
                        }
                      }
                    }
                  }

                  if (adjPowerLine == true) { 

                    //cout << "0 + power line" << endl; 
                    classism(i, j, copyVec, originalVec); 
                    conditionMet(copyVec, i, j, pollutionVec); 

                  }
                  else { 
                  // at least one cell with a population of at least 1

                    //cout << "adjacent? > "; 

                    bool adj1= false; 
                    for (int m = i-1; m <= i+1; m++){ //iterating through adjacent cells
                      for (int n = j-1; n <= j+1; n++){
                        if (m < 0 || m >= vecRows || n < 0 || n >= vecCols || (m==i && n==j)) {
                          continue;
                        }
                        else {
                          
                          if (copyVec[m][n] >= 1) { 
                            
                            //cout << " YES" << endl; 
                            adj1 = true; 

                          }

                          //else { cout << "NO" << endl;}
                          
                        }
                      }
                    }

                    if (adj1 == true) { 
                      
                      //cout << "YES!" << endl; 
                      classism(i, j, copyVec, originalVec); 
                      conditionMet(copyVec, i, j, pollutionVec); 
                      
                    }

                  }

                } else if (copyVec[i][j] == 1 && available_workers >= 2) {

                  // at least two cells with a population of at least 1
                  
                  bool adj1 = false; 
                  int adj1num = 0; 
                  for (int m = i-1; m <= i+1; m++){ //iterating through adjacent cells
                    for (int n = j-1; n <= j+1; n++){
                      if (m>=0 && m < vecRows && n>=0 && n < vecCols && !(m==i && n==j)){
                        if (copyVec[m][n] >= 1) { adj1num++; }
                        if (adj1num >= 2) { adj1 = true; break; }
                      }
                    }
                  }

                  if (adj1 == true) { 
                    
                    //cout << "2 adjcent of at least one" << endl; 
                    classism(i, j, copyVec, originalVec); 
                    conditionMet(copyVec, i, j, pollutionVec); 
                    
                  }

                } else if (copyVec[i][j] == 2 && available_workers >= 2) {

                  // at least two cell with a population of at least 2
                  
                  bool adj2 = false; 
                  int adj2num = 0; 
                  for (int m = i-1; m <= i+1; m++){ //iterating through adjacent cells
                    for (int n = j-1; n <= j+1; n++){
                      if (m>=0 && m < vecRows && n>=0 && n < vecCols && !(m==i && n==j)){
                        if (copyVec[m][n] >= 2) { adj2num++; }
                        if (adj2num >= 2) { adj2 = true; break; }
                      }
                    }
                  }

                  if (adj2 == true) { 
                    
                    //cout << "2 adjcent of at least two" << endl;
                    classism(i, j, copyVec, originalVec); 
                    conditionMet(copyVec, i, j, pollutionVec); 
                    
                  }

                }

              }

          }

        }

    }
    
}
