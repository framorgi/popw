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
    int energy;
    double temperature;
    bool alive;
    int age;
    Coord position;
    Coord lastDirection;
    Organics organics;
}StateVars;


typedef struct
{
    unsigned mitochondrions;    // quantity of mitochondrions defines aerobic respiration and so Glycolysis  capacity
    unsigned chloroplasts;      // quantity of chloroplasts defines solar sensitivity and photosynthesis capacity
    unsigned sensitiveness;     // sensor stimuli sensitiveness
    unsigned adiposeStockMax;   // max quantity of fat storage permitted  


}Phy;

class Pop{
    public:
    Pop();
    Pop(int x,int y);
    private:
    StateVars state_;
    Phy phy_;
    std::string id_;
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

    std::string ID() {return id_;}
    void ID(std::string v) {id_=v;}
    
    int GeneticColor() {return geneticColor_;}
    void GeneticColor(int v) {geneticColor_=v;}
    
    float Temp(){return state_.temperature;}
    int Energy(){return state_.energy;}
    unsigned Mitochondrions(){return phy_.mitochondrions;}
    unsigned Chloroplasts(){return phy_.chloroplasts;}
    unsigned Sensitiveness(){return phy_.sensitiveness;}
    void SetAt(Coord newLoc);
    Coord Rotate90CW(Coord loc);
    void ComputeLastDirection(Coord newLoc, Coord oldLoc);
    Coord LastDirection(){return state_.lastDirection;};
    Coord Rotate90CCW(Coord loc);
    Coord GetLoc();
    float Sense(Sensor a);
    int ThinkWhatToDo();
    void MakeAction(Action action);
    void NewGenome();
    void SetGenome(Genome g){genome_=g;}
    void SetPhy(Phy p){phy_=p;}
    void SetOrganics (Organics o){state_.organics=o;}

    void InitLife();
    void InitLife(Genome g,Phy p, Organics s);

    void Die();

    Coord GetDropLocation();

    bool CheckForReplication();

    Pop* TryReplication();

    Pop* ReplicateMyself();

    void StepOfLife();
    void EnergyBalance();
    void TemperatureBalance();
    void produceMetabolismHeat();
    void TakeFromField();
    void RunChloroplasts();
    void RunMitochondrions();
    void StepMetabolism();
    void updateTemperature();
    double computeAlpha( double maxLipidsRef, double alphaMin, double alphaMax);
};

#endif //"POP_H_"
