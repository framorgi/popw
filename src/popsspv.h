#ifndef POPSSPV_H_
#define POPSSPV_H_

#pragma once 
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include"field.h"
#include "common.h"
#include "pop.h"


using namespace std;

extern Field field;
 
class PopsSpv
{
    public:
    PopsSpv();
  
    std::map<std::string ,Pop* > alivePops_;
    std::vector<Pop*> deadPops_;
    std::vector<std::string> toRemove;
    std::vector<Pop*> childrenPops_;
    
    std::map<std::string ,Pop* >  AlivePopPtr() {return alivePops_;}
    int population_;

    void CreatePopulation(int population, int size);
    void RunPopsMove();
    void CorpsesCollector();



};




#endif //"POPSSPV_H_"
