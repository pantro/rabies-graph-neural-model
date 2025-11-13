#ifndef GEODATA_H
#define GEODATA_H

#include <vector>
#include <string>

// Estrutura simples para armazenar coordenadas
struct Point {
    double lat;
    double lon;
};

// Funções para carregar dados
std::vector<std::vector<Point>> cargarPoligonos(const std::string& csv_file);
std::vector<Point> cargarCentros(const std::string& kml_file);

// Função auxiliar para calcular a distância de Haversine
double haversine(const Point& a, const Point& b);

#endif
