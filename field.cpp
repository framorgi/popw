#include "field.h"

Field::Field()
{
    InitPlanet();
}
void Field::InitPlanet()
{
    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COL;j++)
        {
            planet[i][j].occupy=false;
            planet[i][j].selectionArea=false;
        }

}

void Field::SpawnPopsOnPlanet()
{
    for(int i=0;i<ROWS;i++)
        {
            planet[i][0].occupy=true;
            Pop p = Pop(i,0);
        }

}
void Field::SetSelectionArea()
{
    for(int i=0;i<ROWS;i++)
        for(int j=COL-5;j<COL;j++)
        {
            planet[i][j].selectionArea=true;
        }

}