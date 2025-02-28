#ifndef POPWORLD_H_
#define POPWORLD_H_

#pragma once 
#include <iostream>
#include "field.h"
#include "popsspv.h"
#include "common.h"
#include "params.h"
#include "imager.h"



extern Field field;
extern   PopsSpv spv_;
extern const Params &p; 
class POPWORLD
{

    public:
    POPWORLD();

    void Go();






    private:
    //sim utils
    RunTimeStatistics stats_;
    Imager* imagerPtr_=nullptr;
 

    //sim objects
    
 

    //methods
    void Generation();
    void SingleRun();
};




#endif //"POPWORLD_H_"
