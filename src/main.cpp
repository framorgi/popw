#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdint>
#include <cstdlib> 
#include <ctime> 
#include <omp.h>
#include "popworld.h"


int main() 
{
    int choice;

         #ifdef _OPENMP
        std::cout << "OpenMP abilitato con " << omp_get_max_threads() << " thread.\n";
        #else
        std::cout << "OpenMP NON abilitato!\n";
        #endif
        
        std::cout<< "####### POPW #######"<<std::endl;
        
        POPWORLD pw;
        pw.Go();
        std::cout<< "####### POPW END #######"<<std::endl;

        std::cout<< "Starting BRAIN-SCOPE - PlotNet"<<std::endl;
      
        std::stringstream ss; 
        ss <<"python ../scripts/PlotNet.py "<< p.VsizeS << " "<<p.VsizeN <<" "<<p.VsizeY;
        std::string cmd = ss.str();
        system(cmd.c_str()); 

}
