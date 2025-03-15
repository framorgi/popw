#ifndef COMMON_H_
#define COMMON_H_

#pragma once 
#include <iostream>
#include <chrono>

//Types


typedef struct
{
    int pops;
    int foods;
    int run;
    int year;
    int generation;
    int size;
    int avgTimeFF;
    int avgTimeWxS;
    int avgTimeVxN;
    int avgTimeDxS;
    int avgTimeSensing;
    int avgTimeSnap;
    int avgTimeRun;

}RunTimeStatistics;

typedef struct
{
    int x;
    int y;

}Coord;



//randomic genenration utils
int Random_int(int min, int max);
double  Random_double(double min, double max); 

class Timer{

private:
    std::chrono::high_resolution_clock::time_point start_;
    int count=0;
    //std::map<std::string, std::chrono::high_resolution_clock::time_point> startTimes_;

public:
    Timer(){};
    void start() 
    {
        start_ = std::chrono::high_resolution_clock::now();
       
    }
    void stop() 
    {
        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double, std::milli>(end - start_).count();
        std::cout<<"Elapsed ["<<duration <<"]"<<std::endl;
    }
};

#endif //"COMMON_H_"
