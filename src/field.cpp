#include "field.h"

Field::Field()
{
    srand(time(0)); // Inizializza il generatore di numeri casuali
    
}
Field::Field(int size)
{
    planetSlice p;
    std::cout<< "Init Field class. Size "<< size<<std::endl;
    planet_ =  std::vector<std::vector<planetSlice>>(size, std::vector<planetSlice>(size, p));
    srand(time(0)); // Inizializza il generatore di numeri casuali
    InitPlanet( size );
   

}
void Field::InitPlanet()
{
    for(int i=0;i<ROWS;i++) //y
        for(int j=0;j<COL;j++) //x
        {
            planet_[i][j].occupy=false;
            planet_[i][j].selectionArea=false;
            planet_[i][j].pop_ptr=nullptr;
        }
        GenTemperatureField();
        GenHeightMapField();

}
void Field::InitPlanet(int size )
{
    size_x=size;
    size_y=size;
    for(int i=0;i<size_y;i++)
        for(int j=0;j<size_x;j++)
        {
            planet_[i][j].occupy=false;
            planet_[i][j].selectionArea=false;
            planet_[i][j].pop_ptr=nullptr;
            planet_[i][j].id="";
        }
        GenTemperatureField();
        GenHeightMapField();
        GenResources();
        
}

void Field::SpawnPopsOnPlanet()
{
    std::cout<< "Spawning pops on grid"<<std::endl;
 
            Coord c= FindEmptyCell();
    
            planet_[c.y][c.x].occupy=true;
            //planet_[c.y][c.x].pop_ptr =p;
        

}
void Field::SetSelectionArea()
{
    for(int i=0;i<ROWS;i++)
        for(int j=COL-5;j<COL;j++)
        {
            planet_[i][j].selectionArea=true;
            
        }

}

float Field::Stiffness(Coord oldLoc,Coord newLoc)
{
    return  planet_[newLoc.y][newLoc.x].height - planet_[oldLoc.y][oldLoc.x].height ;
}
float Field::TemperatureAt(Coord p)
{
    
    return planet_[p.y][p.x].temp;
}

resourcesContainer &Field::GetResourcesAt(Coord p)
{
    
    return  planet_[p.y][p.x].resources;
}

