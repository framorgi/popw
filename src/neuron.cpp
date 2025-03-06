#include "neuron.h"

void exportSensorToCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Errore nell'apertura del file.\n";
        return;
    }
    for (Sensor s : magic_enum::enum_values<Sensor>()) {
        file << static_cast<int>(s) << "," << magic_enum::enum_name(s) <<";";
    }
    file.close();
}
void exportOutputToCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Errore nell'apertura del file.\n";
        return;
    }
    for (Action s : magic_enum::enum_values<Action>()) {
        file << static_cast<int>(s) << "," << magic_enum::enum_name(s) <<";";
    }
    file.close();
}
