#ifndef FIELD_H_
#define FIELD_H_
#pragma once
#include "common.h"
#include "params.h"
#include <cmath>
#include <cstdlib>
#include <vector>
#include <ctime>
#define ROWS 128
#define COL 128

extern const Params &p;

struct GaussianBaseFunction{
    double x0, y0;    // Posizione della gaussiana
    double ampiezza;  // Altezza della gaussiana
    double sigma;     // Deviazione standard
};

typedef struct 
{
    unsigned c6h12o6;
    unsigned o2;
    unsigned co2;
    unsigned h2o;
    unsigned n2;
    unsigned caco3; 
}
resourcesContainer;
typedef struct 
{
    resourcesContainer resources;
    bool occupy;
    bool selectionArea;
    float temp;
    void* pop_ptr;
    int id;
    float height;

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
    float TemperatureAt(Coord p);
    resourcesContainer& GetResourcesAt(Coord p);
   
    void ReleaseResourceAt(Coord p, int c6h12o6, int caco3, int h2o, int co2, int n2, int o2);
    float HeightAt(Coord p);

private:

    int size_y;
    int size_x;

    
   
    double EvaluateGaussian(double x, double y, const GaussianBaseFunction& base);
  
    void GenTemperatureField();
    void GenHeightMapField();
    void GenResources();

    void SpawnWaterDeposit();

    void SpawnBasicRandomResources();

public:
    void SpawnAt(Coord loc, int ID);
    void RemoveAt(Coord loc);
    Coord FindEmptyCell();
    bool IsEmptyAt(Coord loc);
    bool IsInBound(Coord loc);
    void UpdateMove(Coord oldLoc,Coord newLoc,int ID);
};



#endif //"FIELD_H_"
