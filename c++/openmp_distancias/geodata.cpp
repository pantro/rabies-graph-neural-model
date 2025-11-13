#include "geodata.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cmath>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

// Função auxiliar para limpeza de espaços
static string trim(const string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

const double R = 6371.0; // radio de la Tierra en km

double haversine(const Point& a, const Point& b) {
    double lat1 = a.lat * M_PI / 180.0;
    double lon1 = a.lon * M_PI / 180.0;
    double lat2 = b.lat * M_PI / 180.0;
    double lon2 = b.lon * M_PI / 180.0;

    double dlat = lat2 - lat1;
    double dlon = lon2 - lon1;
    double h = sin(dlat/2)*sin(dlat/2) +
               cos(lat1)*cos(lat2)*sin(dlon/2)*sin(dlon/2);
    return 2 * R * asin(sqrt(h));
}

// Suporta múltiplos arquivos CSV e reconhece separadores entre polígonos.
vector<vector<Point>> cargarPoligonos(const string& rutaEntrada) {
    vector<vector<Point>> todosLosPoligonos;

    // Se for uma pasta, ele lê todos os arquivos .csv que estão dentro dela.
    vector<string> archivosCSV;
    if (fs::is_directory(rutaEntrada)) {
        for (const auto& entry : fs::directory_iterator(rutaEntrada)) {
            if (entry.path().extension() == ".csv")
                archivosCSV.push_back(entry.path());
        }
    } else {
        archivosCSV.push_back(rutaEntrada);
    }

    for (const auto& csv_file : archivosCSV) {
        ifstream file(csv_file);
        if (!file.is_open()) {
            cerr << "❌ Não foi possível abrir " << csv_file << endl;
            continue;
        }

        cout << "📄 Lendo arquivo: " << csv_file << endl;

        string line;
        vector<Point> poligonoActual;
        string last_id = "";

        while (getline(file, line)) {
            if (line.empty()) continue;
            stringstream ss(line);
            string ident, lat, lon, yproj, xproj, ingreso;
            getline(ss, ident, ';');
            getline(ss, lat, ';');
            getline(ss, lon, ';');
            getline(ss, yproj, ';');
            getline(ss, xproj, ';');
            getline(ss, ingreso, ';');

            lat = trim(lat);
            lon = trim(lon);

            // Línea vacía → fin de polígono
            if (lat.empty() || lon.empty()) {
                if (!poligonoActual.empty()) {
                    todosLosPoligonos.push_back(poligonoActual);
                    poligonoActual.clear();
                }
                continue;
            }

            try {
                double la = stod(lat);
                double lo = stod(lon);
                poligonoActual.push_back({la, lo});
            } catch (...) {
                cerr << "⚠️ Línea con datos inválidos en " << csv_file << ": " << line << endl;
            }
        }

        // Último polígono do arquivo
        if (!poligonoActual.empty())
            todosLosPoligonos.push_back(poligonoActual);

        cout << "✅ Se leyeron " << todosLosPoligonos.size() << " polígonos hasta ahora.\n";
    }

    cout << "📦 Total de polígonos cargados: " << todosLosPoligonos.size() << endl;
    return todosLosPoligonos;
}

// Carregar centros
vector<Point> cargarCentros(const string& kml_file) {
    vector<Point> centros;
    ifstream file(kml_file);
    if (!file.is_open()) {
        cerr << "No se pudo abrir " << kml_file << endl;
        return centros;
    }

    string line;
    while (getline(file, line)) {
        if (line.find("<coordinates>") != string::npos) {
            size_t start = line.find("<coordinates>") + 13;
            size_t end = line.find("</coordinates>");
            string coord_str = line.substr(start, end - start);
            stringstream ss(coord_str);
            double lon, lat;
            char comma;
            ss >> lon >> comma >> lat;
            centros.push_back({lat, lon});
        }
    }

    cout << "🏥 Se carregaron " << centros.size() << " centros de saúde.\n";
    return centros;
}
