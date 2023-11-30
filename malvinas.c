// Materia: Introducción a la algorítmica y programación
// Proyecto Integrador 2023
// Comisión: 3
// Alumnos: Gargiulo Franco y Gentile Octavio

//===========================
//
//  Librerias
//
//===========================

#include "biblioteca.h"

//===========================
//
//  Lexico
//
//===========================

int opcion, dni;
char menuCheck[2];
char mjeDespedida[50];
char nombreArchivo[25];

struct TData personas, personasMes;
struct TNodoS *cabFallecidos;
struct TNodoD *cabFuerza, *ultFuerza;

FILE *p, *q;

//===========================
//
//  Programa main
//
//===========================

int main() {
  strcpy(nombreArchivo, "malvinas.dat");
  desdeArchivoHaciaArreglo(p, nombreArchivo, &personas);

  do {
    mostrarMenuPrincipal();
    scanf("%d", &opcion);
    strcpy(menuCheck, "s");

    while (opcion < 1 || opcion > 9) {
      printf("\nLa opcion elegida no es valida, por favor elegir entre el 1 y el 9.\n");
      mostrarMenuPrincipal();
      scanf("%d", &opcion);
    };

    if (opcion == 1) {
      cargarPersona(&personas);
    } else if (opcion == 2) {
      if (!estaVacio(personas)) {
        obtenerDni(&dni);
        borrarPersona(dni, &personas);
      } else {
        printf("\nLa lista esta vacia, no podemos eliminar una persona.\n");
      };
    } else if (opcion == 3) {
      if (!estaVacio(personas)) {
        obtenerDni(&dni);
        modificarPersona(dni, &personas);
      } else {
        printf("\nLa lista esta vacia, no podemos eliminar una persona.\n");
      };
    } else if (opcion == 4) {
      mostrarArregloCompleto(personas);
    } else if (opcion == 5) {
      mostrarPorApellido(personas);
    } else if (opcion == 6) {
      cargarLSEFallecidos(personas, &cabFallecidos);
      mostrarLSEFallecidos(cabFallecidos);
      liberarLSE(&cabFallecidos);
    } else if (opcion == 7) {
      cargarLDEporFuerza(personas, &cabFuerza, &ultFuerza);
      mostrarLDEFuerza(cabFuerza, ultFuerza);
      liberarLDE(&cabFuerza, &ultFuerza);
    } else if (opcion == 8) {
      crearArregloPorMes(personas, &personasMes);
      burbujaPorMes(&personasMes);
      mostrarPorMes(personasMes);
    } else if (opcion == 9) {
      strcpy(menuCheck, "f");
    };

    if (strcmp(menuCheck, "f") != 0) {
      checkContinuar();
      getchar();
      scanf("%c", &menuCheck);
    };

  } while (strcmp(menuCheck, "f") != 0);

  strcpy(mjeDespedida, "\n\tMuchas gracias por usar nuestro programa!\n\n");
  desdeArregloHaciaArchivo(q, nombreArchivo, personas, 1);
  printf("%s", mjeDespedida);

  chomp();
  getchar();

  return 0;
};