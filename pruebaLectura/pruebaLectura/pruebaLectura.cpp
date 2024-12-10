#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>

class CSVReader {
public:
    // Estructura para representar un registro del CSV
    struct Registro {
        std::string figura;
        std::string material;
        double r, g, b;
        double d, v1x, v1y, v1z;
        double v2x, v2y, v2z;
        double v3x, v3y, v3z;

        // M�todo para imprimir un registro
        void imprimir() const {
            std::cout << "Figura: " << figura << ", Material: " << material
                << ", RGB: (" << r << ", " << g << ", " << b << ")"
                << ", D: " << d
                << ", V1: (" << v1x << ", " << v1y << ", " << v1z << ")"
                << ", V2: (" << v2x << ", " << v2y << ", " << v2z << ")"
                << ", V3: (" << v3x << ", " << v3y << ", " << v3z << ")"
                << std::endl;
        }
    };

private:
    std::vector<Registro> registros; // Vector para almacenar los registros
    std::string filePath;            // Ruta del archivo CSV

    // M�todo auxiliar para procesar una l�nea del archivo
    Registro procesarLinea(const std::string& line) const {
        Registro registro;
        std::istringstream lineStream(line);
        std::string temp;

        // Leer y parsear cada columna
        std::getline(lineStream, registro.figura, ',');
        std::getline(lineStream, registro.material, ',');

        std::getline(lineStream, temp, ','); registro.r = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.g = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.b = std::stod(temp);

        std::getline(lineStream, temp, ','); registro.d = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.v1x = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.v1y = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.v1z = std::stod(temp);

        std::getline(lineStream, temp, ','); registro.v2x = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.v2y = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.v2z = std::stod(temp);

        std::getline(lineStream, temp, ','); registro.v3x = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.v3y = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.v3z = std::stod(temp);

        return registro;
    }

public:
    // Constructor
    explicit CSVReader(const std::string& path) : filePath(path) {}

    // M�todo para leer el archivo CSV
    bool leerCSV() {
        std::ifstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo: " << filePath << std::endl;
            return false;
        }

        std::string line;
        bool firstLine = true;

        while (std::getline(file, line)) {
            if (firstLine) { // Saltar la primera l�nea
                firstLine = false;
                continue;
            }

            registros.push_back(procesarLinea(line)); // Procesar y almacenar la l�nea
        }

        file.close();
        return true;
    }

    // M�todo para imprimir los registros
    void imprimirRegistros() const {
        for (const auto& registro : registros) {
            registro.imprimir();
        }
    }

    // M�todo para obtener los registros (por si se necesita procesarlos externamente)
    const std::vector<Registro>& obtenerRegistros() const {
        return registros;
    }
};

// Funci�n principal
int main() {
    // Ruta del archivo CSV
    const std::string filePath = "C:/Users/Paula/source/repos/pruebaLectura/pruebaLectura/prueba.csv";

    // Crear un objeto CSVReader
    CSVReader lector(filePath);

    // Leer el archivo CSV
    if (!lector.leerCSV()) {
        return 1; // Terminar si no se puede leer el archivo
    }

    // Imprimir el contenido del archivo
    std::cout << "Contenido del archivo CSV:" << std::endl;
    lector.imprimirRegistros();

    return 0;
}
