#include "pop.h"
#include <cassert>  // Per assert()

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
Coord Pop::Rotate90CW(Coord loc)
{
    Coord wRet;
    wRet.x=loc.y;
    wRet.y=-loc.x;
 
    return wRet;
}
void Pop::ComputeLastDirection(Coord newLoc, Coord oldLoc)
{
    Coord lastdir;
    lastdir.x=newLoc.x-oldLoc.x;
    assert( lastdir.x>= -1.0 && lastdir.x <= 1.0);
    lastdir.y=newLoc.y-oldLoc.y;
    assert( lastdir.y>= -1.0 && lastdir.y <= 1.0);
    if (lastdir.x!=0||lastdir.y!=0)
        state_.lastDirection=lastdir;

    
}
Coord Pop::Rotate90CCW(Coord loc)
{
    Coord wRet;
    wRet.x=-loc.y;
    wRet.y=loc.x;
 
    return wRet;
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
        case Sensor::TEMP:
        {

           // std::cout<<"return minOut + (x - min) * (maxOut - minOut) / (max -min)"<< std::endl;
            //std::cout<<"return "<<(float)p.minTemp <<" + ("<<state_.temperature <<" - "<< 0.0f <<") * ("<<(float)p.maxTemp <<" - "<<(float)p.minTemp <<") / ("<<1.0f <<" -"<< 0.0f <<")"<< std::endl;
            
            //val = Normalize_float(state_.temperature,(float)p.minTemp-30, (float)p.maxTemp+30,   0.0f, 1.0f);
          val= Random_double(0.0f, 1.0f);
        }
        break;
        case Sensor::GENETIC_SIM_FWD:
        {
            val = Random_double(0.0f, 1.0f);
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
            val = (float)state_.lastDirection.x*0.5+0.5 ;
        }
        break;
        case Sensor::LAST_MOVE_DIR_Y : 
        {
            val = (float)state_.lastDirection.y*0.5+0.5 ;
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
            val = sin(state_.age)*0.5+0.5;
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

        
            
        case Sensor::TEMP_AVG_S  :
        {
            
            val = field.GetTempAvg(GetLoc(),S,phy_.sensitiveness);
            val=Normalize_float(val,(float)p.minTemp, (float)p.maxTemp,   0.0f, 1.0f);
        }
        break;
        case Sensor::TEMP_AVG_N  :
        {
            val = field.GetTempAvg(GetLoc(),N,phy_.sensitiveness);
            val=Normalize_float(val,(float)p.minTemp, (float)p.maxTemp,   0.0f, 1.0f);
        }
        break;

        case Sensor::TEMP_AVG_W  :
        {
            val = field.GetTempAvg(GetLoc(),W,phy_.sensitiveness);
            val=Normalize_float(val,(float)p.minTemp, (float)p.maxTemp,   0.0f, 1.0f);
        }
        break;

        case Sensor::TEMP_AVG_E  :
        {
            val = field.GetTempAvg(GetLoc(),E,phy_.sensitiveness);
            val=Normalize_float(val,(float)p.minTemp, (float)p.maxTemp,   0.0f, 1.0f);
        }
        break;
        case Sensor::TEMP_DRV_S  :
        {
            val = field.GetTempDirectionalDerivative(GetLoc(),S,phy_.sensitiveness); 
        }
        case Sensor::TEMP_DRV_E  :
        {
            val = field.GetTempDirectionalDerivative(GetLoc(),E,phy_.sensitiveness); 
        }

        case Sensor::TEMP_DRV_N  :
        {
            val = field.GetTempDirectionalDerivative(GetLoc(),N,phy_.sensitiveness); 
        }
        break;
        case Sensor::TEMP_DRV_W  :
        {
            val = field.GetTempDirectionalDerivative(GetLoc(),W,phy_.sensitiveness); 
        }
        break;
        case Sensor::SENSE_SIGNAL  :
        {
            //TODO
            val = field.GetFeromoneAt(GetLoc(),Feromone_t::fA);
        }
        break;

        case Sensor::SENSE_SIGNAL_DRV_E  :
        {
            val = field.GetFeromoneDirectionalDerivative(GetLoc(),E,phy_.sensitiveness,Feromone_t::fA);
        }
        break;
        case Sensor::SENSE_SIGNAL_DRV_S  :
        {
            val = field.GetFeromoneDirectionalDerivative(GetLoc(),S,phy_.sensitiveness,Feromone_t::fA);
        }
        break;
  
        case Sensor::SENSE_SIGNAL_DRV_N  :
        {
            val = field.GetFeromoneDirectionalDerivative(GetLoc(),N,phy_.sensitiveness,Feromone_t::fA);
        }
        break;
        case Sensor::SENSE_SIGNAL_DRV_W  :
        {
            val = field.GetFeromoneDirectionalDerivative(GetLoc(),W,phy_.sensitiveness,Feromone_t::fA);
        }   
        break;
        case Sensor::GLUCOSE_DENSITY_N  :
        {
            val = field.GetGlucoseDensity(GetLoc(),W,phy_.sensitiveness);
        }   
        break;
        case Sensor::GLUCOSE_DENSITY_W  :
        {
            val = field.GetGlucoseDensity(GetLoc(),W,phy_.sensitiveness);
        }   
        break;
        case Sensor::GLUCOSE_DENSITY_E  :
        {
            val = field.GetGlucoseDensity(GetLoc(),W,phy_.sensitiveness);
        }   
        break;case Sensor::GLUCOSE_DENSITY_S  :
        {
            val = field.GetGlucoseDensity(GetLoc(),W,phy_.sensitiveness);
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
    
   // std::cout<<"Return val
    //std::cout<< " ----EXIT SENSE "<<magic_enum::enum_name(a)<< " ["<<val <<"] "<<std::endl;

    assert( val>= 0.0 && val <= 1.0);
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

    energyCost_+=1;
    if (state_.temperature<5)
    {
        energyCost_++;
    }
    //std::cout<<"feedForward --"<<std::endl;
    return brain_.feedForward(sVal);
}

void Pop::MoveTo( Coord newL)
{
    Coord oldL=GetLoc();
    if (field.IsEmptyAt(newL))
        {
            float st= field.Stiffness(oldL,newL);
            if(st<=0)
            { 
                field.UpdateMove(oldL,newL,ID());
                SetAt(newL);
                ComputeLastDirection(newL,newL);
                energyCost_++;
                producedMetabolismHeat_+=0.7;
            }
        } 
}
void Pop::MakeAction(Action action)
{
    switch (action)
    {

    case Action::KILL_FORWARD :
    /* code */
        break;
    
    case Action::MOVE_FORWARD :
    /* code */
    {
        Coord oldLoc= GetLoc();
        Coord newLoc;
        newLoc.x= oldLoc.x+state_.lastDirection.x;
        newLoc.y= oldLoc.y+state_.lastDirection.y;
        MoveTo(newLoc);
    }
        break;
      
    case Action::MOVE_BACKWARD :
    {
        Coord oldLoc= GetLoc();
        Coord newLoc;
        newLoc.x= oldLoc.x-state_.lastDirection.x;
        newLoc.y= oldLoc.y-state_.lastDirection.y;
        MoveTo(newLoc);
    }
    /* code */
    break;
    case Action::MOVE_LEFT:
    /* code */
    {
        Coord oldLoc= GetLoc();
        Coord newLoc;
        Coord newDir=Rotate90CCW(state_.lastDirection);
        newLoc.x= oldLoc.x+newDir.x;
        newLoc.y= oldLoc.y+newDir.y;
        MoveTo(newLoc);
    }
        break;
      
    case Action::MOVE_RIGHT :
    /* code */
    {
        Coord oldLoc= GetLoc();
        Coord newLoc;
        Coord newDir=Rotate90CW(state_.lastDirection);
        newLoc.x= oldLoc.x+newDir.x;
        newLoc.y= oldLoc.y+newDir.y;
        MoveTo(newLoc);
    }
        break;


    case Action::MOVE_NORTH:
    /* code */
    {
        Coord oldLoc= GetLoc();
        Coord newLoc;
        newLoc.x= oldLoc.x;
        newLoc.y= oldLoc.y+1;
        MoveTo(newLoc);
    }
        break;

    case Action::MOVE_RANDOM:
    {
        Coord oldLoc= GetLoc();
        Coord newLoc;
        newLoc.x= oldLoc.x+Random_int(-1,1);
        newLoc.y= oldLoc.y+Random_int(-1,1);
        MoveTo(newLoc);
    }
    /* code */
    break;
    
   
    case Action::MOVE_EAST :

    {
        Coord oldLoc= GetLoc();
        Coord newLoc;
        newLoc.x= oldLoc.x+1;
        newLoc.y= oldLoc.y;
        if (field.IsEmptyAt(newLoc))
        MoveTo(newLoc);
    }
        break;
    case Action::MOVE_SOUTH  :
    {
        Coord oldLoc= GetLoc();
        Coord newLoc;
        newLoc.x= oldLoc.x;
        newLoc.y= oldLoc.y-1;
        MoveTo(newLoc);
    }
        break;
  
    case Action::MOVE_WEST  :
    {
        Coord oldLoc= GetLoc();
        Coord newLoc;
        newLoc.x= oldLoc.x-1;
        newLoc.y= oldLoc.y;
        MoveTo(newLoc);
    }  
         break;
    case Action::EMIT_SIGNAL  :
    {

        EmitSignal();
        
    }
     break;

    case Action::BURN_CALORIES  :
    /* code */
    {
        produceMetabolismHeat();
    }
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
    state_.lastDirection.x=0.0;
    state_.lastDirection.y=0.0;
    state_.alive=true;
    state_.age=0;
    state_.energy=50;
    state_.temperature=25;
    state_.organics.lipids=20;
    state_.organics.c6h12o6=20;
    phy_.chloroplasts=Random_int(0,2);
    phy_.mitochondrions=Random_int(1,3);
    phy_.sensitiveness=Random_int(1,6);
    NewGenome();
    geneticColor_=makeGeneticColor(genome_);
    brain_.WireBrain(genome_);
    //brain_.ToCsV(id_);
}
void Pop::InitLife(Genome g,Phy p, Organics o)
{
   

    state_.lastDirection.x=0.0;
    state_.lastDirection.y=0.0;
    state_.alive=true;
    state_.age=0;
    state_.energy=50;
    state_.temperature=25;
    SetOrganics(o);
    SetPhy(p);
    SetGenome(g);
    geneticColor_=makeGeneticColor(genome_);
    brain_.WireBrain(genome_);
    //brain_.ToCsV(id_);
}
void Pop::Die()
{
    state_.alive=false;
    
    //std::cout<<"Pop ["<<ID() <<"] Releasing ["<<state_.organics.c6h12o6<<"] "<<std::endl;
    assert( state_.organics.c6h12o6>= 0&&state_.organics.c6h12o6<1000000000);
    //define a mass energy to translate into c6h12o6
    int mass=state_.organics.lipids*2+5;
    field.ReleaseResourceAt(GetLoc(), state_.organics.c6h12o6+mass,state_.organics.caco3,state_.organics.h2o,state_.organics.co2,state_.organics.n2,state_.organics.o2 );
    field.RemoveAt(GetLoc());
}
void Pop::SetNewDropLocation()
{
    Coord myLoc= GetLoc();
    
    childDropLocation_.x= myLoc.x+Random_int(-1,1);
    childDropLocation_.y= myLoc.y+Random_int(-1,1);

}
void Pop::EmitSignal()
{
    Feromone_t type=fA;
    float quantity=1;

    field.ReleaseFeromoneAt(GetLoc(), quantity, type);
    //std::cout<<"ReleaseFeromoneAt"<<std::endl;
}
bool Pop::CheckForReplication()
{
    bool go=false;
    if(  state_.alive
    && ( state_.age>30)
    //&& ((state_.organics.c6h12o6)>5)
    && ((state_.energy)>6)
    && ( state_.temperature>20))
        {
            // Is there any  place behind?
            SetNewDropLocation();
           
            if (field.IsEmptyAt(childDropLocation_)&& field.Stiffness(GetLoc(),childDropLocation_)<=0)
                {
                    //std::cout<<"Reserving Location ["<< loc.<<"] on field"<<std::endl;
                    //field.ReserveLocation(dropLoc);
                    go=true;
                }
        }
    return go;
}
Pop* Pop::TryReplication()
{
    Pop* child= nullptr;
    if (CheckForReplication())
    {
        child = ReplicateMyself();
        
    }
    return child;
    
}

Pop* Pop::ReplicateMyself()
{
    Pop* child= new Pop();
    child->ID(UniqueID::generateStringID()) ;
    child->SetAt(childDropLocation_);
    field.SpawnAt( child->GetLoc(), child->ID());
    Organics o;
    //state_.organics.c6h12o6-=5;
    o.c6h12o6= 5;
    //state_.organics.lipids-=5;
    o.lipids= 5;
    state_.energy-=6;
    Genome newgenome=Mutate(genome_);
    child->InitLife(newgenome,phy_,o);
    return child;
}

Genome Pop::Mutate(Genome g)
{
    Genome newg;
    int i=0;
    for (auto &gene : g)
    {
        if (i%20==0)
        {
            //std::cout <<"mutation occurred"<<std::endl;
            Gene mutatedgene=makeRandomGene();
            newg.push_back(mutatedgene);
        }
        else{
            newg.push_back(gene);
        }
        i++;
    }
    return newg;
}
void Pop::StepOfLife()
{
    
    energyCost_=0;
    producedMetabolismHeat_=0;
    assert( state_.organics.c6h12o6>= 0 && state_.organics.c6h12o6<=100);
    //take reousrces from field
    TakeFromField();
    // do phy things
    StepMetabolism();
    //neural network think
    int a=ThinkWhatToDo();

    // TODO Check ThinkWhatToDo() return values and range
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
        Die();
        //std::cout <<"DIE WTH NO ENERGY"<<std::endl;
    }   
}

void Pop::produceMetabolismHeat() // is a wilful brain action
{
       // should be 0.01 - 0.1
        producedMetabolismHeat_+=1;
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
            if (state_.organics.c6h12o6>100)
                {
                    if (state_.organics.lipids<= phy_.adiposeStockMax)
                        state_.organics.lipids++; //storage excess
                }
            else
                {
                    state_.organics.c6h12o6++;
                    //std::cout<<"I took glucose from field!"<< state_.organics.c6h12o6<<"]"<<std::endl;
                }

        assert( state_.organics.c6h12o6>= 0&&state_.organics.c6h12o6<1000000000);
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
            energyCost_-=2;
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
   double maxLipidsRef=80;//phy_.adiposeStockMax;
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