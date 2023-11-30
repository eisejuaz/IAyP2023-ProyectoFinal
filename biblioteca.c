//===========================
//
//  Header para nuestras constantes, librerias, structs, funciones, acciones
//
//===========================

#include "biblioteca.h"

//===========================
//
//  Funciones
//
//===========================

int buscarIndice(struct TPersona persona, struct TData arr) {
  // esta funcion indica en que posicion de un arreglo debe ubicarse una persona alfabeticamente
  // primero compara el apellido
  // en caso de igual apellido compara el nombre
  // y finalmente decide en dni, que es el campo univoco.
  // devuelve un entero con el indice, si el arreglo no esta vacio, o 0 en caso de estarlo.
  // sabemos que tiene como problema que las mayusculas no comparan igual que minusculas
  // en futuras iteraciones, deberiamos controla la carga de informacion en el arreglo para prevenir comportamientos no deseados

  int i;
  if ((estaVacio(arr) == 0)) {
    i = 0;
    while ((i < arr.cant) && (strcmp(persona.apellido, arr.a[i].apellido)) > 0) {
      i = i + 1;
    };
    if (strcmp(persona.apellido, arr.a[i].apellido) == 0) {
      while ((i < arr.cant) && (strcmp(persona.nombre, arr.a[i].nombre)) > 0) {
        i = i + 1;
      };
      if (strcmp(persona.nombre, arr.a[i].nombre) == 0) {
        while ((i < arr.cant) && (persona.DNI > arr.a[i].DNI)) {
          i = i + 1;
        };
      };
    };

    return i;

  } else {
    return 0;
  };
};

int buscarIndiceDNI(int dni, struct TData arr) {
  // esta funcion busca en que ubicacion de un arreglo se encuentra un dni
  // si lo encuentra, devuelve un entero con el indice, o -1 si no existe en el arreglo

  int i;

  if (estaVacio(arr) == 0) {
    i = 0;
    while ((i <= (arr.cant - 1)) && (dni != arr.a[i].DNI)) {
      i = i + 1;
    };
    if (i >= arr.cant) {
      i = -1;
    };
  };
  return i;
};

int calcEdad(struct TFecha fec) {
  // asigno a la variable edad el resultado de anio actual - anio de nacimiento
  // si aun no llego al mes de nacimiento, resto 1
  // si el mes es el mismo pero no llegue al dia, tambien resto 1
  // devuelvo esa variable entera edad

  struct TFecha hoy;
  int edad;

  // para manipular tiempo:
  // se declara una variable con tipo time_t que almacena lo que devuelve time(NULL)
  // se almacena en el struct tm fecha un puntero a localtime con la ubicacion de t
  // luego se pueden utilizar los campos tm_xxx para acceder a dia, mes y anio
  // mes va de 0-11, por eso se suma 1
  // anio cuenta el anio actual - 1900, por eso se le suman 1900
  time_t t = time(NULL);
  struct tm fecha = *localtime(&t);

  hoy.dia = fecha.tm_mday;
  hoy.mes = fecha.tm_mon + 1;
  hoy.anio = fecha.tm_year + 1900;

  edad = hoy.anio - fec.anio;

  if (hoy.mes < fec.mes) {
    edad--;
  } else if (hoy.mes == fec.mes && hoy.dia < fec.dia) {
    edad--;
  };

  return edad;
};

int calcEdadFallecimiento(struct TFecha fecNac, struct TFecha fecFall) {
  // analoga a la funcion calcEdad, pero ahora sustrayendo la fecha de nacimiento a la fecha de fallecimiento

  struct TFecha hoy;
  int edad;

  // se declara una variable con tipo time_t que almacena lo que devuelve time(NULL)
  time_t t = time(NULL);
  // se almacena en el struct tm fecha un puntero a localtime con la ubicacion de t
  struct tm fecha = *localtime(&t);

  // luego se pueden utilizar los campos tm_xxx para acceder a dia, mes y anio
  // mes va de 0-11, por eso se suma 1
  // anio cuenta el anio actual - 1900, por eso se le suman 1900
  hoy.dia = fecha.tm_mday;
  hoy.mes = fecha.tm_mon + 1;
  hoy.anio = fecha.tm_year + 1900;

  edad = fecFall.anio - fecNac.anio;

  if (fecFall.mes < fecNac.mes) {
    edad--;
  } else if (fecFall.mes == fecNac.mes && fecFall.dia < fecNac.dia) {
    edad--;
  };

  return edad;
};

int checkDniRepetido(struct TData arr, int dni) {
  // esta funcion devuelve 1 en caso de encontrar un dni en un arreglo o 0 en caso de que no exista
  // se usa para no permitir duplicados
  int i;
  for (i = 0; i < arr.cant; i++) {
    if (arr.a[i].DNI == dni) {
      return 1;
    };
  };
  return 0;
};

int checkFecha(struct TFecha fec) {
  // el uso de variables temporales es analogo a calcEdad
  // retorno 0 si la fecha que intentan ingresar es posterior al dia de hoy, y 1 si es igual o menor
  // de esta manera validamos que no se ingresen fechas posteriores al dia corriente en que se usa la aplicacion

  struct TFecha hoy;

  // se declara una variable con tipo de dato time_t que almacena lo que devuelve time(NULL)
  time_t t = time(NULL);
  // se almacena en el struct tm fecha un puntero a localtime con la ubicacion de t
  struct tm fecha = *localtime(&t);

  // luego se pueden utilizar los campos tm_xxx para acceder a dia, mes y anio
  // mes va de 0-11, por eso se suma 1
  // anio cuenta el anio actual - 1900, por eso se le suman 1900
  hoy.dia = fecha.tm_mday;
  hoy.mes = fecha.tm_mon + 1;
  hoy.anio = fecha.tm_year + 1900;

  if ((fec.anio > hoy.anio) || (fec.anio < 100) ||
      (fec.mes < 1) || (fec.mes > 12) ||
      (fec.dia < 1) || (fec.dia > 31) ||
      (fec.anio == hoy.anio && fec.mes > hoy.mes) || (fec.anio == hoy.anio && fec.dia > hoy.dia)) {
    return 0;
  } else {
    return 1;
  };
};

