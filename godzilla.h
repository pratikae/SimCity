/*
Godzilla Functionality, written by Chloe Huang
*/

#ifndef GODZILLA_H
#define GODZILLA_H

#include "commercial.h"
#include "industrial.h"
#include "residential.h"
#include "simulation.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

//structure to hold values of x, y for coordinates
struct Coords {
  int x;
  int y;
};

//define class Godzilla
class Godzilla {
public:
  //initializer
  Godzilla();
  //function to runGodzilla
  void runGodzilla(vector<vector<string> > &originalVec);
  Coords generateRandomCoords(int x, int y);
  void attack(char cell);
  bool isAlive() const;
  int getHealth() const;
  int getPower() const;
  bool powerLineFound(vector<vector<string> > &originalVec, int i, int j);
  void getCell(vector<vector<string> > originalVec);
  void deletePowerLines(vector<vector<string> > &originalVec, int i, int j);
  void killWorkers(int num);
  void destroyGoods(int num);
  void killPeople(int num);

private:
  int health = 1; //Godzilla has 1 health, if it hits a powerline, it dies
  int power = 1; //power starts at 1, increases with time_steps
  int numdeaths = 0; //store total num of deaths
  int numGoods = 0; // store total numGoods destroyed
};

#endif
