#ifndef POPSSPV_H_
#define POPSSPV_H_

#pragma once 
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include"field.h"
#include "pop.h"


using namespace std;

extern Field field;
 
class PopsSpv
{
    public:
    PopsSpv();
  
    std::map<int ,Pop* > alivePops_;
    std::vector<Pop*> deadPops_;
 
    
    std::map<int ,Pop* >  AlivePopPtr() {return alivePops_;}
    int population_;

    void CreatePopulation(int population, int size);
    void RunPopsMove();



};




#endif //"POPSSPV_H_"
