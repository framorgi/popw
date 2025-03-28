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

    POPULATION_DENSITY_N,    // 
    POPULATION_DENSITY_W,    // 
    POPULATION_DENSITY_E,    // 
    POPULATION_DENSITY_S,    // 
    TEMP_AVG_N,              //         
    TEMP_AVG_W,              //       
    TEMP_AVG_E,              //       
    TEMP_AVG_S,              //   
    TEMP_DRV_N,              //
    TEMP_DRV_W,              //
    TEMP_DRV_E,              // 
    TEMP_DRV_S,              //
    SENSE_SIGNAL,            //
    SENSE_SIGNAL_DRV_N,      //
    SENSE_SIGNAL_DRV_W,      //
    SENSE_SIGNAL_DRV_E,      //
    SENSE_SIGNAL_DRV_S,      //
    GLUCOSE_DENSITY_N,       //
    GLUCOSE_DENSITY_W,       //
    GLUCOSE_DENSITY_E,       //
    GLUCOSE_DENSITY_S,       //
    OSC1,              // I oscillator +-value
    AGE,               // I
    TEMP,              // I
    RANDOM,            //   random sensor value, uniform distribution

    NUM_SENSES,        // <<------------------ END OF ACTIVE SENSES MARKER
};

 
enum Action {
    MOVE_FORWARD,             // W continue last direction
    MOVE_BACKWARD,            // W
    MOVE_LEFT,                // W
    MOVE_RIGHT,               // W
    MOVE_RANDOM,              // W
    MOVE_EAST,                // W
    MOVE_WEST,                // W
    MOVE_NORTH,               // W
    MOVE_SOUTH,               // W
    SET_OSCILLATOR_PERIOD,    // I
    SET_LONGPROBE_DIST,       // I
    SET_RESPONSIVENESS,       // I
    EMIT_SIGNAL,              // W
    BURN_CALORIES,            // W

 
    NUM_ACTIONS,       // <<----------------- END OF ACTIVE ACTIONS MARKER
    KILL_FORWARD,             // W
};


void exportOutputToCSV(const std::string& filename);
void exportSensorToCSV(const std::string& filename);


#endif //"NEURON_H_"
