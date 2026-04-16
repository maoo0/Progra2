#include "Bibliotecas/Funciones.h"

int main() {

    char*** cursos, ***alumno_nom_mod;
    double *cursos_cred, escalas[5];
    int alumnos_cod, **alumnos;

    cargarCursosYEscalas(cursos, cursos_cred, escalas, "ArchivosDeDatos/Cursos.csv", "Escalas.csv");
    pruebaDeCargaDeCursos("ArchivosDeReporte/PruebaCursos.txt", cursos, cursos_cred);
    return 0;
}