int estaLleno(struct TData arr) {
  // funcion usada para validar si hay espacio en el arreglo
  return arr.cant == Max;
};

int estaVacio(struct TData arr) {
  // funcion usada para validar si el arreglo esta vacio
  return arr.cant == 0;
};

//===========================
//
//  Acciones
//
//===========================

void borrarPersona(int dni, struct TData *arr) {
  // accion que elimina una persona mediante su dni
  // al quitar un elemento, luego realiza el corrimiento correspondiente
  // con la optimizacion de que, si e el ultimo, solo disminuye el cant en 1 unidad
  int j;

  if (estaVacio(*arr)) {
    printf("\n\tNo hay nadie en la lista.\n");
  } else {
    // debe confirmar que el dni efectivamente exista antes de realizar el procedimiento
    j = buscarIndiceDNI(dni, *arr);
    if (j == -1) {
      printf("\n\tDNI no encontrado.\n");
    } else {
      printf("\n\tLa persona eliminada de la lista es %s %s\n\t", arr->a[buscarIndiceDNI(dni, *arr)].apellido, arr->a[buscarIndiceDNI(dni, *arr)].nombre);
      if (j == arr->cant - 1) {
        suprimirUlt(arr);
      } else {
        while (j < arr->cant - 1) {
          arr->a[arr->cant - 2] = arr->a[arr->cant - 1];
          j = j + 1;
        };
        arr->cant = arr->cant - 1;
      };
    };
  };
};

void burbujaPorMes(struct TData *arr) {
  // implementacion del bubble sort para organizar el arreglo que se genera con todas las personas que cumplen anios en un mismo mes
  // ordena de menor a mayor segun el dia.
  // permitiria saber, por ejemplo, armar un calendario de salutaciones de cumpleanios dia por dia.

  struct TPersona aux;
  int i, j;

  i = arr->cant - 1;

  while (i > 0) {
    j = 0;
    while (j < i) {
      if (arr->a[j].nacimiento.dia > arr->a[j + 1].nacimiento.dia) {
        aux = arr->a[j];
        arr->a[j] = arr->a[j + 1];
        arr->a[j + 1] = aux;
      };
      j++;
    };
    i--;
  };
};

void cargarLDEporFuerza(struct TData arr, struct TNodoD **cab, struct TNodoD **ult) {
  // esta accion arma una LDE segun el campo fuerza
  // sigue la misma logica que cargarFallecidos para mantener el orden alfabetico original del arreglo

  struct TNodoD *aux, *aux2;
  int fuerza;
  int i;

  ingresarFuerza(&fuerza);

  crearLDEconF(cab, ult);

  i = arr.cant - 1;

  while (i >= 0) {
    if (arr.a[i].fuerza == fuerza) {
      aux = (*cab);
      aux2 = (struct TNodoD *)malloc(sizeof(struct TNodoD));
      aux2->info = arr.a[i];
      aux2->next = aux->next;
      aux2->back = aux;
      aux->next->back = aux2;
      aux->next = aux2;
    };
    i = i - 1;
  };
};

void cargarLSEFallecidos(struct TData arr, struct TNodoS **cab) {
  // esta accion genera una LSE que contiene aquellas personas que han fallecido
  // inserta todas las personas cuyo campo VF sea 0
  // la particularidad que tiene es que se genera leyendo el arreglo de "de derecha a izquierda" e incorporando siempre a la cabeza.
  // con esto mantiene el orden alfabetico que mantiene el arreglo

  struct TNodoS *aux;
  int i;

  if (estaVacio(arr)) {
    printf("No hay nadie en la lista.");
  } else {
    crearLSEconF(cab);
    i = arr.cant - 1;
    while (i >= 0) {
      if (arr.a[i].VF == 0) {
        aux = (struct TNodoS *)malloc(sizeof(struct TNodoS));
        strcpy(aux->info.nombre, arr.a[i].nombre);
        strcpy(aux->info.apellido, arr.a[i].apellido);
        aux->info.DNI = arr.a[i].DNI;
        aux->info.nacimiento.dia = arr.a[i].nacimiento.dia;
        aux->info.nacimiento.mes = arr.a[i].nacimiento.mes;
        aux->info.nacimiento.anio = arr.a[i].nacimiento.anio;
        strcpy(aux->info.ciudad, arr.a[i].ciudad);
        aux->next = (*cab)->next;
        (*cab)->next = aux;
      };
      i = i - 1;
    };
  };
};

void cargarPersona(struct TData *arr) {
  // esta accion crea una persona, luego busca el indice que le corresponderia en el arreglo y finalmente la inserta
  // valida que el arreglo tenga lugar y que el arreglo tenga lugar disponible

  int i, dni;
  struct TPersona persona;

  if (!estaLleno(*arr)) {
    printf("\n===========================================================================================\n");
    printf("\n\tIngrese el DNI de la persona a cargar: ");
    scanf("%d", &dni);
    if (checkDniRepetido(*arr, dni) == 0) {
      crearPersona(&persona, dni);

      i = buscarIndice(persona, *arr);

      insertarPersona(persona, i, arr);

    } else {
      printf("\n\tEl dni esta repetido, la persona ya esta cargada.\n\n");
    };
  } else {
    printf("\nLista llena.\n");
  };
};

void checkContinuar() {
  // accion meramente informativa
  char mjeCorte[200];
  printf("\n==========================================================================================");
  strcpy(mjeCorte, "\n\n\tPresione la tecla Enter para volver al menu.\n\n\tSi desea finalizar, presione 'f'.\n\n");
  printf("%s", mjeCorte);
  printf("==========================================================================================");
};

void chomp() {
  // consume los espacios vacios y protege de inputs indeseados
  while (getchar() != '\n') {
  };
};

