//
// Created by mauma on 15/04/2026.
//

#ifndef INC_23_1_PARCIAL_FUNCIONES_H
#define INC_23_1_PARCIAL_FUNCIONES_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
using namespace std;

void cargarCursosYEscalas(char***& cursos, double*& cursosCred, double* escalas, const char* cursosCsv,
                          const char* escalasCsv);
char* leerCadena(ifstream& input, int i, char c);
void aumentarEspacio(char***& cursos, double*& cursosCred, int& numDatos, int& capacidad);
void asignarCursosYEscalas(char***& cursos, double*& cursosCred, char** arrCursos, double creditos, int& capacidad);
void pruebaDeCargaDeCursos(const char* nombre, char*** cursos, double* cursosCred);


#endif //INC_23_1_PARCIAL_FUNCIONES_H
