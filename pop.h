#ifndef POP_H_
#define POP_H_

#pragma once 
#include <iostream>
#include <vector>
#include <string>
#include "brain.h"
typedef int Gene;
using namespace std;

typedef vector<Gene> Genome;

 
class Pop
{
    public:
    Pop();
    Pop(int x,int y);
    private:
    int x_;
    int y_;
    bool alive_;
    Genome genome_;
    Brain brain_;
    public:
    
    int X() {return x_;}
    void X(int v) {x_=v;}

    int Y() {return y_;}
    void Y(int v) {y_=v;}

    void Act();




};




#endif //"POP_H_"
