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
    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COL;j++)
        {
            planet_[i][j].occupy=false;
            planet_[i][j].selectionArea=false;
            planet_[i][j].pop_ptr=nullptr;
        }
        GenTemperatureField();

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
            planet_[i][j].id=-1;
        }
        GenTemperatureField();
        
}

void Field::SpawnPopsOnPlanet()
{
    std::cout<< "Spawning pops on grid"<<std::endl;
 
            Coord c= FindEmptyCell();
    
            planet_[c.x][c.y].occupy=true;
            //planet_[c.x][c.y].pop_ptr =p;
        

}
void Field::SetSelectionArea()
{
    for(int i=0;i<ROWS;i++)
        for(int j=COL-5;j<COL;j++)
        {
            planet_[i][j].selectionArea=true;
            
        }

}




// Calcola il valore della gaussiana in un punto (x, y)
double Field::EvaluateGaussian(double x, double y, const GaussianBaseFunction& g) {
    double dx = x - g.x0;
    double dy = y - g.y0;
    return g.ampiezza * exp(-(dx * dx + dy * dy) / (2 * g.sigma * g.sigma));
}


void Field::GenTemperatureField()
{
    const int num_gaussiane = rand() % 5 + 3; // Numero casuale di gaussiane tra 3 e 7
    double min_val = 1e9, max_val = -1e9;
    //Init basis functions
    std::vector<GaussianBaseFunction> basis(num_gaussiane);
    for (auto& g : basis) {
        g.x0 = Random_double(0, size_y - 1);
        g.y0 = Random_double(0, size_x - 1);
        g.ampiezza = Random_double(10, 50);
        g.sigma = Random_double(8, 15);
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

    // Normalizzazione nell'intervallo [-20, 55]
    for(int i=0;i<size_y;i++)
        for(int j=0;j<size_x;j++)
        {
            planet_[i][j].temp = MIN_VAL + (MAX_VAL - MIN_VAL) * ((planet_[i][j].temp- min_val) / (max_val - min_val));
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


void Field::SpawnAt(Coord loc, int ID)
{
    planet_[loc.x][loc.y].occupy=true;
    planet_[loc.x][loc.y].id=ID;
}
bool Field::IsEmptyAt(Coord loc)
{
    if (IsInBound(loc))
        return planet_[loc.x][loc.y].occupy? false:true;
    else
        return false;
}
void Field::UpdateMove(Coord oldLoc,Coord newLoc,int ID)
{
    planet_[oldLoc.x][oldLoc.y].occupy=false;
    planet_[oldLoc.x][oldLoc.y].id=-1;

    
    planet_[newLoc.x][newLoc.y].occupy=true;
    planet_[newLoc.x][newLoc.y].id=ID;
}

bool Field::IsInBound(Coord loc)
{
    return (loc.x<size_x && loc.y<size_y);
}