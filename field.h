#ifndef FIELD_H_
#define FIELD_H_
#include "pop.h"
#define ROWS 128
#define COL 128
typedef struct 
{
    bool occupy;
    bool selectionArea;
    Pop* pop_ptr;
   
}planetMatrix;


class Field  //the sim arena
{
    Field();

    planetMatrix planet[ROWS][COL];
    public:
    
    void InitPlanet();
    void SpawnPopsOnPlanet();
    void SetSelectionArea();
};




#endif //"FIELD_H_"