void continuarModif(char *modif) {
  // esta accion se usa para revisar si el usuario quiere continuar modificando campos en modificarPersona(...)
  char mjeContinuar[400];
  char modifCheck[2];

  strcpy(mjeContinuar, "\n\n==========================================================================================\n\n\tSi desea hacer otro cambio, presione 's'.\n\n\tDe lo contrario,  presione 'n' para finalizar. \n\n==========================================================================================");
  printf("%s", mjeContinuar);
  scanf("%s", modif);

  while (strcmp(modif, "n") != 0 && strcmp(modif, "s") != 0) {
    printf("\n\n> Error! Usted a presionado '%s'. Por favor, ingrese una letra valida.\n\n", modif);
    strcpy(mjeContinuar, "\n> Si desea hacer otro cambio, presione 's'. De lo contrario,  presione 'n' para finalizar. \n\n");
    printf("%s", mjeContinuar);
    scanf("%s", modif);
  };
};

void crearArregloPorMes(struct TData arr, struct TData *arr2) {
  // esta accion recorre el arreglo principal buscando personas que hayan nacido en un mes que se solicita al usuario
  // si nacimiento.mes coincide, se insertan en el segundo arreglo
  // como los indices no coincidiran necesariamente, salvo que todas las personas cargadas hayan nacido el mismo mes, debemos usar variables diferentes (i, j)

  int i, j, mes;
  struct TPersona persona;

  if (estaVacio(arr) == 1) {
    printf("\n\tEl arreglo esta vacio.\n");
  } else {
    printf("\n\tIngrese un mes siendo enero el numero 1 y diciembre el numero 12.\n\n\tUsted escoge: ");
    scanf("%d", &mes);
    i = 0;
    j = 0;
    arr2->cant = 0;
    while (i < arr.cant) {
      if (arr.a[i].nacimiento.mes == mes) {
        arr2->a[j] = arr.a[i];
        j++;
        arr2->cant++;
      };
      i++;
    };
  };
};

void crearLDEconF(struct TNodoD **cab, struct TNodoD **ult) {
  // accion que crea una LDE con ficticio

  struct TNodoD *aux;
  (*cab) = NULL;
  (*ult) = NULL;
  aux = (struct TNodoD *)malloc(sizeof(struct TNodoD));
  aux->next = (*cab);
  aux->back = (*ult);
  (*cab) = aux;
  aux = (struct TNodoD *)malloc(sizeof(struct TNodoD));
  aux->next = (*ult);
  aux->back = (*cab);
  (*ult) = aux;
  (*cab)->next = (*ult);
};

void crearLSEconF(struct TNodoS **cab) {
  // accion que crea una LSE con ficticio

  struct TNodoS *aux;
  (*cab) = NULL;
  aux = (struct TNodoS *)malloc(sizeof(struct TNodoS));
  aux->next = (*cab);
  (*cab) = aux;
};

void crearPersona(struct TPersona *pers, int dni) {
  // accion que crea campo por campo una persona
  // solo se ejecutara si el dni fue previamente validado

  char mje[100];
  char sOn[2];

  pers->DNI = dni;

  printf("\n\n\tIngrese el nombre: ");
  chomp();
  scanf("%[^\n]", &pers->nombre);

  printf("\n\tIngrese el apellido: ");
  chomp();
  scanf("%[^\n]", &pers->apellido);

  printf("\n\tAhora ingresaremos la fecha de nacimiento de la persona.");
  printf("\n\n\tIngrese el dia de nacimiento: ");
  chomp();
  scanf("%d", &pers->nacimiento.dia);

  printf("\n\tIngrese el mes de nacimiento: ");
  chomp();
  scanf("%d", &pers->nacimiento.mes);

  printf("\n\tIngrese el anio de nacimiento en formato de 4 digitos: ");
  chomp();
  scanf("%d", &pers->nacimiento.anio);

  // Validamos el ingreso de fecha de nacimiento
  while (checkFecha(pers->nacimiento) == 0) {
    printf("La fecha ingresada fue: %02d-%02d-%d\n", pers->nacimiento.dia, pers->nacimiento.mes, pers->nacimiento.anio);
    printf("La misma no es valida, debe haber un error. Ingrese nuevamente, por favor.\n");
    printf("Ingrese el dia de nacimiento:\n");
    chomp();
    scanf("%d", &pers->nacimiento.dia);

    printf("Ingrese el mes de nacimiento:\n");
    chomp();
    scanf("%d", &pers->nacimiento.mes);

    printf("Ingrese el anio de nacimiento en formato de 4 digitos:\n");
    chomp();
    scanf("%d", &pers->nacimiento.anio);
  }
  printf("\n\tLa fecha ingresada fue: %02d-%02d-%d\n", pers->nacimiento.dia, pers->nacimiento.mes, pers->nacimiento.anio);

  printf("\n\tIngrese el domicilio actual: ");
  chomp();
  scanf("%[^\n]", &pers->DP);

  printf("\n\tIngrese la ciudad de residencia actual: ");
  chomp();
  scanf("%[^\n]", &pers->ciudad);

  printf("\n\tIngrese el codigo postal: ");
  chomp();
  scanf("%[^\n]", &pers->CP);

  printf("\n\tIngrese la ciudad de residencia al momento de la guerra: ");
  chomp();
  scanf("%[^\n]", &pers->ciudadAntes);

  printf("\n\tIngrese el correo electronico: ");
  chomp();
  scanf("%[^\n]", &pers->CE);

  printf("\n\tIngrese el telefono: ");
  chomp();
  scanf("%[^\n]", &pers->tel);

  printf("\n\tIngrese el numero de beneficio nacional: ");
  chomp();
  scanf("%[^\n]", &pers->beneficio);

  printf("\n\tIngrese la provincia de nacimiento: ");
  chomp();
  scanf("%[^\n]", &pers->provincia);

  ingresarFuerza(&pers->fuerza);

  printf("\n\tIngrese el destino que tuvo en Malvinas: ");
  chomp();
  scanf("%[^\n]", &pers->destino);

  printf("\n\tIngrese la funcion que cumplio: ");
  chomp();
  scanf("%[^\n]", &pers->funcion);

  printf("\n\tIngrese el grado militar de la persona: ");
  chomp();
  scanf("%[^\n]", &pers->grado);

  printf("\n\tIngrese las secuelas que tiene a causa de la guerra: ");
  chomp();
  scanf("%[^\n]", &pers->secuelas);

  printf("\n\tIngrese Si o No. La persona vive? ");
  chomp();
  scanf("%[^\n]", &sOn);

  // Chequeamos si vive o no
  // si no vive, pedir fallecimiento, validar y calcular edad de fallecimiento
  // si vive, calcular edad comun
  while (!(strcmp("si", sOn) == 0 || strcmp("SI", sOn) == 0 || strcmp("Si", sOn) == 0 ||
           strcmp("no", sOn) == 0 || strcmp("NO", sOn) == 0 || strcmp("No", sOn) == 0)) {
    printf("El valor ingresado no es valido. Por favor, ingrese Si o No.\n");
    chomp();
    scanf("%[^\n]", &sOn);
  };

  if (strcmp("no", sOn) == 0 || strcmp("NO", sOn) == 0 || strcmp("No", sOn) == 0) {
    pers->VF = 0;
    printf("\n\n\tAhora ingresaremos la fecha de fallecimiento de la persona.");
    printf("\n\n\tIngrese el dia de fallecimiento: ");
    chomp();
    scanf("%d", &pers->fallecimiento.dia);

    printf("\n\tIngrese el mes de fallecimiento: ");
    chomp();
    scanf("%d", &pers->fallecimiento.mes);

    printf("\n\tIngrese el anio de fallecimiento en formato de 4 digitos: ");
    chomp();
    scanf("%d", &pers->fallecimiento.anio);

    // Validamos el ingreso de fecha de fallecimiento
    while (checkFecha(pers->fallecimiento) == 0) {
      printf("La fecha ingresada fue: %02d-%02d-%d\n", pers->fallecimiento.dia, pers->fallecimiento.mes, pers->fallecimiento.anio);
      printf("La misma no es valida, debe haber un error. Ingrese nuevamente, por favor.\n");
      printf("Ingrese el dia de fallecimiento:\n");
      chomp();
      scanf("%d", &pers->fallecimiento.dia);

      printf("Ingrese el mes de fallecimiento:\n");
      chomp();
      scanf("%d", &pers->fallecimiento.mes);

      printf("Ingrese el anio de fallecimiento en formato de 4 digitos:\n");
      chomp();
      scanf("%d", &pers->fallecimiento.anio);
    };

    printf("\n\tLa fecha ingresada fue: %02d-%02d-%d", pers->fallecimiento.dia, pers->fallecimiento.mes, pers->fallecimiento.anio);

    pers->edadAlFallecer = calcEdadFallecimiento(pers->nacimiento, pers->fallecimiento);
  };

  if (strcmp("si", sOn) == 0 || strcmp("SI", sOn) == 0 || strcmp("Si", sOn) == 0) {
    pers->VF = 1;
    pers->edad = calcEdad(pers->nacimiento);
  };
};