float Field::GetTmpAt(Coord loc)
{
     return planet_[loc.y][loc.x].temp;
}
float Field::GetTempAvg(Coord p,Dir dir,int sensitiveness)
{
    int places=0;
    float tmp=0;
    Coord startP;
    switch (dir)
    {
        case Dir::N:
        {         
            startP.x=p.x-sensitiveness;
            startP.y=p.y-sensitiveness;
            for(int i=startP.y;i<startP.y+(2*sensitiveness)+1;i++) //y
            {  for(int j=startP.x;j<startP.x+(sensitiveness);j++) //x
                {
                    Coord loc;
                    loc.x=j;
                    loc.y=i;
                    if (IsInBound(loc))
                    {
                        places++;
                        if (!IsEmptyAt(loc))
                        {   
                            tmp+=TemperatureAt(loc);
                        }
                    }
                   
                }
            }         
        }
        break;
        case Dir::E: //ok
        {
            
            startP.x=p.x+sensitiveness;
            startP.y=p.y+sensitiveness;
            for(int i=startP.y;i>startP.y-(2*sensitiveness)-1;i--)
            {   
              
                for(int j=startP.x;j>startP.x -sensitiveness;j--)
                {
                 
                    Coord loc;
                    loc.x=j;
                    loc.y=i;
                    if (IsInBound(loc))
                    {
                        places++;
                        if (!IsEmptyAt(loc))
                        {   
                            tmp+=TemperatureAt(loc);
                        }
                    }
                   
                }
            }
        }

        break;
        case Dir::S:
        {   
            
            startP.x=p.x-sensitiveness;
            startP.y=p.y+1;
            for(int i=startP.y;i<startP.y+(2*sensitiveness)+1;i++) //y
            {   for(int j=startP.x;j<startP.x+(sensitiveness);j++) //x
                {
                    Coord loc;
                    loc.x=j;
                    loc.y=i;
                    if (IsInBound(loc))
                    {
                        places++;
                        if (!IsEmptyAt(loc))
                        {   
                            tmp+=TemperatureAt(loc);
                        }
                    }
                   
                }
            }
           
        }

        break;
        case Dir::W:  //ok
        {
          
            startP.x=p.x-sensitiveness;
            startP.y=p.y-sensitiveness;
            for(int i=startP.y;i<startP.y+(2*sensitiveness)+1;i++) //y
            { 
                for(int j=startP.x;j<startP.x+(sensitiveness);j++) //x
                {
                    Coord loc;
                    loc.x=j;
                    loc.y=i;
                    //std::cout<< "Looking...     i["<< i<<"]    j["<< j<<"]"<< std::endl;
                    if (IsInBound(loc))
                    {
                        places++;
                        if (!IsEmptyAt(loc))
                        {   
                           
                            tmp+=TemperatureAt(loc);
                        }
                    }
                }
            }
           
        }
        break;
        default:
            std::cout<< "GetTempAVG default"<< std::endl;
            return 0;   
        break;
    }

    float ret=places==0?0.0 : tmp /places;
    //std::cout<< "GetTempAVG ["<<tmp <<"]/["<<places <<"]=["<<ret <<"]"<< std::endl;
    return  ret;   
}
float Field::GetPopDensity(Coord p,Dir dir,int sensitiveness)
{ 
    int places=0;
    int occupied=0;
    Coord startP;
    switch (dir)
    {
        case Dir::N:
        {   
           
            startP.x=p.x-sensitiveness;
            startP.y=p.y-sensitiveness;
            for(int i=startP.y;i<startP.y+(2*sensitiveness)+1;i++) //y
            {  for(int j=startP.x;j<startP.x+(sensitiveness);j++) //x
                {
                    Coord loc;
                    loc.x=j;
                    loc.y=i;
                    if (IsInBound(loc))
                    {
                        places++;
                        if (!IsEmptyAt(loc))
                        {   
                            occupied++;
                        }
                    }
                   
                }
            }

          
        }
        break;
        case Dir::E: //ok
        {
            
            startP.x=p.x+sensitiveness;
            startP.y=p.y+sensitiveness;
            for(int i=startP.y;i>startP.y-(2*sensitiveness)-1;i--)
            {   
              
                for(int j=startP.x;j>startP.x -sensitiveness;j--)
                {
                 
                    Coord loc;
                    loc.x=j;
                    loc.y=i;
                    if (IsInBound(loc))
                    {
                        places++;
                        if (!IsEmptyAt(loc))
                        {   
                            occupied++;
                        }
                    }
                   
                }
            }

            
        }

        break;
        case Dir::S:
        {   
            
            startP.x=p.x-sensitiveness;
            startP.y=p.y+1;
            for(int i=startP.y;i<startP.y+(2*sensitiveness)+1;i++) //y
            {   for(int j=startP.x;j<startP.x+(sensitiveness);j++) //x
                {
                    Coord loc;
                    loc.x=j;
                    loc.y=i;
                    if (IsInBound(loc))
                    {
                        places++;
                        if (!IsEmptyAt(loc))
                        {   
                            occupied++;
                        }
                    }
                   
                }
            }
           
        }

        break;
        case Dir::W:  //ok
        {
          
            startP.x=p.x-sensitiveness;
            startP.y=p.y-sensitiveness;
            for(int i=startP.y;i<startP.y+(2*sensitiveness)+1;i++) //y
            { 
                for(int j=startP.x;j<startP.x+(sensitiveness);j++) //x
                {
                    Coord loc;
                    loc.x=j;
                    loc.y=i;
                    //std::cout<< "Looking...     i["<< i<<"]    j["<< j<<"]"<< std::endl;
                    if (IsInBound(loc))
                    {
                        places++;
                        if (!IsEmptyAt(loc))
                        {   
                            //std::cout<< "FOUND POP at WEST  i["<< loc.y<<"] j["<< loc.x<<"]"<< std::endl;
                            occupied++;
                        }
                    }
                }
            }
           
        }
        break;
        default:
            std::cout<< "GetPopDensity default"<< std::endl;
            return 0;   
        break;
    }

   
    return  places==0? 0.0: (float)occupied /places;   
}
void Field::ReleaseResourceAt(Coord p, int c6h12o6,int caco3, int h2o,int co2,int n2, int o2 )
{
    planet_[p.y][p.x].resources.c6h12o6+=c6h12o6;
    planet_[p.y][p.x].resources.caco3+=caco3;
    planet_[p.y][p.x].resources.h2o+=h2o;
    planet_[p.y][p.x].resources.co2+=co2;
    planet_[p.y][p.x].resources.n2+=n2;
    planet_[p.y][p.x].resources.o2+=o2;
}
float Field::HeightAt(Coord p)
{
    return planet_[p.y][p.x].height;
}

