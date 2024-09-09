#pragma once
#include <iostream>
#include <vector>
#include "Vertice.h"
#include "Cara.h"
using namespace std;

class Modelo {
public:
    vector<Vertice> vertices;
    vector<Cara> caras;
    string nombre;
public:
    void AddVertice(float x, float y, float z) {
        vertices.push_back(Vertice(x, y, z));
    }

    void AddCara(int v1, int v2, int v3) {
        caras.push_back(Cara(v1, v2, v3));
    }

    Vertice getVertice() {
        return vertices.back();
    }

    Cara getCara() {
        return caras.back();
    }

    void setNombre(string n) {
        nombre = n;
    }
};