void desdeArchivoHaciaArreglo(FILE *archivo, char nombreArchivo[25], struct TData *arr) {
  // esta accion es la que nos permite, durante la ejecucion del programa, contar con un arreglo de los elementos que previamente se hayan ingresado y se encuentren almacenados en un archivo.
  // va leyendolos uno a uno y asignandolos en igual orden al arreglo principal que se utiliza en el programa
  // si el archivo existe, se abre en modo lectura
  // si no existe, se crea
  struct TPersona persona;
  int i;

  if ((archivo = fopen(nombreArchivo, "rb")) != NULL) {
    i = 0;
    while (fread(&persona, sizeof(struct TPersona), 1, archivo) == 1) {
      arr->a[i] = persona;
      arr->cant = i + 1;
      i++;
    };
  };
  if ((archivo = fopen(nombreArchivo, "a+b")) != NULL) {
    fseek(archivo, 0, SEEK_SET);
    i = 0;
    while (fread(&persona, sizeof(struct TPersona), 1, archivo) == 1) {
      arr->a[i] = persona;
      arr->cant = i + 1;
      i++;
    };
  } else {
    printf("\nError al abrir el archivo");
  };
  fclose(archivo);
};

void desdeArregloHaciaArchivo(FILE *archivo, char nombre[25], struct TData arr, int tamano) {
  // esta funcion se utiliza al final de la ejecucion del programa, para poder persistir la informacion del arreglo principal.
  // cada elemento del arreglo se copia uno a uno en el archivo
  // decidimos hacer una escritura desde cero en cada uso

  struct TPersona pers;
  int i;
  struct TData test;

  archivo = fopen(nombre, "wb+");  // Abre el archivo para añadir contenido binario

  if (archivo == NULL) {
    printf("No se pudo abrir el archivo.");
  } else {
    fseek(archivo, 0, SEEK_SET);
    // Escribir en el archivo
    for (i = 0; i < arr.cant; i++) {
      // leer persona del arreglo en pers
      pers = arr.a[i];
      fwrite(&pers, sizeof(pers), tamano, archivo);
    };

    fclose(archivo);
  };
};

void ingresarFuerza(int *num) {
  // accion que usamos para validar que la fuerza ingresada sea un entero entre 1 y 4
  // combina con mostrarFuerza, que muestra al usuario el campo fuerza mediante su equivalente en texto

  char mje[100];

  strcpy(mje, "\n\tIngrese la fuerza:\n\n\t1. Marina.\n\t2. Gendarmeria.\n\t3. Ejercito.\n\t4. Aeronautica.\n\n");
  printf("%s", mje);
  printf("\tUsted ha elegido: ");

  scanf("%d", num);

  while (*num < 1 || *num > 4) {
    strcpy(mje, "\n\tLa opcion ingresada no es valida, ingrese nuevamente, por favor.\n");
    printf("%s", mje);
    printf("\tUsted ha elegido: ");
    scanf("%d", num);
  };
};

void insertarPersona(struct TPersona pers, int ind, struct TData *arr) {
  // esta accion inserta una persona en el arreglo
  // si esta vacio, en la posicion 1
  // si no, desplaza los elementos desde el final hasta el indice que corresponderia, "hace lugar", amplia el cant y finalmente asigna en esa posicion

  int j;

  if (estaVacio(*arr) == 1) {
    arr->cant = 1;
  } else {
    j = arr->cant - 1;
    while (j >= ind) {
      arr->a[j + 1] = arr->a[j];
      j = j - 1;
    };
    arr->cant = arr->cant + 1;
  };
  arr->a[ind] = pers;
};

