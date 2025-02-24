#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Per rand()
#include <ctime> 
#include <opencv2/opencv.hpp>
  // Per time()
#include "matrixc.h"
static constexpr int SIZE = 128;  // Dimensione della griglia
static constexpr int CELL_SIZE = 10; // Dimensione delle celle
static constexpr int WIDTH = SIZE * CELL_SIZE;
static constexpr int HEIGHT = SIZE * CELL_SIZE;

cv::Mat img;

// ... fino a exercise30();
void RunSim() {
    std::cout << "\n=======  START =======\n";
    std::vector<int> a;
    for (int i = 1; i <= 30; ++i) {
     

        
    }
   
    std::cout << "Seleziona un'opzione: ";
}
void drawCircle(int x, int y, bool filled) {
    if (filled) {
        std::cout << "CV DRAW\n";
        int centerX = x * CELL_SIZE + CELL_SIZE / 2;
        int centerY = y * CELL_SIZE + CELL_SIZE / 2;
        cv::circle(img, cv::Point(centerX, centerY), CELL_SIZE / 3, cv::Scalar(0, 0, 0), -1); // Nero
    }
}
int main() {
    int choice;
    do {
        drawCircle(3, 3, true); 
        RunSim();
        std::cin >> choice;

        switch (choice) {
        case 1:
            
            break;
        case 2:
 
            break;
        // ... aggiungi i case fino a 30
        case 30:
         
            break;
        case 0:
            std::cout << "Uscita dal programma.\n";
            break;
        default:
            std::cout << "Opzione non valida. Riprova.\n";
        }

    } while (choice != 0);

    return 0;
}
