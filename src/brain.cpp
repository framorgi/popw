#include "brain.h"

Brain::Brain()
{
    sizeS = p.VsizeS;
    sizeN = p.VsizeN; 
    sizeY = p.VsizeY;   
 
    W = Eigen::SparseMatrix<float> (sizeN, sizeS);
    D = Eigen::SparseMatrix<float> (sizeY, sizeS);
    V = Eigen::SparseMatrix<float> (sizeY, sizeN);

    s_ = Eigen::SparseVector<float> (sizeS);
    n_ = Eigen::SparseVector<float> (sizeN);
    y_ = Eigen::SparseVector<float> (sizeY);
    y_t = Eigen::SparseVector<float> (sizeY);
    y_d = Eigen::SparseVector<float> (sizeY);
}

// Funzione per il prodotto matrice sparsa - vettore sparso
Eigen::VectorXf product(const Eigen::SparseMatrix<float>& A, const Eigen::SparseVector<float>& x) {
    if (A.cols() != x.size()) {
        throw std::runtime_error("Errore: Dimensioni incompatibili tra matrice e vettore!");
    }
    return A * x; // Eigen supporta direttamente il prodotto tra sparse matrix e sparse vector
}

float Brain::sigmoid(float x) {
    if (x >= 0) {
        return 1.0f / (1.0f + std::exp(-x));
    } else {
        float expX = std::exp(x);
        return expX / (1.0f + expX);
    }
}

void Brain::ApplyInputFromSensor(std::vector<float> sensorValue)
{
    for (int i=0;i<sizeS;i++)
        insertSValue(i,sensorValue[i]);

}
int Brain::feedForward(std::vector<float> sensorValue)
{

// 0. Inerimento degli input in arrivo dai sensori 
    ApplyInputFromSensor(sensorValue);

// 1. Prodotto matrice dei pesi (W) e vettore di input (s_) per calcolare il layer nascosto (n_):
//    - Formula: n_= σ(W * s_)
        n_=W*s_;
        for (Eigen::SparseVector<float>::InnerIterator it(n_); it; ++it) {
            const_cast<float&>(it.valueRef()) = sigmoid(it.value());
        }

// 2. Prodotto matrice dei pesi (V) e vettore del layer nascosto (n_) per calcolare l'output (y):
//    - Formula: y = V * h
        y_=V*n_;

// 3. Prodotto matrice dei pesi per la connessione diretta (D) e vettore di input (s_) per calcolare un contributo diretto all'output:
//    - Formula: y_d = D * s_
        y_d = D * s_;

// 4. Somma dei contributi ottenuti dal layer nascosto e dalla connessione diretta per ottenere il risultato finale dell'output:
//    - Formula: y_t = σ(y + y_d)
        y_t=y_+ y_d;
        for (Eigen::SparseVector<float>::InnerIterator it(y_t); it; ++it) {
            const_cast<float&>(it.valueRef()) = sigmoid(it.value());
        }
        //printRow();
// 5. Valutazione del neurone con segnale piùù forte:
//    - Formula: max(y_t)
        int maxIndex = -1;
        float maxValue = 0;

        for (Eigen::SparseVector<float>::InnerIterator it(y_t); it; ++it) {
            if (it.value() > maxValue)
            {
                maxValue = it.value();
                maxIndex = it.index();
            }
        }
        return maxIndex;
}


void Brain::WireBrain(Genome gen)
{ 
    
    for (Gene g : gen)
    { 
        //std::cout <<"--------------------------------------------------------------------------------------------------------------------------"<<std::endl;
        //std::cout <<"WIRING GENE sourceType["<<g.sourceType<<"]  sourceNum["<<g.sourceNum<<"]  sinkType["<<g.sinkType<<"] sinkNum["<<g.sinkNum<<"] Weight ["<<g.weight<<"] "<<std::endl;

        if (g.sourceType==0 && g.sourceNum< sizeS) // SOURCE SENSOR
        {
            if (g.sinkType==0 && g.sinkNum< sizeN )   // SINK NEURON
                {
                    insertWValue(g.sinkNum,g.sourceNum,g.weightAsFloat());  // create a connection in matrix W
                }
            if (g.sinkType==1 && g.sinkNum< sizeY )   // SINK ACTION
                {
                    insertDValue(g.sinkNum,g.sourceNum,g.weightAsFloat()); // create a connection in matrix D
                }
        }

        if (g.sourceType==1 && g.sourceNum< sizeN) // SOURCE NEURON
        {
            if (g.sinkType==1 && g.sinkNum< sizeY )  // SINK ACTION
                {
                    insertVValue(g.sinkNum,g.sourceNum,g.weightAsFloat()); // create a connection in matrix V
                }

        }




    }

    /*printSparseMatrix(W,"Weight W Matrix");
        
    printSparseMatrix(V,"Weight V Matrix");

    printSparseMatrix(D,"Weight D Matrix");
*/

}

