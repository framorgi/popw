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
void PopsSpv::CorpsesCollector()
{
    for ( auto p: toRemove)
    {
        delete alivePops_[p];
        alivePops_.erase(p);
        std::cout<<"Removed pop ["<<p <<"]"<<std::endl;
    }
    
    toRemove.clear();
}
void PopsSpv::RunPopsMove( )
{
    
    for (auto& pop :alivePops_)
    {   
       if ( pop.second->Alive())
        {
            std::cout<<"Snap for pop["<< pop.first<<"]"<<std::endl;
            pop.second->StepOfLife();
        }
        else
        {
            std::cout<<"Found dead pop ["<< pop.first<<"]"<<std::endl;
            population_--;
            toRemove.push_back(pop.first);  
        }
    }

   

}