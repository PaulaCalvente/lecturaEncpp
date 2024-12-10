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
        double aspect_ratio;
        int image_width;
        int samples_per_pixel;
        int max_depth;
        double background1, background2, background3;
        int vfov;
        double lookfrom1, lookfrom2, lookfrom3;
        double lookat1, lookat2, lookat3;
        double vr1, vr2, vr3;
        double defocus_angle, focus_dist;

        // Método para imprimir un registro
        void imprimir() const {
            std::cout << "Aspect Ratio: " << aspect_ratio
                << ", Image Width: " << image_width
                << ", Samples per Pixel: " << samples_per_pixel
                << ", Max Depth: " << max_depth
                << ", Background: (" << background1 << ", " << background2 << ", " << background3 << ")"
                << ", VFOV: " << vfov
                << ", LookFrom: (" << lookfrom1 << ", " << lookfrom2 << ", " << lookfrom3 << ")"
                << ", LookAt: (" << lookat1 << ", " << lookat2 << ", " << lookat3 << ")"
                << ", VR: (" << vr1 << ", " << vr2 << ", " << vr3 << ")"
                << ", Defocus Angle: " << defocus_angle
                << ", Focus Distance: " << focus_dist
                << std::endl;
        }
    };

private:
    std::vector<Registro> registros; // Vector para almacenar los registros
    std::string filePath;            // Ruta del archivo CSV

    // Método auxiliar para procesar una línea del archivo
    Registro procesarLinea(const std::string& line) const {
        Registro registro;
        std::istringstream lineStream(line);
        std::string temp;

        // Leer y parsear cada columna según el nuevo formato
        std::getline(lineStream, temp, ','); registro.aspect_ratio = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.image_width = std::stoi(temp);
        std::getline(lineStream, temp, ','); registro.samples_per_pixel = std::stoi(temp);
        std::getline(lineStream, temp, ','); registro.max_depth = std::stoi(temp);

        std::getline(lineStream, temp, ','); registro.background1 = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.background2 = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.background3 = std::stod(temp);

        std::getline(lineStream, temp, ','); registro.vfov = std::stoi(temp);

        std::getline(lineStream, temp, ','); registro.lookfrom1 = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.lookfrom2 = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.lookfrom3 = std::stod(temp);

        std::getline(lineStream, temp, ','); registro.lookat1 = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.lookat2 = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.lookat3 = std::stod(temp);

        std::getline(lineStream, temp, ','); registro.vr1 = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.vr2 = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.vr3 = std::stod(temp);

        std::getline(lineStream, temp, ','); registro.defocus_angle = std::stod(temp);
        std::getline(lineStream, temp, ','); registro.focus_dist = std::stod(temp);

        registro.imprimir();
        return registro;
    }

public:
    // Constructor
    explicit CSVReader(const std::string& path) : filePath(path) {}

    // Método para leer el archivo CSV
    bool leerCSV() {
        std::ifstream file(filePath);

        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo: " << filePath << std::endl;
            return false;
        }

        std::string line;
        bool firstLine = true;

        while (std::getline(file, line)) {
            if (firstLine) { // Saltar la primera línea
                firstLine = false;
                continue;
            }

            registros.push_back(procesarLinea(line)); // Procesar y almacenar la línea
        }

        file.close();
        return true;
    }

    //// Método para imprimir los registros
    //void imprimirRegistros() const {
    //    for (const auto& registro : registros) {
    //        registro.imprimir();
    //    }
    //}

    // Método para obtener los registros (por si se necesita procesarlos externamente)
    const std::vector<Registro>& obtenerRegistros() const {
        return registros;
    }
};

// Función principal
int main() {
    // Ruta del archivo CSV
    const std::string filePath = "C:/Users/Paula/source/repos/lectorCamara/lectorCamara/camara.csv";

    // Crear un objeto CSVReader
    CSVReader lector(filePath);

    // Leer el archivo CSV
    if (!lector.leerCSV()) {
        return 1; // Terminar si no se puede leer el archivo
    }

    // Imprimir el contenido del archivo
    std::cout << "Contenido del archivo CSV:" << std::endl;
    //lector.imprimirRegistros();

    return 0;
}
