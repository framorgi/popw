#ifndef FIELD_H_
#define FIELD_H_
#pragma once
#include "common.h"
#include <cmath>
#include <cstdlib>
#include <vector>
#include <ctime>
#define ROWS 128
#define COL 128

const int num_gaussiane = rand() % 5 + 3; // Numero casuale di gaussiane tra 3 e 7
const double MIN_VAL = 10.0;
const double MAX_VAL = 30.0;

struct GaussianBaseFunction{
    double x0, y0;    // Posizione della gaussiana
    double ampiezza;  // Altezza della gaussiana
    double sigma;     // Deviazione standard
};

typedef struct 
{
    bool occupy;
    bool selectionArea;
    float temp;
    void* pop_ptr;
    int id;
 
   
}planetSlice;


class Field  //the sim arena
{
    public:

    Field();
    Field(int size);
    void InitPlanet();
    void InitPlanet(int size);
    void SpawnPopsOnPlanet();
    void SetSelectionArea();
    std::vector<std::vector<planetSlice>> planet_;

    private:

    int size_y;
    int size_x;

    
   
    double EvaluateGaussian(double x, double y, const GaussianBaseFunction& base);
  
    void GenTemperatureField();
    public:
    void SpawnAt(Coord loc, int ID);
    Coord FindEmptyCell();
    bool IsEmptyAt(Coord loc);
    bool IsInBound(Coord loc);
    void UpdateMove(Coord oldLoc,Coord newLoc,int ID);
};



#endif //"FIELD_H_"
