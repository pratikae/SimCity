#include "death.h"
#include <iterator> 
#include <algorithm>
#include <cmath>
//death component by phoebe kim

/* Functionalities:
    > disease depends location to pollution
        > hierarchy: cell's individual pollution, then cell's adjacent pollution
    > mortality is calculated from disease and the population vector is updated to decrease cell population according to mortality
    > every 5 deaths creates one cemetery plot
	    > max is 3 plots, over max will increase disease
    > rat infestation (random : ))
	    > rat infestation will get delete goods and increase disease
*/

//function: to get some variable of the adjacent cells, specifically used for death
//return: returns an integer value 
//parameters: 2d vector, int i- the x coordinate, int j- the y coordinate
int death_adj_numbers(vector< vector<int> > &vec, int i, int j){
    int num = 0;
    for (int m = i-1; m < i+2; m++){ //iterating through adjacent cells :3
        for (int n = j-1; n < j+2; n++){
            if (m < vecRows && n < vecCols && m >= 0 && n >= 0){ //checking bounds of the vector
                if (vec[m][n] >= 1 && !(m == i && n == j)){ //check if cell has value
                    num += vec[m][n];
                }
            }
        }
    }
    return num;
}

//object: contains information on singular cell
struct DeathCell{
    int index[2]; //xy-coordinates
    int population; //cell population
    int pollution; //cell pollution
    int adjPollution; //adjacent cells pollution
    float mortality; //percent of deaths calculated from disease and classism
    float injured; //percent of injured calculated from disease and classism
    int diseases; //amount of diseases in cell
};

//function: used to sort Cell object in cells vector by greatest to least according to cell pollution
bool compareByPollution(const DeathCell &a, const DeathCell &b)
{
    return a.pollution > b.pollution;
}

//function: used to sort Cell object in cells vector by greatest to least according to adjacent pollution
bool compareByAdjPollution(const DeathCell &a, const DeathCell &b)
{
    return a.adjPollution > b.adjPollution;
}

//function: initializing InjuredVec
void initializeInjuredVec(vector< vector<int> > &injuredVec){
    vector<int> injuredTempVec;
    for(int i = 0; i < vecRows; i++){
        for (int j = 0; j < vecCols; j++){
            injuredTempVec.push_back(0);
        }
        injuredVec.push_back(injuredTempVec);
    }
}