void liberarLDE(struct TNodoD **cab, struct TNodoD **ult) {
  // accion para liberar los punteros de la LDE

  struct TNodoD *aux, *r;
  aux = (*cab)->next;
  while (aux->next != NULL) {
    r = aux;
    aux = aux->next;
    free(r);
  }
  (*cab)->next = (*ult);
  (*ult)->back = (*cab);
};

void liberarLSE(struct TNodoS **cab) {
  // accion para liberar los punteros de la LSE

  struct TNodoS *aux, *r;
  aux = (*cab)->next;
  while (aux != NULL) {
    r = aux;
    aux = aux->next;
    free(r);
  }
  (*cab)->next = NULL;
};

void mostrarMenuPrincipal() {
  // accion meramente informativa
  char mjeInicial[1000];

  strcpy(mjeInicial, "\n=============================== Elija una opcion, por favor ===============================\n\n\t1. Insertar persona \n\n\t2. Eliminar una persona (ingrese su dni).\n\n\t3. Modificar datos de una persona (ingrese su dni).\n\n\t4. Listar todos los integrantes.\n\n\t5. Listar por apellido.\n\n\t6. Listar fallecidos.\n\n\t7. Listar personas segun la fuerza a la que pertecio.\n\n\t8. Listar personas que cumplen anios en un mes.\n\n\t9. Guardar y salir.\n\n===========================================================================================");
  printf("%s", mjeInicial);
};

