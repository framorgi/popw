#include "popsspv.h"

PopsSpv::PopsSpv()
{
    std::cout<<"Created PopsSpv"<<std::endl;

}

//put pops on the arena
void PopsSpv::CreatePopulation(int population, int size)
{
    population_=population;
    for (int i=0;i<population_; i++)
    {
        Pop* popPtr= new Pop();
        popPtr->ID(i);
        popPtr->InitLife();
        Coord c=field.FindEmptyCell();
        field.SpawnAt(c,popPtr->ID());
        popPtr->X(c.x);
        popPtr->Y(c.y);
        alivePops_[i]=popPtr;
        
    }
    std::cout<<"PopsSpv created "<<population << "pops."<<std::endl;
    

}

void PopsSpv::RunPopsMove( )
{
    for (int i=0;i<population_; i++)
    {   
       
        Coord oldLoc= alivePops_[i]->GetLoc();
   
        Coord newLoc;
        newLoc.x= oldLoc.x+1;
        newLoc.y= oldLoc.y+1;
        if (field.IsEmptyAt(newLoc))
        {
           
            field.UpdateMove(oldLoc,newLoc,alivePops_[i]->ID());
            alivePops_[i]->SetAt(newLoc);
            //std::cout<<"Pop  of "<<alivePops_[i]->ID() << std::endl;
        }
        
        
    }
}