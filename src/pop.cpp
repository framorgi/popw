#include "pop.h"

Pop::Pop()
{
  
}
Pop::Pop(int x,int y)
{
    state_.position.x=x;
    state_.position.y=y;
}
void Pop::SetAt(Coord newLoc)
{
    state_.position=newLoc;

}
Coord Pop::GetLoc()
{  
    return state_.position;
}

float Pop::Sense(Sensor a)
{
    float val=0;;
    //std::cout<< " ----ENTER  SENSE "<<magic_enum::enum_name(a)<< std::endl;
    switch (a)
    {
        case Sensor::AGE:
        {
            val = (float)state_.age / p.runsPerGeneration;
        }
        break;
        case Sensor::GENETIC_SIM_FWD:
        {
            val = Random_double(0,1);

        }
        
        break;
        case Sensor::BOUNDARY_DIST_X :
        {
            int minDistX = std::min<int>(state_.position.x, (p.size - state_.position.x) - 1);
            val = (float)minDistX / (p.size / 2.0);
        }
        break;
        case Sensor::BOUNDARY_DIST_Y:
        {
            int minDistY = std::min<int>(state_.position.y, (p.size - state_.position.y) - 1);
            val = (float)minDistY / (p.size / 2.0);
        }
        break;
        case Sensor::LAST_MOVE_DIR_X :
        {
            val = Random_double(0,1);
        }
        break;
        case Sensor::LAST_MOVE_DIR_Y :
        {
            val = Random_double(0,1);
        }
        break;
        case Sensor::LOC_X :
        {
            val = (float)state_.position.x / (p.size - 1);        
        }
        break;
        case Sensor::LOC_Y :
        {
            val = (float)state_.position.x / (p.size - 1);
        }
        break;
        case Sensor::OSC1 :
        {
            val = Random_double(0,1);
        }
        break;
        case Sensor::POPULATION_DENSITY_N :
        {
            
            val = field.GetPopDensity(GetLoc(),N,phy_.sensitiveness);
        }
        break;
        case Sensor::POPULATION_DENSITY_W :
        {
            
            val = field.GetPopDensity(GetLoc(),W,phy_.sensitiveness);
            
        }
        break;
        case Sensor::POPULATION_DENSITY_E :
        {
   
           
            val = field.GetPopDensity(GetLoc(),E,phy_.sensitiveness);
        }
        break;
        case Sensor::POPULATION_DENSITY_S :
        {
           
            val = field.GetPopDensity(GetLoc(),S,phy_.sensitiveness);
        }
        break;
        case Sensor::POPULATION_LR :
        {
            val = Random_double(0,1);
        }
        
        break;
        case Sensor::RANDOM  :
        {
            val = Random_double(0,1);
        }
        break;

    
    default:
        break;
    }
    
   // std::cout<<"Return val ["<<val <<"] "<<std::endl;
    //std::cout<< " ----EXIT SENSE "<<magic_enum::enum_name(a)<< std::endl;
    return val;
}
int Pop::ThinkWhatToDo()
{
    std::vector<float> sVal;
    for (int i=0;i<p.VsizeS;i++)
    {
        Sensor s= (Sensor)i;
        //std::cout<<" calling Sense ["<<i<<"] "<<magic_enum::enum_name(s)<<std::endl;
        float val=Sense(s);
       // std::cout<<" DONE Sense ["<<i<<"] "<<magic_enum::enum_name(s)<<" -- ["<<val<<"]"<<std::endl;
        sVal.push_back( val );
        
       
    }

    energyCost_++;
    std::cout<<"feedForward --"<<std::endl;
    return brain_.feedForward(sVal);
}
void Pop::MakeAction(Action action)
{
    switch (action)
    {
    case Action::EMIT_SIGNAL0:
        /* code */
        break;
    case Action::KILL_FORWARD :
    /* code */
        break;
    case Action::MOVE_EAST :

    {
        Coord oldLoc= GetLoc();
        Coord newLoc;
        newLoc.x= oldLoc.x+1;
        newLoc.y= oldLoc.y;
        if (field.IsEmptyAt(newLoc))
        {
            field.UpdateMove(oldLoc,newLoc,ID());
            SetAt(newLoc);
        } 
    }
        break;
    case Action::MOVE_FORWARD :
    /* code */
        break;
    case Action::MOVE_LEFT:
    /* code */
    {
        Coord oldLoc= GetLoc();
        Coord newLoc;
        newLoc.x= oldLoc.x-1;
        newLoc.y= oldLoc.y;
        if (field.IsEmptyAt(newLoc))
        {
            field.UpdateMove(oldLoc,newLoc,ID());
            SetAt(newLoc);
        } 
    }
        break;

    case Action::MOVE_NORTH:
    /* code */
    {
        Coord oldLoc= GetLoc();
        Coord newLoc;
        newLoc.x= oldLoc.x;
        newLoc.y= oldLoc.y+1;
        if (field.IsEmptyAt(newLoc))
        {
            field.UpdateMove(oldLoc,newLoc,ID());
            SetAt(newLoc);
        } 
    }
        break;

    case Action::MOVE_RANDOM:
    /* code */
    break;
    case Action::MOVE_REVERSE :
    /* code */
    break;
    case Action::MOVE_RIGHT :
    /* code */
    {
        Coord oldLoc= GetLoc();
        Coord newLoc;
        newLoc.x= oldLoc.x+1;
        newLoc.y= oldLoc.y;
        if (field.IsEmptyAt(newLoc))
        {
            field.UpdateMove(oldLoc,newLoc,ID());
            SetAt(newLoc);
        } 
    }
        break;

    case Action::MOVE_RL:
    /* code */
    break;
    case Action::MOVE_SOUTH  :
    {
        Coord oldLoc= GetLoc();
        Coord newLoc;
        newLoc.x= oldLoc.x;
        newLoc.y= oldLoc.y-1;
        if (field.IsEmptyAt(newLoc))
        {
            field.UpdateMove(oldLoc,newLoc,ID());
            SetAt(newLoc);
        } 
    }
        break;
  
    case Action::MOVE_WEST  :
    {
        Coord oldLoc= GetLoc();
        Coord newLoc;
        newLoc.x= oldLoc.x-1;
        newLoc.y= oldLoc.y;
        if (field.IsEmptyAt(newLoc))
        {
            field.UpdateMove(oldLoc,newLoc,ID());
            SetAt(newLoc);
        } 
    }
        break;

    case Action::MOVE_X  :
    /* code */
    break;
    case Action::MOVE_Y  :
    /* code */
    break;
    case Action::SET_RESPONSIVENESS  :
    /* code */
    break;
    
    default:
        break;
    }
}
void Pop::NewGenome()
{
    genome_ = makeRandomGenome();
}