void modificarPersona(int dni, struct TData *arr) {
  // esta accion es la que permite modificar una persona ya creada.
  // mediante un menu de opciones, el usuario elige que campos modificar, a excepcion del dni
  // si se afectan apellido o nombre, se reordena el arreglo, ya que podria modificar la ubicacion alfabetica
  // mostramos el cambio parcial del campo que se hizo, el la persona completa resultante

  char mje[100];
  char mjeContinuar[400];
  char modifCheck[2];
  int i, opcionModif, errorDni;
  struct TPersona aux;

  char nuevoNombre[20];
  char nuevoApellido[20];
  struct TFecha nuevoNacimiento;
  char nuevoCiudad[20];
  char nuevoCiudadAntes[20];
  char nuevoDP[30];
  char nuevoCE[20];
  char nuevoTel[15];
  int nuevoVF;
  struct TFecha nuevoFallecimiento;
  char nuevoBeneficio[20];
  char nuevoCP[10];
  char nuevoProvincia[50];
  int nuevoFuerza;
  char nuevoDestino[50];
  char nuevoFuncion[100];
  char nuevoGrado[20];
  char nuevoSecuelas[400];

  if (estaVacio(*arr)) {
    strcpy(mje, "\nNo hay nadie en la lista, intente nuevamente luego de crearla");
    printf("%s", mje);
  } else {
    i = buscarIndiceDNI(dni, *arr);

    if (i == -1) {
      strcpy(mje, "\n\tDNI no encontrado, intente nuevamente.\n");
      printf("%s", mje);

      printf("\n\tDesea buscar otro DNI?\n\tPresione 1 para indicar que si, o 0 para salir de este menu.\n");
      scanf("%d", &errorDni);
      if (errorDni == 1)
        modificarPersona(dni, arr);
    } else {
      strcpy(modifCheck, "s");
      while (strcmp(modifCheck, "s") == 0) {
        printf("\n\n\tVamos a modificar los datos de %s %s\n", arr->a[i].apellido, arr->a[i].nombre);

        mostrarMjeModif();

        scanf("%d", &opcionModif);
        printf("\n\n\tUsted ha ingresado la opcion: %d.\n", opcionModif);

        if (opcionModif < 1 || opcionModif > 18) {
          printf("\nError! Por favor, ingrese una opcion valida.\n");
        };

        if (opcionModif == 1) {
          printf("\n\tEl nombre actual es: %s", arr->a[i].nombre);
          printf("\n\tIngrese el nuevo nombre: ");
          chomp();
          scanf("%[^\n]", &nuevoNombre);
          strcpy(arr->a[i].nombre, nuevoNombre);

          // reordeno
          aux = arr->a[i];
          borrarPersona(arr->a[i].DNI, arr);
          insertarPersona(aux, buscarIndice(aux, *arr), arr);
        } else if (opcionModif == 2) {
          printf("\n\tEl apellido actual es: %s", arr->a[i].apellido);
          printf("\n\tIngrese el nuevo apellido: ");
          chomp();
          scanf("%[^\n]", &nuevoApellido);
          strcpy(arr->a[i].apellido, nuevoApellido);

          // reordeno
          aux = arr->a[i];
          borrarPersona(arr->a[i].DNI, arr);
          insertarPersona(aux, buscarIndice(aux, *arr), arr);
        } else if (opcionModif == 3) {
          printf("\n\tLa fecha de nacimiento actual es %02d-%02d-%d \n", arr->a[i].nacimiento.dia, arr->a[i].nacimiento.mes, arr->a[i].nacimiento.anio);
          printf("\n\tAhora ingresaremos la nueva fecha de nacimiento de la persona:\n");
          printf("\n\tIngrese el nuevo dia de nacimiento: ");
          chomp();
          scanf("%d", &nuevoNacimiento.dia);

          printf("\n\tIngrese el mes de nacimiento: ");
          chomp();
          scanf("%d", &nuevoNacimiento.mes);

          printf("\n\tIngrese el anio de nacimiento en formato de 4 digitos: ");
          chomp();
          scanf("%d", &nuevoNacimiento.anio);

          // Validamos el ingreso de fecha de nacimiento
          while (checkFecha(nuevoNacimiento) == 0) {
            printf("\n\tLa fecha ingresada fue: %02d-%02d-%d\n", nuevoNacimiento.dia, nuevoNacimiento.mes, nuevoNacimiento.anio);
            printf("\n\tLa misma no es valida, debe haber un error. Ingrese nuevamente, por favor.\n");
            printf("\n\tIngrese el dia de nacimiento: ");
            chomp();
            scanf("%d", &nuevoNacimiento.dia);

            printf("\n\ttIngrese el mes de nacimiento: ");
            chomp();
            scanf("%d", &nuevoNacimiento.mes);

            printf("\n\tIngrese el anio de nacimiento en formato de 4 digitos: ");
            chomp();
            scanf("%d", &nuevoNacimiento.anio);
          };

          arr->a[i].nacimiento.dia = nuevoNacimiento.dia;
          arr->a[i].nacimiento.mes = nuevoNacimiento.mes;
          arr->a[i].nacimiento.anio = nuevoNacimiento.anio;

          printf("\n\tLa fecha de nacimiento actualizada es %02d-%02d-%d \n", arr->a[i].nacimiento.dia, arr->a[i].nacimiento.mes, arr->a[i].nacimiento.anio);
        } else if (opcionModif == 4) {
          printf("\n\tLa ciudad de residencia actual es: %s", arr->a[i].ciudad);
          printf("\n\tIngrese la nueva ciudad de residencia: ");
          chomp();
          scanf("%[^\n]", &nuevoCiudad);
          strcpy(arr->a[i].ciudad, nuevoCiudad);
        } else if (opcionModif == 5) {
          printf("\n\tLa ciudad de residencia al momento de la guerra actual es: %s", arr->a[i].ciudadAntes);
          printf("\n\tIngrese la nueva ciudad de residencia al momento de la guerra: ");
          chomp();
          scanf("%[^\n]", &nuevoCiudadAntes);
          strcpy(arr->a[i].ciudadAntes, nuevoCiudadAntes);
        } else if (opcionModif == 6) {
          printf("\n\tEl domicilio actual es: %s", arr->a[i].DP);
          printf("\n\tIngrese el nuevo domicilio: ");
          chomp();
          scanf("%[^\n]", &nuevoDP);
          strcpy(arr->a[i].DP, nuevoDP);
        } else if (opcionModif == 7) {
          printf("\n\tEl correo electronico actual es: %s", arr->a[i].CE);
          printf("\n\tIngrese el nuevo correo electronico: ");
          chomp();
          scanf("%[^\n]", &nuevoCE);
          strcpy(arr->a[i].CE, nuevoCE);
        } else if (opcionModif == 8) {
          printf("\n\tEl telefono actual es: %s", arr->a[i].tel);
          printf("\n\tIngrese el nuevo telefono: ");
          chomp();
          scanf("%[^\n]", &nuevoTel);
          strcpy(arr->a[i].tel, nuevoTel);
        } else if (opcionModif == 9) {
          if (arr->a[i].VF == 1) {
            printf("\n\tDesea indicar que la persona ha fallecido?\n\tPresione 0 para indicar que si, o 1 para salir de este menu.\n");
            scanf("%d", &nuevoVF);
          };
          if (nuevoVF == 0) {
            arr->a[i].VF = nuevoVF;
            printf("Ahora ingresaremos la nueva fecha de fallecimiento de la persona:\n");
            printf("Ingrese el nuevo dia de fallecimiento:\n");
            chomp();
            scanf("%d", &nuevoFallecimiento.dia);

            printf("Ingrese el mes de fallecimiento:\n");
            chomp();
            scanf("%d", &nuevoFallecimiento.mes);

            printf("Ingrese el anio de fallecimiento en formato de 4 digitos:\n");
            chomp();
            scanf("%d", &nuevoFallecimiento.anio);

            // Validamos el ingreso de fecha de fallecimiento
            while (checkFecha(nuevoFallecimiento) == 0) {
              printf("\nLa fecha ingresada fue: %02d-%02d-%d\n", nuevoFallecimiento.dia, nuevoFallecimiento.mes, nuevoFallecimiento.anio);
              printf("\nLa misma no es valida, debe haber un error. Ingrese nuevamente, por favor.\n");
              printf("Ingrese el dia de fallecimiento:\n");
              chomp();
              scanf("%d", &nuevoFallecimiento.dia);

              printf("Ingrese el mes de fallecimiento:\n");
              chomp();
              scanf("%d", &nuevoFallecimiento.mes);

              printf("Ingrese el anio de fallecimiento en formato de 4 digitos:\n");
              chomp();
              scanf("%d", &nuevoFallecimiento.anio);
            };
            arr->a[i].fallecimiento.dia = nuevoFallecimiento.dia;
            arr->a[i].fallecimiento.mes = nuevoFallecimiento.mes;
            arr->a[i].fallecimiento.anio = nuevoFallecimiento.anio;

            printf("\nLa fecha de fallecimiento actualizada es %02d-%02d-%d \n", arr->a[i].fallecimiento.dia, arr->a[i].fallecimiento.mes, arr->a[i].fallecimiento.anio);
          };
        } else if (opcionModif == 10) {
          printf("\n\tEl numero de beneficio nacional actual es: %s", arr->a[i].beneficio);
          printf("\n\tIngrese el nuevo numero de beneficio nacional: ");
          chomp();
          scanf("%[^\n]", &nuevoBeneficio);
          strcpy(arr->a[i].beneficio, nuevoBeneficio);
        } else if (opcionModif == 11) {
          printf("\n\tEl codigo postal actual es: %s", arr->a[i].CP);
          printf("\n\tIngrese el nuevo codigo postal: ");
          chomp();
          scanf("%[^\n]", &nuevoCP);
          strcpy(arr->a[i].CP, nuevoCP);
        } else if (opcionModif == 12) {
          printf("\n\tLa provincia de nacimiento actual es: %s", arr->a[i].ciudad);
          printf("\n\tIngrese la nueva provincia de nacimiento: ");
          chomp();
          scanf("%[^\n]", &nuevoProvincia);
          strcpy(arr->a[i].provincia, nuevoProvincia);
        } else if (opcionModif == 13) {
          printf("\n\tLa fuerza actual a la que pertenecio es: ");
          mostrarFuerza(arr->a[i].fuerza);
          printf("Procederemos a actualizarla.\n\n");
          ingresarFuerza(&nuevoFuerza);
          arr->a[i].fuerza = nuevoFuerza;
          printf("\n\tLa fuerza a la que pertenecio actualizada es: ");
          mostrarFuerza(arr->a[i].fuerza);
        } else if (opcionModif == 14) {
          printf("\n\tEl destino en Malvinas actual es: %s", arr->a[i].destino);
          printf("\n\tIngrese el nuevo destino en Malvinas: ");
          chomp();
          scanf("%[^\n]", &nuevoDestino);
          strcpy(arr->a[i].destino, nuevoDestino);
        } else if (opcionModif == 15) {
          printf("\n\tLa funcion en Malvinas actual es: %s", arr->a[i].funcion);
          printf("\n\tIngrese la nueva funcion en Malvinas: ");
          chomp();
          scanf("%[^\n]", &nuevoFuncion);
          strcpy(arr->a[i].funcion, nuevoFuncion);
        } else if (opcionModif == 16) {
          printf("\n\tEl grado actual es: %s", arr->a[i].grado);
          printf("\n\tIngrese el nuevo grado: ");
          chomp();
          scanf("%[^\n]", &nuevoGrado);
          strcpy(arr->a[i].grado, nuevoGrado);
        } else if (opcionModif == 17) {
          printf("\n\tLas secuelas actuales ingresadas son: %s", arr->a[i].secuelas);
          printf("\n\tIngrese las nuevas secuelas: ");
          chomp();
          scanf("%[^\n]", &nuevoSecuelas);
          strcpy(arr->a[i].secuelas, nuevoSecuelas);
        } else if (opcionModif == 18) {
          arr->a[i].VF = 1;
          printf("\n\tSe ha actualizado la informacion y ahora esta persona figura con vida en la base de datos.\n");
        };

        printf("\n\tA continuacion les mostraremos el resultado de la modificacion hecha: \n");
        mostrarPersona(buscarIndiceDNI(dni, *arr), *arr);
        continuarModif(modifCheck);
      };
    };
  };
};

