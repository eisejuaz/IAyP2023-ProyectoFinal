# proyectoIntegrador-iayp2023

Repo del proyecto integrador de IAyP 2023

## Estructura de archivos

### Main file

> malvinas.c

Este será el archivo donde implementamos todo.

### Header de nuestras funciones y acciones

> biblioteca.h

Este archivo funciona similar a las bibliotecas que importamos como <stdio.h>, <string.h> y otras. En nuestro caso se llama biblioteca.h y se importa usando comillas dobles: #include "biblioteca.h"
Aquí se almacenan todas las constantes y los perfiles de las funciones y acciones.

### Cuerpo de las funciones y acciones

> biblioteca.c

Este archivo tiene las declaraciones de todas nuestras funciones y acciones, cuyos perfiles deben estar incluidos en biblioteca.h, y que debe incluir #include "biblioteca.h" para llamarla y poder usar todas las constantes que allí se declaren.

## Personas ejemplo

Se puede testear usando el archivo malvinas.dat , que contiene ya precargadas varias personas con distintas fechas se nacimiento, función o estado Vive/fallecido.

> malvinas.dat

## Compilado

Este proyecto se compila con la siguiente línea:

```bash
gcc malvinas.c biblioteca.c -o malvinas
```
