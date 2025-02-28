#include "popworld.h"

//globals
Field field;
PopsSpv spv_;
ParamManager paramManager;
const Params &p { paramManager.getParamRef() };


POPWORLD::POPWORLD()
{
    std::cout<< "Init popworld container."<<std::endl;
    paramManager.setDefaults();
    paramManager.registerConfigFile("../src/param.ini");
    paramManager.updateFromConfigFile(0);
    paramManager.checkParameters(); // check and report any problems
    std::cout<< "Size "<<p.size<<std::endl;
    std::cout<< "Population "<<p.population<<std::endl;
    std::cout<< "Generations "<<p.maxGenerations<<std::endl;
    std::cout<< "Run per generation "<<p.runsPerGeneration<<std::endl;
    stats_.foods=0;
    stats_.pops=0;
    stats_.run=0;
    stats_.size=p.size;
    stats_.year=0;
    stats_.generation=0;
    imagerPtr_=new Imager(p.size);
    field= Field(p.size);
    

    spv_.CreatePopulation(p.population,p.size);
    
}


void POPWORLD::Go()
{
    Generation();
}

void POPWORLD::Generation()
{
    for (int i=0; i<p.runsPerGeneration;i++)
        
    {
        SingleRun();
    }
    stats_.generation++;


}
void POPWORLD::SingleRun()
{
    std::cout<<"Run ["<<stats_.run <<"]"<<std::endl;
    spv_.RunPopsMove();
 
    imagerPtr_->UpdateDraw(stats_.run);
   
     stats_.run++;
} 