//function: creates rat infestation and disease/calculates number of deaths and injured from disease
void death(vector< vector<int> > &copyVec, vector< vector<string> > &originalVec, vector< vector<int> > &pollutionVec, vector< vector<int> > &injuredVec, vector<string> &cemeteryVec){
    vector<DeathCell> cells; //vector to store object called DeathCell
    int disease_count = 0; //diseases from rat infestation
    vector<vector<int> > diseaseVec; //visualizing disease spread if needed
    vector<int> diseaseTempVec; //vector to initialize disease vec

    //initializing diseaseVec
    for(int i = 0; i < vecRows; i++){
        for (int j = 0; j < vecCols; j++){
            diseaseTempVec.push_back(0);
        }
        diseaseVec.push_back(diseaseTempVec);
    }

    //creating cemeteries based on disease deaths
    if (num_deaths >= 5){
        int num_cemetery = num_deaths / 5; //one cemetery is 5 deaths
        num_deaths = num_deaths % 5; //reset disease variable with remaining death count
        if (cemetery > 5){ //if there are too many cemeteries, then increase disease
            disease_count += cemetery;
        }
        else{
            for (int i = 0; i < num_cemetery; i++){
                cemeteryVec.push_back("D"); //creating cemetery
            }
            cemetery += num_cemetery;
        }
    }

    for (int i = 0; i < vecRows; i++) { //iterating through vector
        for (int j = 0; j < vecCols; j++) {
            if (copyVec[i][j] != -1){
                int adjPollution = death_adj_numbers(pollutionVec, i, j);

                DeathCell temp = {{i, j}, copyVec[i][j], pollutionVec[i][j], adjPollution, 0, 0, 0}; //creating temporary Cell object
                cells.push_back(temp); //adding cell to vector
            }
        }
    }

    //random rat infestion
    int rand_num = rand() % 20 + 1;
    if (rand_num == 3){
        cout << endl;
        cout << "(o)(o)--." << endl;
        cout << " \\../ (  )hjw" << endl;
        cout << "m\\/m--m'`--." << endl;
        cout << "   ____" << endl;
        cout << "  /|o  |" << endl;
        cout << " /o|  o|" << endl;
        cout << "/o_|_o_|   -Row" << endl;
        //Small mice by Joan Stark, from https://www.asciiart.eu/animals/rodents/mice
        cout << "Oh nooOOoooOoo, a rat infestation decimated your industrial and commercial districts..." << endl;
        cout << "People petted the rats and caught diseases..." << endl;
        cout << "The rats kept eating all the goods... back to zero goods :(" << endl;
        available_goods = 0; //deleting all goods
        disease_count++; //increasing disease count
    }

    sort(cells.begin(), cells.end(), compareByPollution); //sorting cells vector by individual cell pollution (greatest to least)

    vector<DeathCell>::iterator it_begin = cells.begin();
    vector<DeathCell>::iterator it_end = cells.begin();
    int j = 1;
    it_end++;

    //sorting by cells by adjacent pollution> if there is equal pollution in two or more cells
    for (int i = 0; i < cells.size(); i++) {
        if (cells[i].pollution == it_end->pollution){
            while (cells[i].pollution == it_end->pollution && it_end != cells.end()){
                j++;
                it_end++;
            }
        }

        sort(it_begin, it_end, compareByAdjPollution);

        if (j < cells.size()){
            i = j;
            it_begin = it_end;
            continue;
        }
        else{
            break;
        }
    }

    //checking whether sorting is working
    // for(int i = 0; i < cells.size(); i++){
    //     cout << "POLLUTION: " << cells[i].pollution << endl;
    //     cout << "COORDS: " << cells[i].index[0] << " " << cells[i].index[1] << endl;
    // }

    //updating disease vector with disease and spreading disease to adjacent cells only if cell has population
    if (cells[0].pollution > 8){
        for (int i = 0; i < cells.size(); i++){
            if (cells[i].pollution > 8 && cells[i].diseases < 4){
                cells[i].diseases++;
                // cout << "Disease: " << cells[i].diseases << endl;
                int row = cells[i].index[0];
                int col = cells[i].index[1];
                diseaseVec[row][col] = cells[i].diseases;
                for (int m = row-1; m < row+2; m++){ //iterating through adjacent cells :3
                    for (int n = col-1; n < col+2; n++){
                        if (m < vecRows && n < vecCols && m >= 0 && n >= 0){ //checking bounds of the vector
                            if (copyVec[m][n] >= 1 && !(m == row && n == col)){ //check if cell has population
                                diseaseVec[m][n] += 1;
                            }
                        }
                    }
                }
            }
        }
    }

    //visualize disease vector
    // cout << "DISEASE VEC" << endl;
    // for (int i = 0; i < vecRows; i++){
    //     for(int j = 0; j < vecCols; j++){
    //         cout << diseaseVec[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    //updating death count and injured vector with 
    for (int i = 0; i < cells.size(); i++){
        int row = cells[i].index[0];
        int col = cells[i].index[1];
        cells[i].diseases = diseaseVec[row][col];

        if (originalVec[row][col] == "C" || originalVec[row][col] == "I"){
            cells[i].diseases += disease_count;
            disease_count = 0;
        }

        cells[i].mortality = cells[i].diseases; //changeable formula for deaths if needed
        cells[i].injured = cells[i].diseases; //given to healthcare component

        injuredVec[row][col] += cells[i].injured;
        num_deaths += cells[i].mortality;
        // cout << num_deaths << "DEATHS!!!" << endl;

        copyVec[row][col] = copyVec[row][col] - round(copyVec[row][col]*cells[i].mortality); //decrease population according to mortality percent
    }
    return;
}

//function: prints out cemetery vector at end of simulation
void printCemetery(vector<string> &cemeteryVec){
    cout << "Cemetary:"<< endl;
    for (int i = 0; i < cemeteryVec.size(); i++){
        cout << cemeteryVec[i] << " ";
    }
    cout << endl;
}
