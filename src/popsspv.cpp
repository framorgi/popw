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
        std::string id= UniqueID::generateStringID() ;
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
        popPtr->ID( id );
        popPtr->InitLife();
        Coord c=field.FindEmptyCell();
        field.SpawnAt(c,popPtr->ID());
        popPtr->X(c.x);
        popPtr->Y(c.y);
        alivePops_[id]=popPtr;
        //std::cout<<"Pops created with id [ "<<id << "]."<<std::endl;
        //std::cout<<"Pop test get  popPtr->ID() [ "<<popPtr->ID() << "]."<<std::endl;
        //std::cout<<"Pop test get  GetLoc [ "<<popPtr->GetLoc().y << "][ "<<popPtr->GetLoc().x << "]."<<std::endl;
       // std::cout<<"Pop test field occurrence [ "<< popPtr->GetLoc().y<< "]-[ "<<popPtr->GetLoc().x << "]----> ID["<<field.planet_[popPtr->GetLoc().y][popPtr->GetLoc().x].id  <<"]."<<std::endl;
    assert(field.planet_[popPtr->GetLoc().y][popPtr->GetLoc().x].id ==popPtr->ID());
    }
    std::cout<<"PopsSpv created "<<population << "pops."<<std::endl;
    

}
void PopsSpv::CorpsesCollector()
{
    for ( auto p: toRemove)
    {
       // std::cout<<"Deleting pop ["<<p <<"]"<<std::endl;
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
        assert(pop.second!=nullptr);
        if ( pop.second)
        {

            //std::cout<<"Start new Loop alivePops_ ["<< pop.second->ID()<<"]"<<std::endl;
            if ( pop.second->Alive())
            {
            // std::cout<<"Snap for pop["<< pop.first<<"]"<<std::endl;
            pop.second->StepOfLife();
            Pop* child= pop.second->TryReplication();
                if(child)
                {
                    std::cout<<"New child pop  in queue []"<<std::endl;
                    childrenPops_.push_back(child);
                } 
                //std::cout << "Alive pops: " << alivePops_.size() << ", Children: " << childrenPops_.size() << std::endl;
            
            }
            else
            {  std::cout<<"Found dead pop ["<< pop.first<<"]"<<std::endl;

            population_--;
            toRemove.push_back(pop.first);  
            }
        }
    }
    
    for (auto& pop :childrenPops_)
    { 
        population_++;
        
        //std::cout<<"Spawing new child to reserved location ["<<pop->ID()<<"]"<<std::endl;
       // field.SpawnAt(pop->GetLoc(),pop->ID());
        std::cout<<"Inserting new child to Alive queue ["<< pop->ID()<<"]"<<std::endl;
        alivePops_[pop->ID()]=pop;
    }
    childrenPops_.clear();
   
   // std::cout<<"---"<<std::endl;
}