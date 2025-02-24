#ifndef FIELD_H_
#define FIELD_H_
#include "pop.h"
#define ROWS 128
#define COL 128
typedef struct 
{
    bool occupy;
    bool selectionArea;
   
}planetMatrix;


class Field  //the sim
{
    Field();

    planetMatrix planet[ROWS][COL];
    public:
    
    void InitPlanet();
    void SpawnPopsOnPlanet();
    void SetSelectionArea();
};




#endif //"FIELD_H_"
