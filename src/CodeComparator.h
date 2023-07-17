/*
 * MODULO: CodeComparator
 * FICHERO: CodeComparator.h
 * HISTORICO:
 *      v1.0 Creado el 17/07/2023 por David Canales
 *
 * DESCRIPCION:
 *      Este modulo proporciona la capacidad de comparar el codigo en dos directorios
 *      diferentes creando un fichero de descripcion del directorio base
 **/

#ifndef HHH_CODECOMPARATOR_DCP
#define HHH_CODECOMPARATOR_DCP

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <openssl/md5.h>

#define MAX_FILE_PATH_LENGTH 1024

typedef struct codeComparator {
    char *ficheroConfig;
    char *directorio;
    int diferencia;
    int totalFicheros;
} CodeComparator;

/*
 * ACCION: newCodeComparator
 * ENTRADA: Un comparador sin inicializar
 * MODIFICA: Inicializa el comparador
 */
void newCodeComparator(CodeComparator *comparator);

/*
 * ACCION: createConfig
 * ENTRADA: Un comparador, el nombre de un fichero de configuracion y un directorio
 * MODIFICA: Crea el fichero con la configuracion y lo almacena en el comparador
 */
void createConfig(CodeComparator *comparator, char *ficheroConfig, char *directorio);

/*
 * ACCION: addConfig
 * ENTRADA: Un comparador y el nombre de un fochero de configuracion
 * MODIFICA: Añade el fichero de configuracion al comparador
 */
void addConfig(CodeComparator *comparator, char *ficheroConfig);

/*
 * ACCION: compare
 * ENTRADA: Un comparador y un directorio
 * MODIFICA: Añade al comparador un indice de comparacion
 */
void compare(CodeComparator *comparator, char *directorio);

/*
 * FUNCION: getDifference
 * ENTRADA: Un comparador
 * SALIDA: Devuelve la diferencia de la comparacion de codigos
 */
int getDifference(CodeComparator comparator);

#endif
