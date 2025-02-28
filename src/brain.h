#ifndef BRAIN_H_
#define BRAIN_H_

#pragma once 
#include <iostream>
#include <vector>
#include <string>
//#include "neuron.h"


using namespace std;

//typedef vector<Net> NNet;

 
class Brain
{
    public:
    Brain();
   
    private:
    //NNet net_
    int y_;
    bool alive_;

    public:
    


    void Act();




};




#endif //"BRAIN_H_"
