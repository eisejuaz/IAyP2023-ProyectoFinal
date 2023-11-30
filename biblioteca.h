// Materia: Introducción a la algorítmica y programación
// Proyecto Integrador 2023
// Comisión: 3
// Alumnos: Gargiulo Franco y Gentile Octavio

#pragma once

//===========================
//
//  Bibliotecas
//
//===========================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//===========================
//
//  Constantes y tipos de datos
//
//===========================

#define Max 250

struct TFecha {
  int dia;
  int mes;
  int anio;
};

struct TPersona {
  int DNI;
  char nombre[20];
  char apellido[20];
  struct TFecha nacimiento;  // Campo de tipo TFecha para la fecha de nacimiento
  int edad;
  char ciudad[20];              // Ciudad de residencia actual
  char ciudadAntes[20];         // Ciudad de residencia en el momento de la guerra
  char DP[30];                  // Dirección Postal
  char CE[20];                  // Correo Electrónico
  char tel[15];                 // Teléfono
  int VF;                       // Vive/falleció: 1 si está vivo, 0 si ha fallecido
  struct TFecha fallecimiento;  // Campo de tipo TFecha para la fecha de fallecimiento
  int edadAlFallecer;
  char beneficio[20];  // Número beneficio nacional
  char CP[10];         // Código postal
  char provincia[50];  // Provincia de nacimiento
  int fuerza;          // Fuerza a la que perteneció: 1-Marina, 2-Gendarmeria, 3-Ejército, 4-Aeronáutica
  char destino[50];    // Destino en Malvinas
  char funcion[100];   // Función en Malvinas
  char grado[20];      // Grado
  char secuelas[400];  // Secuelas de la guerra, ampliamos este campo a 400 chars
};

struct TData {
  struct TPersona a[Max];
  int cant;
};

struct TNodoD {
  struct TPersona info;
  struct TNodoD *next;
  struct TNodoD *back;
};

struct TNodoS {
  struct TPersona info;
  struct TNodoS *next;
};

//===========================
//
//  Perfiles de funciones
//
//===========================

int buscarIndice(struct TPersona persona, struct TData arr);
int buscarIndiceDNI(int dni, struct TData arr);
int calcEdad(struct TFecha fec);
int calcEdadFallecimiento(struct TFecha fecNac, struct TFecha fecFall);
int checkDniRepetido(struct TData arr, int dni);
int checkFecha(struct TFecha fec);
int estaLleno(struct TData arr);
int estaVacio(struct TData arr);

//===========================
//
//  Perfiles de Acciones
//
//===========================

void borrarPersona(int dni, struct TData *arr);
void burbujaPorMes(struct TData *arr);
void cargarLDEporFuerza(struct TData arr, struct TNodoD **cab, struct TNodoD **ult);
void cargarLSEFallecidos(struct TData arr, struct TNodoS **cab);
void cargarPersona(struct TData *arr);
void checkContinuar();
void chomp();
void continuarModif(char *modif);
void crearArregloPorMes(struct TData arr, struct TData *arr2);
void crearLDEconF(struct TNodoD **cab, struct TNodoD **ult);
void crearLSEconF(struct TNodoS **cab);
void crearPersona(struct TPersona *pers, int dni);
void desdeArchivoHaciaArreglo(FILE *archivo, char nombreArchivo[25], struct TData *arr);
void desdeArregloHaciaArchivo(FILE *archivo, char nombre[25], struct TData arr, int tamano);
void ingresarFuerza(int *num);
void insertarPersona(struct TPersona pers, int ind, struct TData *arr);
void liberarLDE(struct TNodoD **cab, struct TNodoD **ult);
void liberarLSE(struct TNodoS **cab);
void mostrarMenuPrincipal();
void modificarPersona(int dni, struct TData *arr);
void mostrarArregloCompleto(struct TData arr);
void mostrarFuerza(int num);
void mostrarLDEFuerza(struct TNodoD *cab, struct TNodoD *ult);
void mostrarLSEFallecidos(struct TNodoS *cab);
void mostrarMjeModif();
void mostrarPersona(int ind, struct TData arr);
void mostrarPorApellido(struct TData arr);
void mostrarPorMes(struct TData arr);
void obtenerDni(int *num);
void suprimirUlt(struct TData *arr);