#ifndef COMMON_H_
#define COMMON_H_

#pragma once 
#include <iostream>




//Types


typedef struct
{
    int pops;
    int foods;
    int run;
    int year;
    int generation;
    int size;

}RunTimeStatistics;

typedef struct
{
    int x;
    int y;

}Coord;



//randomic genenration utils
int Random_int(int min, int max);
double  Random_double(double min, double max); 

#endif //"COMMON_H_"
