//
// Created by mauma on 16/04/2026.
//

#include "Funciones.h"

#define E1 282.3
#define E2 362
#define E3 454.2
#define E4 556.7
#define E5 666.9
#define INC 5

char* leerCadena(ifstream& input, int n, char c) {
    char *str, buffer[n];
    input.getline(buffer, n, c);
    str = new char[strlen(buffer) + 1];
    strcpy(str, buffer);
    return str;
}

void concaternar(char* arrAlumno, char c) {
    arrAlumno[8] = '.';
    arrAlumno[9] = c;
    arrAlumno[10] = '\0';
}

void leerDatosYCreditos(ifstream& input, char**& arrCursos, char c, int& creditos, int& cantAlumnos,
                        double& ingresosBrutos) {
    cantAlumnos = 0;
    ingresosBrutos = 0;
    arrCursos = new char*[2];
    arrCursos[0] = leerCadena(input, 10, ',');
    arrCursos[1] = leerCadena(input, 50, ',');
    input >> creditos >> c;
}

void leerAlumnos(ifstream& input, char**& arrAlumnos, char c, int creditos, int& cantAlumnos, double& ingresosBrutos) {
    arrAlumnos = new char*[2];
    arrAlumnos[0] = leerCadena(input, 100, ',');
    arrAlumnos[1] = new char[11];
    input.getline(arrAlumnos[1], 50, '.');
    input.get(c);
    concaternar(arrAlumnos[1], c);
    cantAlumnos++;
    if(c == '1') ingresosBrutos += creditos * E1;
    if(c == '2') ingresosBrutos += creditos * E2;
    if(c == '3') ingresosBrutos += creditos * E3;
    if(c == '4') ingresosBrutos += creditos * E4;
    if(c == '5') ingresosBrutos += creditos * E5;
}

void aumentarMemoria(char****& cursosAlumnos, char***& cursosDatos, int*& cursosCredito,
                     double**& cursosInformacionEconomica, int& numDatos, int& capacidad) {
    char ****auxAlumnos, ***auxDatos;
    int* auxCreditos;
    double** auxInformacionEconomica;
    capacidad += INC;
    if(numDatos == 0) {
        cursosAlumnos = new char***[capacidad]{};
        cursosDatos = new char**[capacidad]{};
        cursosCredito = new int[capacidad]{};
        cursosInformacionEconomica = new double*[capacidad]{};
        numDatos++;
    } else {
        auxAlumnos = new char***[capacidad]{};
        auxDatos = new char**[capacidad]{};
        auxCreditos = new int[capacidad]{};
        auxInformacionEconomica = new double*[capacidad]{};

        for(int i = 0; i < numDatos; i++) {
            auxAlumnos[i] = cursosAlumnos[i];
            auxDatos[i] = cursosDatos[i];
            auxCreditos[i] = cursosCredito[i];
            auxInformacionEconomica[i] = cursosInformacionEconomica[i];
        }
        delete[] cursosAlumnos;
        delete[] cursosDatos;
        delete[] cursosCredito;
        delete[] cursosInformacionEconomica;
        cursosAlumnos = auxAlumnos;
        cursosDatos = auxDatos;
        cursosCredito = auxCreditos;
        cursosInformacionEconomica = auxInformacionEconomica;
    }
}

void asignarDatosYCreditos(char****& cursosAlumnos, char***& cursosDatos, int*& cursosCredito,
                           double**& cursosInformacionEconomica, char** arrCursos, int creditos, int& capacidad) {
    int numDatos = 0; // puedo tenerlo q vaya sumando desde la funcion anterior?
    if(cursosDatos != nullptr) {
        for(int i = 0; cursosAlumnos[i] != nullptr; i++) numDatos++;
        numDatos++;
    }

    if(numDatos == capacidad) {
        aumentarMemoria(cursosAlumnos, cursosDatos, cursosCredito, cursosInformacionEconomica, numDatos, capacidad);
        //una vez le aumento a uno le puedo aumentar a otro
    }
    cursosCredito[numDatos - 1] = creditos;
    cursosDatos[numDatos - 1] = arrCursos;
    cursosDatos[numDatos] = nullptr;
}

void aumentarMemoriaAlumnos(char***& cursosAlumno, int& numDatos, int& capacidad) {
    char ***aux;
    capacidad += INC;
    if(numDatos == 0) {
        cursosAlumno = new char**[capacidad]{};
        numDatos++;
    }
    else {
        aux = new char**[capacidad]{};
        for(int i = 0; i < numDatos; i++)
            aux[i] = cursosAlumno[i];
        delete [] cursosAlumno;
        cursosAlumno = aux;
    }
}

void asignarAlumnos(char***& cursosAlumno, char** arrAlumnos, int& capacidad) {
    int numDatos = 0;
    if(cursosAlumno != nullptr) {
        for(int i = 0; cursosAlumno[i] != nullptr; i++) numDatos++;
        numDatos++;
    }

    if(capacidad == numDatos) {
        aumentarMemoriaAlumnos(cursosAlumno, numDatos, capacidad);
    }
    cursosAlumno[numDatos - 1] = arrAlumnos;
    cursosAlumno[numDatos] = nullptr;

}

