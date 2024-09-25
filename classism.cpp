#include "classism.h"

void initializeMaps(vector< vector<string> > &originalVec) {

    // initializing vectors so that they won't be null next time around 

    int numregions = 0; 

    for (int i = 0; i < vecRows; i++) {

        for (int j = 0; j < vecCols; j++) {

            if (originalVec[i][j] == "R" || originalVec[i][j] == "I" || originalVec[i][j] == "C" 
            || originalVec[i][j] == " R" || originalVec[i][j] == " I" || originalVec[i][j] == " C") numregions++; 

        }

    }

    for (int i = 0; i < numregions; i++) {

        ClassDetail nullClass; 
        nullClass.mortality = 0; 
        nullClass.salary = 0; 
        nullClass.insurance = 0; 

        indexOrder[i] = make_pair(-1, -1);
        classStructs[i] = nullClass; 

    }

}

void classism(int i, int j, vector< vector<int> > &copyVec, vector< vector<string> > &originalVec) {

    pair<int, int> coordinates = make_pair(i, j); 
    bool coordExists = false; 
    int coordIndex = -1; 

    for (int n = 0; n < idx; n++) {

        if (indexOrder[n] == coordinates) { coordExists = true; coordIndex = n; }

    }

    if (!coordExists) { // if the cell doesn't already have an index (i.e. it's just been populated) then assign it an index 

        ClassDetail newClass; 
        newClass.mortality = (rand()%(19) + 1); 
        newClass.salary = rand()%(9384) + 50000;
        newClass.insurance = (rand()%(20) + 10);

        cout << "Mortality: " << newClass.mortality << "%" << endl;
        cout << "Salary: $" << newClass.salary << endl;
        cout << "Insurance: " << newClass.insurance << "%" << endl;

        if (originalVec[i][j] == "R" || originalVec[i][j] == " R") {

            pair<int, int> tempcoord = indexOrder[idx]; 
            indexOrder[idx-1] = coordinates;
            indexOrder[idx] = tempcoord; 
            // manipulate coordinates through index 

            ClassDetail tempClass = classStructs[idx]; 
            classStructs[idx-1] = newClass;
            classStructs[idx] = tempClass; 
            
        }

        else if (originalVec[i][j] == "I" || originalVec[i][j] == " I") {

            // if industrial region, add up to 5% onto the mortality rate 
            newClass.mortality = (newClass.mortality) + ((rand()%(4)) + 1);

            // swap index to push the industrial coordinate one place "below" where it should go 
            pair<int, int> tempcoord = indexOrder[idx]; 
            indexOrder[idx+1] = coordinates; 
            indexOrder[idx] = tempcoord; 

            ClassDetail tempClass = classStructs[idx]; 
            classStructs[idx+1] = newClass;
            classStructs[idx] = tempClass; 

        }

        else if (originalVec[i][j] == "C" || originalVec[i][j] == " C") { indexOrder[idx] = coordinates; } // otherwise run as normal 

        idx++; 

    } 

    else { // cell does have coordinate — time to iterate and stuff 

        if (!(coordIndex == idx))  { // location is not the end of the index 

            // current cell reaps benefits based on position 
            classStructs[coordIndex].salary += 0.05 * classStructs[coordIndex + 1].salary; // increased avg salary by 5% of the later cells salary
            classStructs[coordIndex].salary += ((idx - coordIndex) * 1000); // increased average salary depending on position
            classStructs[coordIndex].insurance *= (0.01 * (idx - coordIndex) + 1); // increased insurance coverage depending on position
            
        }

    }
    
}

void printClassResults(vector< vector<string> > &originalVec) {

    cout << "PRINTING CLASS RESULTS" << endl;

    for (int i = 0; i < idx; i++) {

        int x = indexOrder[i].first;
        int y = indexOrder[i].second; 

        cout << "For zone " << x << "," << y << " ("; 
        if (originalVec[x][y] == "R") { cout << "RESIDENTIAL) : " << endl;}
        else if (originalVec[x][y] == "I") { cout << "INDUSTRIAL) : " << endl;}
        else if (originalVec[x][y] == "C") { cout << "COMMERCIAL) : " << endl;}

        cout << "> Queue Order:" << i << endl;
        cout << "> Mortality:" << classStructs[i].mortality << "%" << endl; 
        cout << "> Annual Salary: $" << classStructs[i].mortality << endl; 
        cout << "> Insurance Coverage:" << classStructs[i].mortality << "%" << endl; 

    } 

}

int promptDeath(vector< vector<int> > &copyVec) {

    int deaths = 0;
    for (int i = 0; i < idx; i++) { 

        int x = indexOrder[i].first;
        int y = indexOrder[i].second; 

        deaths += (copyVec[x][y] * classStructs[i].mortality); 

    } 

    cout << "A total of " << deaths << " people have passed away." << endl;
    return deaths;  

}
