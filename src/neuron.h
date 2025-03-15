#ifndef NEURON_H_
#define NEURON_H_

#pragma once 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include <magic_enum.hpp>

using namespace std;


 
enum Sensor {
    LOC_X,             // I distance from left edge
    LOC_Y,             // I distance from bottom
    BOUNDARY_DIST_X,   // I X distance to nearest edge of world
    BOUNDARY_DIST,     // I distance to nearest edge of world
    BOUNDARY_DIST_Y,   // I Y distance to nearest edge of world
    GENETIC_SIM_FWD,   // I genetic similarity forward
    LAST_MOVE_DIR_X,   // I +- amount of X movement in last movement
    LAST_MOVE_DIR_Y,   // I +- amount of Y movement in last movement
    LONGPROBE_POP_FWD, // W long look for population forward
    LONGPROBE_BAR_FWD, // W long look for barriers forward
    POPULATION_DENSITY_N,    // 
    POPULATION_DENSITY_W,    // 
    POPULATION_DENSITY_E,    // 
    POPULATION_DENSITY_S,    // 
    POPULATION_LR,     // W population density in the left-right axis
    OSC1,              // I oscillator +-value
    AGE,               // I
    BARRIER_FWD,       // W neighborhood barrier distance forward-reverse axis
    BARRIER_LR,        // W neighborhood barrier distance left-right axis
    RANDOM,            //   random sensor value, uniform distribution
    SIGNAL0,           // W strength of signal0 in neighborhood
    SIGNAL0_FWD,       // W strength of signal0 in the forward-reverse axis
    SIGNAL0_LR,        // W strength of signal0 in the left-right axis
    NUM_SENSES,        // <<------------------ END OF ACTIVE SENSES MARKER
};

 
enum Action {
    MOVE_X,                   // W +- X component of movement
    MOVE_Y,                   // W +- Y component of movement
    MOVE_FORWARD,             // W continue last direction
    MOVE_RL,                  // W +- component of movement
    MOVE_RANDOM,              // W
    SET_OSCILLATOR_PERIOD,    // I
    SET_LONGPROBE_DIST,       // I
    SET_RESPONSIVENESS,       // I
    EMIT_SIGNAL0,             // W
    MOVE_EAST,                // W
    MOVE_WEST,                // W
    MOVE_NORTH,               // W
    MOVE_SOUTH,               // W
    MOVE_LEFT,                // W
    MOVE_RIGHT,               // W
    MOVE_REVERSE,             // W
    NUM_ACTIONS,       // <<----------------- END OF ACTIVE ACTIONS MARKER
    KILL_FORWARD,             // W
};


void exportOutputToCSV(const std::string& filename);
void exportSensorToCSV(const std::string& filename);


#endif //"NEURON_H_"
