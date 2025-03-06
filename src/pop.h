#ifndef POP_H_
#define POP_H_

#pragma once 
#include <iostream>
#include <vector>
#include <string>
#include "common.h"
#include "genome.h"
#include "field.h"
#include "brain.h"

extern Field field;
typedef struct
{
    unsigned c6h12o6;
    unsigned lipids;  //can be transformed into energy and reduce temperature exchange factor  [0.01 - 0.5]
    unsigned o2;
    unsigned co2;
    unsigned h2o;
    unsigned n2;
    unsigned caco3; 
    
}Organics ;
typedef struct
{
    unsigned energy;
    double temperature;
    bool alive;
    Coord position;
    Organics organics;
}StateVars;


typedef struct
{
    unsigned mitochondrions; //quantity of mitochondrions defines aerobic respiration and so Glycolysis  capacity
    unsigned chloroplasts;  //quantity of chloroplasts defines solar sensitivity and photosynthesis capacity
    float    sensitiveness;   // sensor stimuli sensitiveness
    unsigned adiposeStockMax; // max quantity of fat storage permitted  

}Phy;

class Pop
{
    public:
    Pop();
    Pop(int x,int y);
    private:
    StateVars state_;
    Phy phy_;
    int id_;
    int energyCost_;
    int producedMetabolismHeat_;
    int geneticColor_;
    
    Genome genome_;
    Brain brain_;
    public:
    
    int X() {return state_.position.x;}
    void X(int v) {state_.position.x=v;}

    int Y() {return state_.position.y;}
    void Y(int v) {state_.position.y=v;}

    bool Alive(){return state_.alive;}

    int ID() {return id_;}
    void ID(int v) {id_=v;}
    
    int GeneticColor() {return geneticColor_;}
    void GeneticColor(int v) {geneticColor_=v;}
    
    float Temp(){return state_.temperature;}
    unsigned Energy(){return state_.energy;}
    
    void SetAt(Coord newLoc);
    Coord GetLoc();
    int ThinkWhatToDo();
    void MakeAction(Action action);
    void NewGenome();
    void InitLife();

    void Die();

    void StepOfLife();
    void EnergyBalance();
    void produceMetabolismHeat();
    void TakeFromField();
    void RunChloroplasts();
    void RunMitochondrions();
    void StepMetabolism();
    void updateTemperature();
    double computeAlpha( double maxLipidsRef, double alphaMin, double alphaMax);
};

#endif //"POP_H_"
