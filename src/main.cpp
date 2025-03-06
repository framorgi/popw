#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> 
#include <ctime> 

#include "popworld.h"


int main() 
{
    int choice;

        std::cout<< "START POPW "<<std::endl;
        
        POPWORLD pw;
        pw.Go();
        system("python PlotNet.py"); 

}