// Calcola il valore della gaussiana in un punto (x, y)
double Field::EvaluateGaussian(double x, double y, const GaussianBaseFunction& g) {
    double dx = x - g.x0;
    double dy = y - g.y0;
    return g.ampiezza * exp(-(dx * dx + dy * dy) / (2 * g.sigma * g.sigma));
}


void Field::GenTemperatureField()
{
    const int num_gaussiane = Random_int(3,7); // Numero casuale di gaussiane tra 3 e 7
    double min_val = 1e9, max_val = -1e9;
    //Init basis functions
    std::vector<GaussianBaseFunction> basis(num_gaussiane);
    for (auto& g : basis) {
        g.x0 = Random_double(0, size_y - 1);
        g.y0 = Random_double(0, size_x - 1);
        g.ampiezza = Random_double(p.minTemp, p.maxTemp);
        g.sigma = Random_double(p.tempSigmaMin, p.tempSigmaMax);
    }  
       // Calcola i valori della funzione nella matrice
       for (int i = 0; i < size_y; ++i) {
        for (int j = 0; j < size_x; ++j) {
            double valore = 0.0;
            for (const auto& g : basis) {
                valore += EvaluateGaussian(i, j, g);
            }
            planet_[i][j].temp = valore;
           
            min_val = std::min(min_val, valore);
            max_val = std::max(max_val, valore);
        }
    }

    // Normalizzazione nell'intervallo 
    for(int i=0;i<size_y;i++)
    for(int j=0;j<size_x;j++)
    {
       // planet_[i][j].temp = p.minTemp + (p.maxTemp - p.minTemp) * ((planet_[i][j].temp- min_val) / (max_val - min_val));
       planet_[i][j].temp= Normalize_float(planet_[i][j].temp,min_val,max_val,p.minTemp,p.maxTemp);
    }
  
}
void Field::GenHeightMapField()
{
    const int num_gaussiane = rand() % 8 + 3; // Numero casuale di gaussiane tra 3 e 7
    double min_val = 1e9, max_val = -1e9;
    //Init basis functions
    std::vector<GaussianBaseFunction> basis(num_gaussiane);
    for (auto& g : basis) {
        g.x0 = Random_double(0, size_y - 1);
        g.y0 = Random_double(0, size_x - 1);
        g.ampiezza = Random_double(p.minHeight, p.maxHeight);
        g.sigma = Random_double(p.heightSigmaMin, p.heightSigmaMax);
    }  
       // Calcola i valori della funzione nella matrice
       for (int i = 0; i < size_y; ++i) {
        for (int j = 0; j < size_x; ++j) {
            double valore = 0.0;
            for (const auto& g : basis) {
                valore += EvaluateGaussian(i, j, g);
            }
            planet_[i][j].height= valore;
            min_val = std::min(min_val, valore);
            max_val = std::max(max_val, valore);
        }
    }


    // Normalizzazione nell'intervallo 
    for(int i=0;i<size_y;i++)
        for(int j=0;j<size_x;j++)
        {
           //planet_[i][j].height = p.minHeight + (p.maxHeight - p.maxHeight) * ((planet_[i][j].height- min_val) / (max_val - min_val));
        }
    
}

