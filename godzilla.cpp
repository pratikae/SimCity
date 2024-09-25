#include "Godzilla.h"
#include <cstdlib>
#include <ctime>

Godzilla::Godzilla() { srand(time(0)); } //initialize and set random time

//function to generate random coordinates within the bounds of vecRows and vecCols
Coords Godzilla::generateRandomCoords(int x, int y) { 
  Coords coords;
  coords.x = rand() % x;
  coords.y = rand() % y;
  return coords;
}

//Function that attacks different types of cells
void Godzilla::attack(char cell) {
  cout << "Godzilla is attacking!!!!" << endl;
  cout << "          \\  /" << endl;
  cout << "   ______/\\0_0______" << endl;
  cout << " /                    \\ " << endl;
  cout << " |    |      |       |" << endl;
  cout << " \\    | (    |    (  |" << endl;
  cout << "  |   | |    |    |  |" << endl;
  cout << "  |__ | |____|____|__|" << endl;
  cout << "  \\__/|___________|__/" << endl;
  cout << "     |_|_|     |_|_|" << endl;

  //if the cell is industrial, kill workers and destroy goods (also any adjacent powerplants but thats in a diff function)
  if (cell == 'I') {
    int num = rand() % power; //power of Godzilla increases every time its called
    killWorkers(num);
    destroyGoods(num);
  } else if (cell == 'C') { //if cell is commericial, destroy goods
    int num = rand() % power;
    destroyGoods(num);
  } else if (cell == 'R') { //if cell is residential, kill people
    int num = rand() % power;
    killPeople(num);
  }
}

//function to see if Godzilla is still alive
bool Godzilla::isAlive() const { return health > 0; }

//function to return health
int Godzilla::getHealth() const { return health; }

//function to getPower
int Godzilla::getPower() const { return power; }

//see if there is a powerline in an adjacent cell, and if there is, kill godzilla
bool Godzilla::powerLineFound(vector<vector<string> > &originalVec, int i,
                              int j) {
  for (int m = i - 1; m < i + 2; m++) {
    for (int n = j - 1; n < j + 2; n++) {
      if (m < vecRows && n < vecCols && m >= 0 && n >= 0) {
        if ((originalVec[m][n] == "T" || originalVec[m][n] == "#") &&
            !(m == i &&
              n == j)) { // checking whether adjacent cell is powerline
          health--;
          return true;
        }
      }
    }
  }
  return false;
}

//destroy the powerline and replace it with an empty cell
void Godzilla::deletePowerLines(vector<vector<string> > &originalVec, int i,
                                int j) {
  for (int m = i - 1; m < i + 2; m++) {
    for (int n = j - 1; n < j + 2; n++) {
      if (m < vecRows && n < vecCols && m >= 0 && n >= 0) {
        if (originalVec[m][n] == "T" || originalVec[m][n] == "#") {
          originalVec[m][n] =
              " "; 
        }
      }
    }
  }
}

//function to get all the info from randomized cell
void Godzilla::getCell(vector<vector<string> > originalVec) {
  //generate random coords to attack
  Coords ranCoords = generateRandomCoords(vecRows, vecCols);
  char cell;
  //see what type of cell it is
  if (originalVec[ranCoords.x][ranCoords.y] == "R") {
    cell = 'R';
    attack(cell);
  } else if (originalVec[ranCoords.x][ranCoords.y] == "I") {
    if (powerLineFound(originalVec, ranCoords.x, ranCoords.y)) { //if its industrial, see if there are any powerlines
      deletePowerLines(originalVec, ranCoords.x, ranCoords.y); //and if so, destroy those powerlines
      cell = 'I';
      attack(cell);
    } else {
      cell = 'I';
      attack(cell);
    }
  } else if (originalVec[ranCoords.x][ranCoords.y] == "C") {
    cell = 'C';
    attack(cell);
  } else {
    cell = 'N'; //if cell is empty or not of any of the above types, don't do anything
  }
}

//function to kill workers and add deaths
void Godzilla::killWorkers(int num) {
  available_workers -= num;
  numdeaths += num;
}

//function to destroy goods and add numGoods destroyed
void Godzilla::destroyGoods(int num) {
  available_goods -= num;
  numGoods += num;
}

//function to kill people and add to numDeaths
void Godzilla::killPeople(int num) {
  available_workers -= num;
  numdeaths += num;
}

//function to run Godzilla
void Godzilla::runGodzilla(vector<vector<string> > &originalVec) {
  if (isAlive()) {
    getCell(originalVec);
    cout << "Godzilla killed " << numdeaths << " people and destroyed "
         << numGoods << " goods!!!" << endl;
    power++;
  } else {
    cout << "RAAAAA!!!!!!!!!" << endl;

    cout << "          \\  /" << endl;
    cout << "   ____/\\XXX_XXX____" << endl;
    cout << " /                    \\ " << endl;
    cout << " |    |      |       |" << endl;
    cout << " \\    | (    |    (  |" << endl;
    cout << "  |   | |    |    |  |" << endl;
    cout << "  |__ | |____|____|__|" << endl;
    cout << "  \\__/|___________|__/" << endl;
    cout << "     |_|_|     |_|_|" << endl;

    cout << "Godzilla is dead!!!" << endl;
  }
}
