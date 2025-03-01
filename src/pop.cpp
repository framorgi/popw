#include "pop.h"

Pop::Pop()
{
  
}
Pop::Pop(int x,int y):
x_(x),y_(y_)
{
    
}
void Pop::SetAt(Coord newLoc)
{
    x_=newLoc.x;
    y_=newLoc.y;
}
Coord Pop::GetLoc()
{  Coord c;
    c.y=y_;
    c.x=x_;
    return c;
}
void Pop::Act()
{
    
}
void Pop::NewGenome()
{
    genome_ = makeRandomGenome();
}

void Pop::InitLife()
{
    alive_=true;
    NewGenome();
    geneticColor_=makeGeneticColor(genome_);
}

void Pop::WireBrain()
{
   
}