void mostrarArregloCompleto(struct TData arr) {
  // esta accion muestra una a una todas las personas de un arreglo

  int i;

  if (estaVacio(arr) == 0) {
    i = 0;
    while (i < arr.cant) {
      mostrarPersona(i, arr);
      i = i + 1;
    };
  } else {
    printf("\n\tLa lista esta vacia.\n");
  };
};

void mostrarFuerza(int num) {
  // accion utilizada cada vez que se muestra el campo fuerza de una persona, imprimiendo la palabra que representa cada numero

  if (num == 1) {
    printf("Marina.\n");
  } else if (num == 2) {
    printf("Gendarmeria.\n");
  } else if (num == 3) {
    printf("Ejercito.\n");
  } else if (num == 4) {
    printf("Aeronautica.\n");
  };
};

void mostrarLDEFuerza(struct TNodoD *cab, struct TNodoD *ult) {
  // accion que muestra los campos requeridos en la consigna de cada persona de una fuerza recorriendo la LDE

  char mje[150];
  struct TNodoD *aux;

  aux = cab->next;

  if (aux->info.fuerza < 1 || aux->info.fuerza > 4) {
    strcpy(mje, "\n\tLa lista esta vacia.\n");
    printf("%s", mje);
  } else {
    printf("\n\n===========================================================================================\n");
    printf("\n\n\tMostrando personas de la siguiente fuerza: ");
    mostrarFuerza((*cab).next->info.fuerza);
    while (aux->next != NULL) {
      printf("\n*\tNombre: %s\n", aux->info.nombre);
      printf("\tApellido: %s\n", aux->info.apellido);
      printf("\tFecha de nacimiento: %02d-%02d-%d\n", aux->info.nacimiento.dia, aux->info.nacimiento.mes, aux->info.nacimiento.anio);
      printf("\tCiudad de residencia: %s\n", aux->info.ciudad);
      printf("\tProvincia: %s\n", aux->info.provincia);
      printf("\tDomicilio: %s\n", aux->info.DP);
      printf("\tCodigo postal: %s\n", aux->info.CP);
      printf("\tCiudad al momento de la guerra: %s\n", aux->info.ciudadAntes);
      printf("\tCorreo electronico: %s\n", aux->info.CE);
      printf("\tTelefono: %s\n", aux->info.tel);
      printf("\tNumero de beneficio nacional: %s\n", aux->info.beneficio);
      printf("\tDestino en Malvinas: %s\n", aux->info.destino);
      printf("\tFuncion: %s\n", aux->info.funcion);
      printf("\tGrado militar: %s\n", aux->info.grado);
      printf("\tSecuelas de la guerra: %s\n", aux->info.secuelas);
      if (aux->info.VF == 0) {
        aux->info.edadAlFallecer = calcEdadFallecimiento(aux->info.nacimiento, aux->info.fallecimiento);
        printf("\tFecha de fallecimiento: %02d-%02d-%d\n", aux->info.fallecimiento.dia, aux->info.fallecimiento.mes, aux->info.fallecimiento.anio);
        printf("\tEdad al fallecer: %d\n", aux->info.edadAlFallecer);
      } else {
        aux->info.edad = calcEdad(aux->info.nacimiento);
        printf("\tEdad:%d\n", aux->info.edad);
      };
      aux = aux->next;
    };
  };
};

void mostrarLSEFallecidos(struct TNodoS *cab) {
  // accion que muestra los campos requeridos en la consigna de cada persona registrada como fallecida recorriendo la LSE
  struct TNodoS *aux;

  aux = cab->next;

  if (aux == NULL) {
    printf("\n\tLista vacia.\n");
  } else {
    printf("\n\n=================================== Los fallecidos son ====================================\n\n");
    while (aux != NULL) {
      printf("\n*\tNombre: %s \n", aux->info.nombre);
      printf("\n\tApellido: %s \n", aux->info.apellido);
      printf("\n\tDNI: %d \n", aux->info.DNI);
      printf("\n\tFecha de nacimiento: %02d-%02d-%d\n", aux->info.nacimiento.dia, aux->info.nacimiento.mes, aux->info.nacimiento.anio);
      printf("\n\tCiudad de residencia actual: %s \n\n", aux->info.ciudad);
      aux = aux->next;
    };
    printf("\n\n==========================================================================================\n\n");
  };
};