void Pop::InitLife()
{
    state_.alive=true;
    state_.age=0;
    state_.energy=20;
    state_.temperature=25;
    state_.organics.lipids=20;
    phy_.chloroplasts=Random_int(1,30);
    phy_.mitochondrions=Random_int(1,30);
    phy_.sensitiveness=Random_int(1,3);
    NewGenome();
    geneticColor_=makeGeneticColor(genome_);
    brain_.WireBrain(genome_);
    brain_.ToCsV(std::to_string(id_));
}
void Pop::Die()
{
    std::cout<<"Pop ["<<ID() <<"] is death"<<std::endl;
    field.ReleaseResourceAt(GetLoc(), state_.organics.c6h12o6,state_.organics.caco3,state_.organics.h2o,state_.organics.co2,state_.organics.n2,state_.organics.o2 );
    field.RemoveAt(GetLoc());
}
void Pop::StepOfLife()
{
    
    energyCost_=0;
    producedMetabolismHeat_=0;

    //take reousrces from field
    TakeFromField();
    // do phy things
    StepMetabolism();
    //neural network think
    int a=ThinkWhatToDo();
    //do what decided
    if (a!=-1)
        MakeAction((Action)a);
    //but at what cost?

    state_.age++;
    EnergyBalance();
}

void Pop::EnergyBalance()
{  
    state_.energy-=energyCost_; 
    if (state_.energy<=0)
    {

        state_.alive=false;
        Die();
        
    
    }
}

