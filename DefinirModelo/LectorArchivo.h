#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Vertice.h"
#include "Cara.h"
#include "Modelo.h"
class LectorArchivo
{
public:
	Modelo lector(string dir) {
        Modelo model;
        ifstream inputFile(dir);

        if (!inputFile.is_open()) {
            cerr << "Error al abrir el archivo." << endl;
            return model;
        }
        else {
            string line;
            stringstream ss(line);
            string word;
            vector<string> words;
            string nom;

            while (getline(inputFile, line)) {
                istringstream iss(line);
                switch (line[0]) {
                case 'o':
                    //Coloca nombre
                    iss >> word;
                    iss >> word;
                    nom = word;
                    model.setNombre(nom);
                    break;
                case 'v':
                    float x, y, z;
                    iss >> word;
                    //X
                    iss >> word;
                    x = stof(word);
                    //Y
                    iss >> word;
                    y = stof(word);
                    //Z
                    iss >> word;
                    z = stof(word);
                    model.AddVertice(x, y, z);
                    /*cout << "( " << (model.vertices.back()).x << " , "
                        << (model.vertices.back()).y << " , "
                        << (model.vertices.back()).z << " )" << endl;*/
                    break;
                case 'f':
                    int c1, c2, c3;
                    iss >> word;
                    //Cara 1
                    iss >> word;
                    c1 = stoi(word)-1;
                    //Cara 2
                    iss >> word;
                    c2 = stoi(word)-1;
                    //Cara 3
                    iss >> word;
                    c3 = stoi(word)-1;
                    model.AddCara(c1, c2, c3);
                    /*cout << "caras: ( " << (model.caras.back()).vertexIndices[0] << " , "
                        << (model.caras.back()).vertexIndices[1] << " , "
                        << (model.caras.back()).vertexIndices[2] << " )" << endl;*/
                    break;
                default:
                    // Acción predeterminada para otras líneas
                    /*cout << "Linea no valida: " << line << endl;*/
                    break;
                }
            }

            inputFile.close();
            return model;
        }
	}
};


