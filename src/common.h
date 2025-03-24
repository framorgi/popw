#ifndef COMMON_H_
#define COMMON_H_

#pragma once 
#include <iostream>
#include <chrono>
#include <thread>
#include <atomic>
#include <cstdint>
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

float Normalize_float(float x, float min, float max, float minOut, float maxOut);

class Timer{

private:
    std::chrono::high_resolution_clock::time_point start_;
    int count=0;
    std::string t_name="t_name";
    //std::map<std::string, std::chrono::high_resolution_clock::time_point> startTimes_;

public:
    Timer(){};
    Timer(std::string s):t_name(s)
    {

    };
    void start() 
    {
        start_ = std::chrono::high_resolution_clock::now();
       
    }
    void stop() 
    {
        auto end = std::chrono::high_resolution_clock::now();
        double duration = std::chrono::duration<double, std::milli>(end - start_).count();
        std::cout<<"["<< t_name<<"] -- time elapsed ["<<duration <<"]"<<std::endl;
    }
};


class UniqueID {
public:
        static uint64_t generateID() {
        static std::atomic<uint64_t> counter{0};
        uint64_t timestamp = static_cast<uint64_t>(
            std::chrono::steady_clock::now().time_since_epoch().count()
        );

        return (timestamp << 16) | (counter.fetch_add(1) & 0xFFFF);
    }
    static std::string generateStringID() {
        static int counter = 0; // Contatore statico
        auto now = std::chrono::system_clock::now();
        auto timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(
                             now.time_since_epoch())
                             .count();
        return std::to_string(timestamp) + "_" + std::to_string(counter++);
    }
};
#endif //"COMMON_H_"
