#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Per rand()
#include <ctime>   // Per time()
#include "matrixC.h"


// ... fino a exercise30();
void RunSim() {
    std::cout << "\n=======  START =======\n";
    for (int i = 1; i <= 30; ++i) {
     

        
    }
    std::cout << "0. Esci\n";
    std::cout << "Seleziona un'opzione: ";
}

int main() {
    int choice;
    do {
        displayMenu();
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
