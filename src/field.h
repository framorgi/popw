#ifndef FIELD_H_
#define FIELD_H_
#pragma once
#include "common.h"
#include "params.h"
#include <cmath>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <map>
#define ROWS 128
#define COL 128

extern const Params &p;

typedef std::map<Feromone_t,float> FeromoneMap;

typedef enum
{
    N,
    NE,
    E,
    SE,
    S,
    SW,
    W,
    NW

}Dir;
struct GaussianBaseFunction{
    double x0, y0;    // Posizione della gaussiana
    double ampiezza;  // Altezza della gaussiana
    double sigma;     // Deviazione standard
};

typedef struct 
{
    int c6h12o6;
    unsigned o2;
    unsigned co2;
    unsigned h2o;
    unsigned n2;
    unsigned caco3; 
}
resourcesContainer;
typedef struct 
{
    FeromoneMap feromones;
    resourcesContainer resources;
    bool reserved;
    bool occupy;
    bool selectionArea;
    float temp;
    void* pop_ptr;
    std::string id;
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
    float Stiffness(Coord oldLoc, Coord newLoc);
    float TemperatureAt(Coord p);
    int GlucoseAt(Coord p);
    resourcesContainer &GetResourcesAt(Coord p);

    float GetTmpAt(Coord loc);

    float GetFeromoneDirectionalDerivative(Coord p, Dir dir, int sensitiveness, Feromone_t type);

    float GetTempDirectionalDerivative(Coord p, Dir dir, int sensitiveness);

    float GetTempAvg(Coord p, Dir dir, int sensitiveness);

    float GetGlucoseDensity(Coord p, Dir dir, int sensitiveness);

    float GetPopDensity(Coord p, Dir dir, int sensibility);

    void ReleaseFeromoneAt(Coord p,float quantity, Feromone_t type);
    FeromoneMap& GetFeromonesAt(Coord p);
    float GetFeromoneAt(Coord p, Feromone_t type);
    void DecayFeromones();
    void UpdateTemperatureField();
    void ReleaseResourceAt(Coord p, unsigned int c6h12o6, unsigned int caco3, unsigned int h2o, unsigned int co2, unsigned int n2, unsigned int o2);
    float HeightAt(Coord p);

private:

    int size_y;
    int size_x;
    std::vector<GaussianBaseFunction> tmpGaussians;
    
   
    double EvaluateGaussian(double x, double y, const GaussianBaseFunction& base);
  
    void GenTemperatureField();
    void GenHeightMapField();
    void GenResources();

    void SpawnWaterDeposit();

    void SpawnBasicRandomResources();

public:
    void ReserveLocation(Coord loc);
    void SpawnAt(Coord loc, std::string ID);
    void RemoveAt(Coord loc);
    Coord FindEmptyCell();
    bool IsEmptyAt(Coord loc);
    bool IsInBound(Coord loc);
    void UpdateMove(Coord oldLoc,Coord newLoc,std::string ID);
};



#endif //"FIELD_H_"
