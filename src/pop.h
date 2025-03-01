#ifndef POP_H_
#define POP_H_

#pragma once 
#include <iostream>
#include <vector>
#include <string>
#include "genome.h"
#include "brain.h"

class Pop
{
    public:
    Pop();
    Pop(int x,int y);
    private:
    int x_;
    int y_;
    int id_;
    int geneticColor_;
    bool alive_;
    Genome genome_;
    Brain brain_;
    public:
    
    int X() {return x_;}
    void X(int v) {x_=v;}

    int Y() {return y_;}
    void Y(int v) {y_=v;}

    int ID() {return id_;}
    void ID(int v) {id_=v;}
    
    int GeneticColor() {return geneticColor_;}
    void GeneticColor(int v) {geneticColor_=v;}

    void SetAt(Coord newLoc);
    Coord GetLoc();
    void Act();
    void NewGenome();
    void InitLife();
    void WireBrain();

};




#endif //"POP_H_"
