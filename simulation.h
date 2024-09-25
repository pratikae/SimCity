#ifndef SIMULATION_H
#define SIMULATION_H
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Global variable so it can be used 
extern int total_pollution;
extern int time_step;
extern int available_workers;
extern int available_goods;
extern int vecRows; 
extern int vecCols;
extern int refresh_rate; 
extern int num_deaths; 
extern int num_injured;
extern int cemetery;
extern int idx; 

class Simulation {
    public:

    // Constructor to read and store configuration info
        Simulation(istream &input, vector< vector<string> > &output);

    // Function to perform simulation operations
        void runSimulation(); 

    private:
};

#endif
