#include <H5Cpp.h>
#include <vector>
#include "popworld.h"
#include <iostream>
extern Field field;
extern PopsSpv spv_;
extern const Params &p;

const std::string FILE_NAME = "simulation.h5";
const int NUM_FLOATS = 20;
class bigMemory
{
private:

    H5::H5File bigFile;
public:

    bigMemory(/* args */);
    ~bigMemory()
    {
    
    }
    


/**
 * @brief Destroy the big Memory::big Memory object
 * 
 */



// Funzione per salvare un vettore di Pop in un file HDF5
void savePopListHDF5(const std::string &filename, const Pop  &pop) {
    H5::H5File file(filename, H5F_ACC_TRUNC);

    // Creiamo un tipo di dato HDF5 che corrisponde alla classe Pop
    H5::CompType popType(sizeof(Pop));
    popType.insertMember("ID", HOFFSET( Pop,ID() ), H5::PredType::NATIVE_INT);
    popType.insertMember("EnergyCost", HOFFSET(Pop, energyCost_), H5::PredType::NATIVE_INT);
    popType.insertMember("ProducedHeat", HOFFSET(Pop, producedMetabolismHeat_), H5::PredType::NATIVE_INT);
    popType.insertMember("GeneticColor", HOFFSET(Pop, geneticColor_), H5::PredType::NATIVE_INT);

    // Definiamo lo spazio dati basato sulla dimensione del vettore
    hsize_t dim[1] = {popList.size()};
    H5::DataSpace dataspace(1, dim);

    // Creiamo il dataset
    H5::DataSet dataset = file.createDataSet("Population", popType, dataspace);

    // Scriviamo i dati nel file
    dataset.write(popList.data(), popType);
}


void initPopDatasetHDF5() {
    H5::H5File file(filename, H5F_ACC_TRUNC);

    // Definiamo un dataset estendibile
    hsize_t initialSize = 0; // Inizialmente vuoto
    hsize_t maxSize = H5S_UNLIMITED;
    H5::DSetCreatPropList prop;
    hsize_t chunkSize = 10;
    prop.setChunk(1, &chunkSize);

    // Definiamo il tipo HDF5 per Pop
    H5::CompType popType(sizeof(Pop));
    
    popType.insertMember("ID", HOFFSET(Pop, id_), H5::PredType::NATIVE_INT);

    // Creiamo il dataset principale con dimensione 0 (sarà esteso dopo)
    H5::DataSpace dataspace(1, &initialSize, &maxSize);
    file.createDataSet("SnapshotPopulation", popType, dataspace, prop);
}

void appendPopToHDF5(const Pop &pop) {
    H5::H5File file(bigFile, H5F_ACC_RDWR);
    H5::DataSet dataset = file.openDataSet("SnapshotPopulation");

    // Recuperiamo la dimensione attuale del dataset
    H5::DataSpace dataspace = dataset.getSpace();
    hsize_t currentSize;
    dataspace.getSimpleExtentDims(&currentSize);

    // Nuova dimensione del dataset (aggiungiamo 1 elemento)
    hsize_t newSize = currentSize + 1;
    dataset.extend(&newSize);

    // Scriviamo il nuovo Pop nell'ultima posizione
    H5::DataSpace memSpace(1, &newSize);
    H5::DataSpace fileSpace = dataset.getSpace();
    fileSpace.selectHyperslab(H5S_SELECT_SET, &newSize, &currentSize);

    dataset.write(&pop, dataset.getDataType(), memSpace, fileSpace);
}

};
