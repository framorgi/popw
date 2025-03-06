#ifndef GENOME_H_
#define GENOME_H_
#pragma once
#include "common.h"
#include "params.h"
#include <cmath>
#include <cstdlib>
#include <vector>
#include <ctime>
extern const Params &p; 
typedef struct  { 
    uint16_t sourceType:1; // SENSOR or NEURON
    uint16_t sourceNum:7;
    uint16_t sinkType:1;   // NEURON or ACTION
    uint16_t sinkNum:7;
    int16_t weight;

    //static constexpr float f1 = 8.0;
    //static constexpr float f2 = 64.0;
    //float weightAsFloat() { return std::pow(weight / f1, 3.0) / f2; }
    float weightAsFloat() const { return weight / 8192.0; }
    static int16_t makeRandomWeight() { return Random_int(0, 0xffff) - 0x8000; }
}Gene ;

typedef std::vector<Gene> Genome;

 // Returns by value a single gene with random members.
// See genome.h for the width of the members.
// ToDo: don't assume the width of the members in gene.
Gene makeRandomGene();


// Returns by value a single genome with random genes.
Genome makeRandomGenome();
uint8_t makeGeneticColor(const Genome &genome);
#endif //"GENOME_H_"