void Field::GenResources()
{
    SpawnBasicRandomResources();
    SpawnWaterDeposit();
}
void Field::SpawnWaterDeposit()
{
    const int num_gaussiane = Random_int(1,10); // Numero casuale di gaussiane tra 3 e 7
   
    //Init basis functions
    std::vector<GaussianBaseFunction> basis(num_gaussiane);
    for (auto& g : basis) {
        g.x0 = Random_double(0, size_y - 1);
        g.y0 = Random_double(0, size_x - 1);
        g.ampiezza = Random_double(100, 120);
        g.sigma = Random_double(20, 30);
    }  
       // Calcola i valori della funzione nella matrice
       for (int i = 0; i < size_y; ++i)
        {
            for (int j = 0; j < size_x; ++j) 
            {
                int valore = 0.0;
                for (const auto& g : basis) 
                {
                    valore += (int)EvaluateGaussian(i, j, g);
                }
                planet_[i][j].resources.h2o= valore;
            
            }
    }

}
void Field::SpawnBasicRandomResources()
{
    for(int i=0;i<size_y;i++)
        for(int j=0;j<size_x;j++)
        {
        planet_[i][j].resources.c6h12o6=Random_int(0,20); 
        planet_[i][j].resources.caco3=Random_int(0,10); 
        planet_[i][j].resources.co2=Random_int(10,20); 
        planet_[i][j].resources.h2o=Random_int(1,20); 
        planet_[i][j].resources.o2=Random_int(1,20); 
        }
}

Coord Field::FindEmptyCell() 
 {
    Coord loc;

    while (true) {
        loc.x = Random_int(0, size_x - 1);
        loc.y = Random_int(0, size_y - 1);
        if (IsEmptyAt(loc)) {
            break;
        }
    }
    return loc;
}

void Field::ReserveLocation(Coord loc)
{
    
    planet_[loc.y][loc.x].occupy=false;
    planet_[loc.y][loc.x].reserved=true;
    planet_[loc.y][loc.x].id="";
}
void Field::SpawnAt(Coord loc, std::string ID)
{
    std::cout<<"Spawning pop ["<< ID<<"] on field at location  ["<< loc.y<<"] ["<< loc.x<<"]"<<std::endl;
    planet_[loc.y][loc.x].occupy=true;
    planet_[loc.y][loc.x].id=ID;
}
void Field::RemoveAt(Coord loc)
{
    planet_[loc.y][loc.x].occupy=false;
    planet_[loc.y][loc.x].id="";
    
    if (IsEmptyAt(loc))
        std::cout<<"Removed pop on field at location  ["<< loc.y<<"] ["<< loc.x<<"]"<<std::endl;
}
bool Field::IsEmptyAt(Coord loc)
{   
   
    if (IsInBound(loc))
        return planet_[loc.y][loc.x].occupy? false:true;
    else
        return false;
}
void Field::UpdateMove(Coord oldLoc,Coord newLoc,std::string ID)
{
   
    planet_[oldLoc.y][oldLoc.x].occupy=false;
    planet_[oldLoc.y][oldLoc.x].id="";

    
    planet_[newLoc.y][newLoc.x].occupy=true;
    planet_[newLoc.y][newLoc.x].id=ID;
    
}

bool Field::IsInBound(Coord loc)
{
    return (loc.y>=0 &&loc.x>=0 && loc.x<size_x && loc.y<size_y);
}