//
// Created by mauma on 15/04/2026.
//

#include "Funciones.h"
#define INC 5

char* leerCadena(ifstream& input, int n, char c) {
    char *str, buffer[n];
    input.getline(buffer, n, c);
    str = new char[strlen(buffer) + 1];
    strcpy(str, buffer);
    return str;
}

void aumentarEspacio(char***& cursos, double*& cursosCred, int& numDatos, int &capacidad) {
    char*** aux;
    double* auxDouble;
    capacidad += INC;
    if(numDatos==0) {
        cursos = new char**[capacidad]{};
        cursosCred = new double[capacidad]{};
        numDatos++;
    } else {

        auxDouble = new double[capacidad]{};
        aux = new char**[capacidad]{};
        for(int i = 0; i < numDatos; i++) aux[i] = cursos[i];
        for(int i = 0; i < numDatos; i++) auxDouble[i] = cursosCred[i];
        delete [] cursos;
        delete [] cursosCred;
        cursos = aux;
        cursosCred = auxDouble;
    }
}

void asignarCursosYEscalas(char***& cursos, double*& cursosCred, char** arrCursos, double creditos, int& capacidad) {
    int numDatos = 0;
    if(cursos != nullptr) {
        for(int i = 0; cursos[i] != nullptr; i++) numDatos++;
        numDatos++;
    }

    if(numDatos == capacidad) {
        aumentarEspacio(cursos, cursosCred, numDatos, capacidad);
    }
    cursos[numDatos - 1] = arrCursos;
    cursosCred[numDatos - 1] = creditos;
    cursos[numDatos] = nullptr;
}

void cargarCursosYEscalas(char***& cursos, double*& cursosCred, double* escalas, const char* cursosCsv,
                          const char* escalasCsv) {
    ifstream inputCurso(cursosCsv, ios::in);
    if(!inputCurso) {
        cout << "Error al abrir " << cursosCsv << endl;
        exit(1);
    }
    cursos = nullptr;
    cursosCred = nullptr;
    char c;
    double creditos;
    int capacidad = 0;
    while(true) {
        char **arrCursos = new char*[3];
        if(inputCurso.peek() == EOF) break;
        arrCursos[0] = leerCadena(inputCurso, 10, ',');
        arrCursos[1] = leerCadena(inputCurso, 70, ',');
        inputCurso >> creditos >> c;
        inputCurso.ignore(15, ',');
        arrCursos[2] = leerCadena(inputCurso, 70, '\n');
        asignarCursosYEscalas(cursos, cursosCred, arrCursos, creditos, capacidad);
    }
}

void pruebaDeCargaDeCursos(const char* nombre, char*** cursos, double* cursosCred) {
    ofstream output(nombre, ios::out);
    if (!output) {
        cout << "Error al crear el archivo " << nombre << endl;
        exit(1);
    }

    output << left << setw(10) << "CODIGO"
            << setw(50) << "NOMBRE DEL CURSO"
            << setw(12) << "CREDITOS"
            << "PROFESOR" << endl;

    output << setfill('=') << setw(110) << "=" << setfill(' ') << endl;

    if (cursos != nullptr) {
        for (int i = 0; cursos[i] != nullptr; i++) {
            output << left << setw(10) << cursos[i][0]
                    << setw(50) << cursos[i][1]
                    << right << setw(8) << fixed << setprecision(2) << cursosCred[i] << "    " 
                    << left << cursos[i][2]
                    << endl;
        }
    } else {
        output << "No hay datos cargados en el arreglo." << endl;
    }
}