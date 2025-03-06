#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <cstdlib> 
#include <ctime> 

#include "popworld.h"


int main() 
{
    int choice;

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