void asignarInfo(double*& cursosInformacionEconomica, int cantAlumnos, double ingresosBrutos) {
    cursosInformacionEconomica = new double[2];
    cursosInformacionEconomica[0] = cantAlumnos;
    cursosInformacionEconomica[1] = ingresosBrutos;
}

void cargarCursos(const char* nombre, char***& cursosDatos, int*& cursosCredito, char****& cursosAlumnos, double**&
                  cursosInformacionEconomica) {
    ifstream input(nombre, ios::in);
    if(!input) {
        cout << "Error al abrir " << nombre << endl;
        exit(1);
    }
    char **arrCursos, **arrAlumnos, c;
    int creditos, cantAlumnos, capacidad1 = 0, capacidad2 = 0,  j=0;
    double ingresosBrutos;
    cursosDatos = nullptr;
    while(true) {
        if(input.peek() == EOF) break;
        capacidad2 = 0;

        leerDatosYCreditos(input, arrCursos, c, creditos, cantAlumnos, ingresosBrutos);
        asignarDatosYCreditos(cursosAlumnos, cursosDatos, cursosCredito, cursosInformacionEconomica, arrCursos,
                              creditos, capacidad1);
        while(true) {
            if(input.get() == '\n') break;
            leerAlumnos(input, arrAlumnos, c, creditos, cantAlumnos, ingresosBrutos);
            asignarAlumnos(cursosAlumnos[j], arrAlumnos, capacidad2);
        }
        asignarInfo(cursosInformacionEconomica[j], cantAlumnos, ingresosBrutos);
        j++;
    }
}

void imprimirLinea(ofstream &arch, char c) {
    for(int i = 0; i < 90; i++) arch << c;
    arch << endl;
}

void reporteDeAlumnosPorCurso(const char* nombreArch, char*** cursos_datos, int* cursos_credito,
                              char**** cursos_alumnos, double** cursos_informacion_economica) {

    ofstream arch(nombreArch, ios::out);
    if(!arch) {
        cout << "Error al crear el archivo de reporte." << endl;
        return;
    }

    arch << fixed << setprecision(2);
    arch << setw(55) << "CURSOS EN EL CICLO 2023-1\n";
    imprimirLinea(arch, '=');
    arch << "RELACION DE ALUMNOS POR CURSO\n";
    imprimirLinea(arch, '=');

    double granTotalRecaudado = 0;

    for(int i = 0; cursos_datos[i] != nullptr; i++) {
        // Punteros auxiliares para evitar usar más de un índice a la vez
        char** cursoActual = cursos_datos[i];
        int creditosActual = cursos_credito[i];
        double* infoEconomicaActual = cursos_informacion_economica[i];

        arch << left << setw(15) << "CODIGO" << setw(45) << "Nombre"
             << right << setw(15) << "Créditos:" << setw(5) << creditosActual << "\n";

        arch << left << setw(15) << cursoActual[0] << setw(45) << cursoActual[1] << "\n";
        imprimirLinea(arch, '-');

        arch << "RELACION DE ALUMNOS MATRICULADOS:\n";
        imprimirLinea(arch, '-');

        arch << right << setw(4) << " " << left << setw(15) << "CODIGO" << setw(45) << "Nombre"
             << right << setw(15) << "Pago total\n";
        imprimirLinea(arch, '-');

        char*** alumnosDelCurso = cursos_alumnos[i];

        if (alumnosDelCurso != nullptr) {
            for (int j = 0; alumnosDelCurso[j] != nullptr; j++) {
                char** alumnoActual = alumnosDelCurso[j];
                char* nombreAlumno = alumnoActual[0];
                char* codigoYEscala = alumnoActual[1];

                // Extraer la escala del final de la cadena del código (ej: 20082060.5 -> '5')
                int len = 0;
                while(codigoYEscala[len] != '\0') len++;
                char escala = codigoYEscala[len - 1];

                double pagoAlumno = calcularPago(escala, creditosActual);

                // Imprimimos con el número de lista (j+1)
                arch << right << setw(2) << (j + 1) << "  "
                     << left << setw(15) << codigoYEscala
                     << setw(45) << nombreAlumno
                     << right << setw(15) << pagoAlumno << "\n";
            }
        }

        imprimirLinea(arch, '-');

        // AQUÍ usamos el arreglo cursos_informacion_economica en lugar de sumar a mano
        double totalDelCurso = infoEconomicaActual[1];
        arch << right << setw(62) << "TOTAL:" << setw(15) << totalDelCurso << "\n";
        imprimirLinea(arch, '=');

        granTotalRecaudado += totalDelCurso;
    }

    arch << right << setw(62) << "TOTAL RECAUDADO 2023-1:" << setw(15) << granTotalRecaudado << "\n";
}

double calcularPago(char escala, int creditos) {
    if(escala == '1') return creditos * E1;
    if(escala == '2') return creditos * E2;
    if(escala == '3') return creditos * E3;
    if(escala == '4') return creditos * E4;
    if(escala == '5') return creditos * E5;
    return 0.0;
}