// Funzione per stampare una matrice sparsa
void Brain::printSparseMatrix(const Eigen::SparseMatrix<float>& sparseMatrix, const std::string& name = "Matrice Sparsa") {
    std::cout << name << " (" << sparseMatrix.rows() << "x" << sparseMatrix.cols() << "):\n";
    for (int k = 0; k < sparseMatrix.outerSize(); ++k) {
        for (Eigen::SparseMatrix<float>::InnerIterator it(sparseMatrix, k); it; ++it) {
            std::cout << "(" << it.row() << ", " << it.col() << ") = " << it.value() << "\n";
        }
    }
    std::cout << "\n";
}
void Brain::insertWValue(int row, int col, float value) {
    if (row < sizeN && col < sizeS) {
        W.coeffRef(row, col) = value;
    //std::cout <<"Positioning weight ["<<value<<"] at ["<<row<<"x"<< col<<"] in Matrix W ["<<sizeN<<"x"<< sizeS<<"]"<<std::endl;
    }
    else
    {
        std::cout <<"Wrong positioning ["<<row<<"x"<< col<<"]. Matrix W is ["<<sizeN<<"x"<< sizeS<<"]"<<std::endl;
    }
}
void Brain::insertVValue(int row, int col, float value) {
    if (row < sizeY && col < sizeN) {
        V.coeffRef(row, col) = value;
       // std::cout <<"Positioning weight ["<<value<<"] at ["<<row<<"x"<< col<<"] in Matrix V ["<<sizeY<<"x"<< sizeN<<"]"<<std::endl;

    }
    else
    {
        std::cout <<"Wrong positioning ["<<row<<"x"<< col<<"]. Matrix V is ["<<sizeY<<"x"<< sizeN<<"]"<<std::endl;
    }
}
void Brain::insertDValue(int row, int col, float value) {
    if (row < sizeY && col < sizeS) {
        D.coeffRef(row, col) = value;
       // std::cout <<"Positioning weight ["<<value<<"] at ["<<row<<"x"<< col<<"] in Matrix D ["<<sizeY<<"x"<< sizeS<<"]"<<std::endl;
    }
    else
    {
        std::cout <<"Wrong positioning ["<<row<<"x"<< col<<"]. Matrix D is ["<<sizeY<<"x"<< sizeS<<"]"<<std::endl;
    }
}

void Brain::insertSValue(int index, float value) {
    if (index < sizeS) {
        s_.coeffRef(index) = value;
    }
}
void Brain::insertNValue(int index, float value) {
    if (index < sizeN) {
        n_.coeffRef(index) = value;
    }
}
void Brain::insertYValue(int index, float value) {
    if (index < sizeY) {
        y_.coeffRef(index) = value;
    }
}
void Brain::insertY_dValue(int index, float value) {
    if (index < sizeY) {
        y_d.coeffRef(index) = value;
    }
}
void Brain::insertY_tValue(int index, float value) {
    if (index < sizeY) {
        y_t.coeffRef(index) = value;
    }
}

void Brain::printRow() {
    std::cout <<"FeedForward Result  : "<<std::endl;
    std::cout <<"S_ Vector : "<<s_<<std::endl;
    std::cout <<"N_ Vector : "<<n_<<std::endl;
 
    std::cout <<"Y_ Vector : "<<y_<<std::endl;
    std::cout <<"Y_d Vector : "<<y_d<<std::endl;
    std::cout <<"Y_t Vector : "<<y_t<<std::endl;
}

// Funzione per scrivere un vettore nel formato CSV
void Brain::writeVectorToCSV(std::ofstream& file, const std::vector<float>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        file << vec[i];
        if (i < vec.size() - 1) {
            file << ","; // Separatore tra i valori
        }
    }
    file << "\n"; // Nuova riga dopo il vettore
}

// Funzione per scrivere una matrice nel formato CSV
void Brain::writeMatrixToCSV(std::ofstream& file, Eigen::SparseMatrix<float> &sparseMatrix, string name) {

    file <<  "@"+name;
    file <<"\n";
    for (int k = 0; k < sparseMatrix.outerSize(); ++k) {
        for (Eigen::SparseMatrix<float>::InnerIterator it(sparseMatrix, k); it; ++it) {
           
            file <<   std::to_string(it.row()) << "," << std::to_string(it.col()) << "," <<std::to_string( it.value()) << ";";
        }

    }
    file <<"\n";
}


void Brain::ToCsV(string pop_id)
{
     // Creazione del file CSV
    string filename = pop_id+"_nn.csv";
    std::ofstream file(filename);
 
    std::cout<<"Open file "<<filename;  
    writeMatrixToCSV(file,W,"W matrix");
    writeMatrixToCSV(file,V,"V matrix");
    writeMatrixToCSV(file,D,"D matrix");
    file.close();
    
    
}