void Pop::produceMetabolismHeat() // is a wilful brain action
{
       // should be 0.01 - 0.1
        producedMetabolismHeat_+=0.1;
        energyCost_++;
 
}
void Pop::TakeFromField()
{
   
    resourcesContainer& res= field.GetResourcesAt(GetLoc());
    
    if (res.h2o>0)
        {
            res.h2o --;
            state_.organics.h2o++;
        }
    if (res.caco3>0)
        {
            res.caco3 --;
            state_.organics.caco3++;
        }
    if (res.c6h12o6>0)
        {
            res.c6h12o6 --;
            state_.organics.c6h12o6++;
          
        }
    if (res.o2 >0)
        {
            res.o2 --;
            state_.organics.o2++;
        }
    if (res.n2 >0)
        {
            res.n2 --;
            state_.organics.n2++;
        }
    if (res.co2 >0)
        {
            res.co2 --;
            state_.organics.co2++;
        }


}
void Pop::RunChloroplasts()
{
    //Cmin minimum number to achieve  photodynthesis
    //Cmax can probably be overlapped
    int minChloroplasts=20;
    int maxChloroplasts=60;
    if (phy_.chloroplasts>minChloroplasts)
    {
        if (field.HeightAt(GetLoc())>(p.maxHeight/3))  //light condition -- to improve
        {   
            if (state_.organics.co2>0 && state_.organics.h2o>0)
            {
                state_.organics.co2--;
                state_.organics.h2o--;
                double p = (double)(phy_.chloroplasts - minChloroplasts) / (maxChloroplasts - minChloroplasts);
                if(Random_double(0,1) < p)
                {
                    std::cout<<"I made Photosynthesis!"<<std::endl;
                    state_.organics.c6h12o6++;
                    field.ReleaseResourceAt(GetLoc(),0,0,0,0,0,1);  //release oxigen
                }
            }
       }
    }
}
void Pop::RunMitochondrions()
{
   
    for(int i=0;i<phy_.mitochondrions;i++)
    {
        if (state_.organics.c6h12o6>0 && state_.organics.o2>0)
        {
            state_.organics.c6h12o6--;
            state_.organics.o2--;
            energyCost_-=1;
            field.ReleaseResourceAt(GetLoc(),0,0,0,1,0,0);  //release co2
            
        }

    }
}
void Pop::StepMetabolism()
{   
    RunChloroplasts();
    RunMitochondrions();
    updateTemperature();
}
void Pop::updateTemperature() {
   //alpha is a thermal exchange coeff. [0.01 - 0,5]
   //lipids storage increase thermal inertia 
   double maxLipidsRef=80;
   double alphaMax=0.5;
   double alphaMin=0.01;
    double oldTemp= state_.temperature;

   double a=computeAlpha( maxLipidsRef,  alphaMin,  alphaMax);

   //producedMetabolismHeat_ refer to heat produced at the expense of energy units.  // should be 0.01 - 0.1
   double inc= a  * ((double)field.TemperatureAt(GetLoc()) - state_.temperature) + producedMetabolismHeat_;
    state_.temperature += inc;
    //std::cout<< "Old  Temp ["<<oldTemp <<"]   New["<< state_.temperature <<"]  Inc ["<< inc <<"] Ext.temp["<< field.TemperatureAt(GetLoc()) <<"] Alfa ["<< a <<"] Beta["<<producedMetabolismHeat_<<"]"<<std::endl; 
}

double Pop::computeAlpha( double maxLipidsRef, double alphaMin, double alphaMax) 
{   
    double a = alphaMax - (alphaMax - alphaMin) * (state_.organics.lipids / maxLipidsRef);
    //std::cout<< "state_.organics.lipids ["<<state_.organics.lipids <<"]   maxLipidsRef["<< maxLipidsRef <<"]  alphaMax ["<< alphaMax <<"] alphaMin["<< alphaMin <<"] Alfa ["<< a <<std::endl; 
    return a;
}