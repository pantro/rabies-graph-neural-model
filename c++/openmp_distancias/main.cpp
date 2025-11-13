#include <iostream>
#include <vector>
#include <omp.h>
#include "geodata.h"

using namespace std;

// Calcule a distância mínima entre os vértices do polígono e todos os centros.
double distancia_minima(const vector<Point>& poligono, const vector<Point>& centros) {
    double min_d = 1e9;
    for (const auto& v : poligono) {
        for (const auto& c : centros) {
            double d = haversine(v, c);
            if (d < min_d)
                min_d = d;
        }
    }
    return min_d;
}

int main() {
    string csv_file = "./dataset/Economic_income_cluster-selected/";
    string kml_file = "./dataset/Puestos_de_salud_AQP_12ene2024.kml";

    cout << "Carregando dados..." << endl;
    auto cuadras = cargarPoligonos(csv_file);
    auto centros = cargarCentros(kml_file);

    cout << "Carregados " << cuadras.size() << " quarteroes de casas e "
         << centros.size() << " postos de saúde.\n";

    
    vector<double> dist_min(cuadras.size());

    // Versión paralela con OpenMP
    double start = omp_get_wtime();

    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < (int)cuadras.size(); ++i) {
        dist_min[i] = distancia_minima(cuadras[i], centros);
    }

    double end = omp_get_wtime();
    cout << "Tempo total: " << (end - start) << " segundos\n";

    // Mostrar algunos resultados
    for (int i = 0; i < 5 && i < (int)dist_min.size(); ++i)
        cout << "Quarteroes " << i + 1 << " -> Distância mínima: " << dist_min[i] << " km\n";

    return 0;
}
