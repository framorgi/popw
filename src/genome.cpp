
#include "genome.h"



 // Returns by value a single gene with random members.
// See genome.h for the width of the members.
// ToDo: don't assume the width of the members in gene.
Gene makeRandomGene()
{
    Gene gene;

    gene.sourceType = Random_int(0, 0xffff) & 1;
    gene.sourceNum = (uint16_t)Random_int(0, 0x7fff);
    gene.sinkType = Random_int(0, 0xffff) & 1;
    gene.sinkNum = (uint16_t)Random_int(0, 0x7fff);
    gene.weight = Gene::makeRandomWeight();

    return gene;
}


// Returns by value a single genome with random genes.
Genome makeRandomGenome()
{
    Genome genome;

    unsigned length = Random_int(p.genomeMinLength, p.genomeMaxLength);
    //std::cout <<"Creating Randon Genome madeof ["<<length<<"]  genes"<<std::endl;

    for (unsigned n = 0; n < length; ++n) {
        genome.push_back(makeRandomGene());
    }

    return genome;
}

uint8_t makeGeneticColor(const Genome &genome)
{
    return ((genome.size() & 1)
         | ((genome.front().sourceType)    << 1)
         | ((genome.back().sourceType)     << 2)
         | ((genome.front().sinkType)      << 3)
         | ((genome.back().sinkType)       << 4)
         | ((genome.front().sourceNum & 1) << 5)
         | ((genome.front().sinkNum & 1)   << 6)
         | ((genome.back().sourceNum & 1)  << 7));
}

