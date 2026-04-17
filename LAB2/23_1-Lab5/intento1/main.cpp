#include <iostream>
#include "Bilbiotecas/Funciones.h"

int main() {
    char ***cursos_datos, ****cursos_alumnos;
    int* cursos_credito;
    double** cursos_informacion_economica;

    cargarCursos("ArchivosDeDatos/matricula_ciclo_2023_1.csv", cursos_datos, cursos_credito, cursos_alumnos,
                 cursos_informacion_economica);
    reporteDeAlumnosPorCurso("ArchivosDeReporte/ReporteDeAlumnos.txt", cursos_datos, cursos_credito,cursos_alumnos, cursos_informacion_economica);

    return 0;
}
