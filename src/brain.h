#ifndef BRAIN_H_
#define BRAIN_H_

#pragma once 
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "params.h"
#include "genome.h"
#include <cmath>
#include "neuron.h"
#include "Eigen/Dense"
#include <Eigen/Sparse>

extern const Params &p; 

// 1. Prodotto matrice dei pesi (W) e vettore di input (s_) per calcolare il layer nascosto (n_):
//    - Formula: n_= σ(W * s_)

// 2. Prodotto matrice dei pesi (V) e vettore del layer nascosto (n_) per calcolare l'output (y):
//    - Formula: y = V * h

// 3. Prodotto matrice dei pesi per la connessione diretta (D) e vettore di input (s_) per calcolare un contributo diretto all'output:
//    - Formula: y_d = D * s_

// 4. Somma dei contributi ottenuti dal layer nascosto e dalla connessione diretta per ottenere il risultato finale dell'output:
//    - Formula: y_t = σ(y + y_d)

class Brain
{
    public:
    Brain();
   
    private:
       
    // Vettore S: rappresenta il vettore dei valori dei sensori (dimensione: vectorSize) [sizeS]
    Eigen::SparseVector<float> s_; 
    // Matrice W: rappresenta i pesi delle connessioni tra il vettore dei sensori S e il layer interno N [sizeN x sizeS]
    Eigen::SparseMatrix<float> W; 



    // Vettore n_: rappresenta il layer interno, ottenuto come prodotto n_= σ(W*S) il vettore s_ e la matrice W [sizeN]
    Eigen::SparseVector<float> n_;      
    // Matrice V: rappresenta i pesi delle connessioni tra il layer N e il vettore delle uscite Y [sizeY x sizeN]
    Eigen::SparseMatrix<float> V;  

    // Matrice D: rappresenta i pesi delle connessioni dirette (residual conncections) tra il layer s_ e il vettore delle uscite Y [sizeY x sizeS]
    Eigen::SparseMatrix<float> D; 
    
    // Vettore y_: rappresenta le uscite del modello, ottenute dalla moltiplicazione tra il layer n_ e la matrice V [sizeY]
    Eigen::SparseVector<float> y_;  

    // Vettore y_d: rappresenta le uscite del modello, ottenute dalla moltiplicazione tra il layer s_ e la matrice D [sizeY]
    Eigen::SparseVector<float> y_d;  

    // Vettore y_t: rappresenta la somma dei contributi ottenuti dal layer  n_ e dalla connessione diretta con il layer s_  [sizeY]
    Eigen::SparseVector<float> y_t;  

    int sizeS, sizeN, sizeY;            // Dimensioni

    


    void printSparseMatrix(const Eigen::SparseMatrix<float> &sparseMatrix, const std::string &name);

    void insertWValue(int row, int col, float value);

    void insertVValue(int row, int col, float value);

    void insertDValue(int row, int col, float value);

    void insertSValue(int index, float value);

    void insertNValue(int index, float value);

    void insertYValue(int index, float value);

    void insertY_dValue(int index, float value);

    void insertY_tValue(int index, float value);

    void printRow();

    void writeVectorToCSV(std::ofstream &file, const std::vector<float> &vec);

    void writeMatrixToCSV(std::ofstream &file, Eigen::SparseMatrix<float> &sparseMatrix, string name);

    

    float sigmoid(float x);

    void ApplyInputFromSensor(std::vector<float> sensorValue);

    public:
    
    void ToCsV(string pop_id);

    int feedForward(std::vector<float> sensorValue);

    void WireBrain(Genome gen);
};




#endif //"BRAIN_H_"