void mostrarMjeModif() {
  // accion meramente informativa
  char mjeModif[1000];

  strcpy(mjeModif, "\n\n=============================== Por favor, elija una opcion ===============================\n\n\t1. Modificar nombre.\n\t2. Modificar apellido.\n\t3. Modificar fecha de nacimiento.\n\t4. Modificar ciudad de residencia actual.\n\t5. Modificar ciudad de residencia en el momento de la guerra.  \n\t6. Modificar domicilio.\n\t7. Modificar correo electronico.\n\t8. Modificar telefono.\n\t9. Modificar fecha de fallecimiento.\n\t10. Modificar numero de beneficio nacional.\n\t11. Modificar codigo postal.\n\t12. Modificar provincia donde nacio.\n\t13. Modificar fuerza a la que pertenecio.\n\t14. Modificar destino en Malvinas.\n\t15. Modificar funcion en Malvinas.\n\t16. Modificar grado.\n\t17. Modificar secuelas.\n\t18. Indicar que la persona no ha fallecido. \n\n============================================================================================");
  printf("%s", mjeModif);
};

void mostrarPersona(int ind, struct TData arr) {
  // accion que muestra todos los campos de una persona segun el indice que ocupa en un arreglo

  printf("\n\n*\tDNI: %d\n", arr.a[ind].DNI);
  printf("\tNombre: %s\n", arr.a[ind].nombre);
  printf("\tApellido: %s\n", arr.a[ind].apellido);
  printf("\tFecha de nacimiento: %02d-%02d-%d\n", arr.a[ind].nacimiento.dia, arr.a[ind].nacimiento.mes, arr.a[ind].nacimiento.anio);
  printf("\tCiudad de residencia actual: %s\n", arr.a[ind].ciudad);
  printf("\tCiudad de residencia durante la guerra: %s\n", arr.a[ind].ciudadAntes);
  printf("\tDireccion Postal: %s\n", arr.a[ind].DP);
  printf("\tCorreo electronico: %s\n", arr.a[ind].CE);
  printf("\tTelefono: %s\n", arr.a[ind].tel);
  printf("\tNumero de beneficio: %s\n", arr.a[ind].beneficio);
  printf("\tCodigo Postal: %s\n", arr.a[ind].CP);
  printf("\tProvincia: %s\n", arr.a[ind].provincia);
  printf("\tFuerza a la que pertenecio durante la guerra: ");
  mostrarFuerza(arr.a[ind].fuerza);
  printf("\tDestino en Malvinas: %s\n", arr.a[ind].destino);
  printf("\tFuncion durante la guerra: %s\n", arr.a[ind].funcion);
  printf("\tGrado: %s\n", arr.a[ind].grado);
  printf("\tSecuelas: %s\n", arr.a[ind].secuelas);
  if (arr.a[ind].VF == 0) {
    arr.a[ind].edadAlFallecer = calcEdadFallecimiento(arr.a[ind].nacimiento, arr.a[ind].fallecimiento);
    printf("\tFecha de fallecimiento: %02d-%02d-%d\n", arr.a[ind].fallecimiento.dia, arr.a[ind].fallecimiento.mes, arr.a[ind].fallecimiento.anio);
    printf("\tEdad al fallecer: %d\n", arr.a[ind].edadAlFallecer);
  } else {
    arr.a[ind].edad = calcEdad(arr.a[ind].nacimiento);
    printf("\tEdad: %d\n\n", arr.a[ind].edad);
  };
};

void mostrarPorApellido(struct TData arr) {
  // esta accion pide un apellido al usuario y muestra persona a persona todos los que encuentra que compartan ese apellido

  char apellido[100];
  int i;

  printf("\n\n\tIngrese el apellido a buscar: ");
  chomp();
  scanf("%[^\n]", &apellido);

  i = 0;
  while ((strcmp(arr.a[i].apellido, apellido) != 0) && (i < arr.cant)) {
    i = i + 1;
  };
  if (i == arr.cant) {
    printf("\n\tApellido no encontrado.\n");
  } else {
    if (i < arr.cant) {
      while ((strcmp(arr.a[i].apellido, apellido) == 0) && (i <= arr.cant)) {
        mostrarPersona(i, arr);
        i = i + 1;
      };
    };
  };
};

void mostrarPorMes(struct TData arr) {
  // esta accion solo muestra algunos campos de la consigna para las personas que cumplen anios en un mismo mes.

  int i, edad;

  if (!estaVacio(arr)) {
    printf("\n\n================================= Cumpleanios de este mes =================================");
    for (i = 0; i < arr.cant; i++) {
      printf("\n\n*\tNombre: %s\n", arr.a[i].nombre);
      printf("\n\tApellido: %s\n", arr.a[i].apellido);
      printf("\n\tFecha de nacimiento: %02d-%02d-%d\n", arr.a[i].nacimiento.dia, arr.a[i].nacimiento.mes, arr.a[i].nacimiento.anio);
      edad = calcEdad(arr.a[i].nacimiento);
      printf("\n\tEdad: %d\n", edad);
      printf("\n\tCiudad de residencia: %s\n", arr.a[i].ciudad);
      printf("\n\tDireccion: %s\n", arr.a[i].DP);
    };
  } else {
    printf("\n==========================================================================================\n\n");
    printf("\n\tSin cumpleanios este mes\n\n");
  };
};

void obtenerDni(int *num) {
  // accion para almacenar el dni
  printf("\n\tIngrese el dni de la persona, por favor: ");
  scanf("%d", num);
};

void suprimirUlt(struct TData *arr) {
  // accion que busca optimizar el caso en que se quiera eliminar la persona en la ultima posicion de un arreglo

  if (estaVacio(*arr) == 0) {
    arr->cant = arr->cant - 1;
  } else {
    printf("\n\tLa lista esta vacia, no puede eliminar.\n");
  };
};