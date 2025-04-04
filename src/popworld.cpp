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
    paramManager.registerConfigFile("../config/param.ini");
    paramManager.updateFromConfigFile(0);
    paramManager.checkParameters(); // check and report any problems
    exportSensorToCSV(p.nnetsDir+"sense.csv");
    exportOutputToCSV(p.nnetsDir+"out.csv");
    std::cout<< "Size "<<p.size<<std::endl;
    std::cout<< "MaxTemp "<<p.maxTemp<<std::endl;
    std::cout<< "MinTemp "<<p.minTemp<<std::endl;
    std::cout<< "tempSigmaMax "<<p.tempSigmaMax<<std::endl;
    std::cout<< "tempSigmaMin "<<p.tempSigmaMin<<std::endl;
    std::cout<< "maxHeight "<<p.maxHeight<<std::endl;
    std::cout<< "MinHeight "<<p.minHeight<<std::endl;
    std::cout<< "heightSigmaMax "<<p.heightSigmaMax<<std::endl;
    std::cout<< "heightSigmaMin "<<p.heightSigmaMin<<std::endl;
    std::cout<< "Population "<<p.population<<std::endl;
    std::cout<< "Generations "<<p.maxGenerations<<std::endl;
    std::cout<< "Run per generation "<<p.runsPerGeneration<<std::endl;
    stats_.foods=0;
    stats_.pops=0;
    stats_.run=0;
    stats_.size=p.size;
    stats_.year=0;
    stats_.generation=0;
    field= Field(p.size);
    imagerPtr_=new Imager(p.size);
   
    imagerPtr_->UpdateDraw(stats_.run);
    spv_.CreatePopulation(p.population,p.size);
    
}


void POPWORLD::Go()
{
    Generation();
    imagerPtr_->ReleaseVideoEditor();
}

void POPWORLD::Generation()
{   
    Timer gt("Generation");
    gt.start();
    for (int i=0; i<p.runsPerGeneration;i++)
        
    {
        if (spv_.alivePops_.size()==0)
            break;
        SingleRun();
    }
    stats_.generation++;
    gt.stop();


}
void POPWORLD::SingleRun()
{
    //Timer pt("Run");
    //Timer rt("Render");
    spv_.CorpsesCollector();
    std::cout<<"Run ["<<stats_.run <<"]"<<std::endl;
    //pt.start();
    spv_.RunPopsMove();
   // pt.stop();
    //rt.start();
    //std::cout<<"Draw"<<std::endl;
    imagerPtr_->UpdateDraw(stats_.run);
    field.DecayFeromones();
    field.UpdateTemperatureField();
   // rt.stop();
    //imagerPtr_->SavePNG(stats_.run);

    stats_.run++;
} 