//
// Created by mauma on 16/04/2026.
//

#ifndef INTENTO1_FUNCIONES_H
#define INTENTO1_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
using namespace std;
void cargarCursos(const char* nombre, char***& cursosDatos, int*& cursosCredito, char****& cursosAlumnos, double**& cursosInformacionEconomica);
char* leerCadena(ifstream& input, int n, char c);
void concaternar(char* arrAlumno, char c);
void leerDatosYCreditos(ifstream& input, char**& arrCursos, char c, int &creditos, int& cantAlumnos, double& ingresosBrutos);
void leerAlumnos(ifstream& input, char**& arrAlumnos, char c, int creditos, int& cantAlumnos, double& ingresosBrutos);
void aumentarMemoria(char****& cursosAlumnos, char***& cursosDatos, int*& cursosCredito, double**& cursosInformacionEconomica);
void asignarDatosYCreditos(char****& cursosAlumnos, char***& cursosDatos, int*& cursosCredito, double**& cursosInformacionEconomica, char** arrCursos, int creditos,int & capacidad);
double calcularPago(char escala, int creditos);
void reporteDeAlumnosPorCurso(const char* nombreArch, char*** cursos_datos, int* cursos_credito,
                              char**** cursos_alumnos, double** cursos_informacion_economica);
#endif //INTENTO1_FUNCIONES_H
