/*
 * PROGRAMA: Dont Angry This Kid
 * FICHERO: main.c
 * HISTORICO:
 *      v1.0 Creado el 17/07/2023
 *
 * DESCRIPCION:
 *      Este programa mide la disimilitud entre el codigo de dos directorios base
 *      cuanto mas difieran entre si mas enfadado estará el niño, así que procura
 *      que esto no pase.
 *
 *      MODO DE EMPLEO:
 *          1. Compilacion ---> $ make
 *          2. Ejecucion   ---> $ ./bin/main <dir1> <dir2>
 *      OPCIONES:
 *          Si solo hay dir1 lo comparará con un fichero de configuración llamado config.txt
 *              Si este fichero no existe en vez de comparar creará el fichero a partir del directorio
 *          Si se establecen los dos directorios el primero actuará como el directorio principal
 *              y el segundo como directorio a comparar.
 **/

#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include "CodeComparator.h"

#define FICHERO_CONFIGURACION "config.txt"

int main(int argc, char** argv){

    CodeComparator comparator;

    newCodeComparator(&comparator);

    if (argc < 2) {
        printf("No se ha introducido ningun directorio. Modo de empleo del programa:\n$ programa <dir1> <dir2>\n");
        return 0;
    }
    else if (argc < 3) {
        if(access(FICHERO_CONFIGURACION, F_OK) == 0) {
            addConfig(&comparator, (char*)FICHERO_CONFIGURACION);
            compare(&comparator, argv[1]);
        }
        else {
            createConfig(&comparator, (char*)FICHERO_CONFIGURACION, argv[1]);
        }
    }
    else {
        createConfig(&comparator, (char*)FICHERO_CONFIGURACION, argv[1]);
        addConfig(&comparator, (char*)FICHERO_CONFIGURACION);
        compare(&comparator, argv[2]);
    }

    printf("CONFIG: %s\n",comparator.ficheroConfig);
    printf("directorio: %s\n",comparator.directorio);
    printf("diferencia: %d\n",comparator.diferencia);
    printf("ficheros: %d\n",comparator.totalFicheros);
    printf("indice de cambios: %.2f%%\n",((double)comparator.diferencia/comparator.totalFicheros)*100);

    return 0;
}
