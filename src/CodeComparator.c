/*
 * MODULO: CodeComparator
 * FICHERO: CodeComparator.c
 * HISTORICO:
 *      v1.0 Creado el 17/07/2023 por David Canales
 *
 * DESCRIPCION:
 *      Este modulo proporciona la capacidad de comparar el codigo en dos directorios
 *      diferentes creando un fichero de descripcion del directorio base
 **/

#include "CodeComparator.h"

void saveDirectory(CodeComparator *comparator, char *directorio);
void directoryMap(char *directoryName, void(*handler)(char*,char*,void*), void *args);
void createConfigMap(char *ruta, char *name, void *args);
void areDifferentMap(char *ruta, char *name, void *args);
int calcularMD5Archivo(const char *rutaArchivo, char *md5Hash);
char *MD5ToString(unsigned char *md5Hash);
int isFile(char *directory);
int isSubdirectory(char *directory, char *subdirectory);

void newCodeComparator(CodeComparator *comparator) {
    comparator->ficheroConfig = malloc(sizeof(char) * MAX_FILE_PATH_LENGTH);
    comparator->directorio = malloc(sizeof(char) * MAX_FILE_PATH_LENGTH);

    strcpy(comparator->ficheroConfig, "");
    strcpy(comparator->directorio, "");
    comparator->diferencia = -1;
    comparator->totalFicheros = -1;
}

void createConfig(CodeComparator *comparator, char *ficheroConfig, char *directorio) {
    strcpy(comparator->ficheroConfig, ficheroConfig);

    FILE *f = fopen(ficheroConfig, "w");
    fprintf(f, "");
    fclose(f);

    saveDirectory(comparator, directorio);
    directoryMap(comparator->directorio, createConfigMap, (void*)(comparator->ficheroConfig));
}

void addConfig(CodeComparator *comparator, char *ficheroConfig) {
    strcpy(comparator->ficheroConfig, ficheroConfig);
}

void compare(CodeComparator *comparator, char *directorio) {
    saveDirectory(comparator, directorio);

    int MAX_LINE_LENGTH = 1024;
    char line[MAX_LINE_LENGTH];
    char nombre[1024], old_md5[50];
    char new_md5[50];

    FILE *file = fopen(comparator->ficheroConfig, "r");
    if (file == NULL) {
        return;
    }

    comparator->diferencia = 0;
    comparator->totalFicheros = 0;

    while (fgets(line, MAX_LINE_LENGTH, file) != NULL) {
        unsigned char md5Hash[MD5_DIGEST_LENGTH];
        strcpy(nombre, strtok(line, " "));
        strcpy(old_md5, strtok(NULL, " "));
        old_md5[strcspn(old_md5, "\n")] = '\0';

        calcularMD5Archivo(nombre, md5Hash);
        strcpy(new_md5,MD5ToString(md5Hash));
        if(strcmp(old_md5, new_md5) != 0 || !isSubdirectory(nombre, comparator->directorio)) {
            comparator->diferencia += 1;
        }
        comparator->totalFicheros += 1;
    }

    fclose(file);
}

int getDifference(CodeComparator comparator) {
    return comparator.diferencia;
}

void saveDirectory(CodeComparator *comparator, char *directorio) {
    if (isSubdirectory(directorio, "/") || isSubdirectory(directorio, "./") || strcmp(directorio, ".") == 0) {
        strcpy(comparator->directorio, directorio);
    }
    else {
        strcpy(comparator->directorio, "./");
        strcat(comparator->directorio, directorio);
    }
}

int calcularMD5Archivo(const char *rutaArchivo, char *md5Hash) {
    int READ_BUFFER_SIZE = 1024;
    FILE *file;
    char buffer[READ_BUFFER_SIZE];
    MD5_CTX md5Context;
    int bytesRead;

    file = fopen(rutaArchivo, "rb");
    if (file == NULL) {
        return 0;
    }

    MD5_Init(&md5Context);

    while ((bytesRead = fread(buffer, 1, READ_BUFFER_SIZE, file)) > 0) {
        MD5_Update(&md5Context, buffer, bytesRead);
    }

    MD5_Final(md5Hash, &md5Context);

    fclose(file);

    return 1;
}

char *MD5ToString(unsigned char *md5Hash) {
    char *md5 = malloc(sizeof(char) * 50);

    strcpy(md5, "");

    for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
        char c[3];
        c[2] = '\0';
        sprintf(c, "%02x", md5Hash[i]);
        strcat(md5, c);
    }

    md5[strcspn(md5, "\n")] = '\0';
    strcat(md5, "\0");

    return md5;
}

void directoryMap(char *directoryName, void(*handler)(char*, char*, void*), void *args) {
    DIR *directory;
    struct dirent *entry;

    // Abre el directorio
    directory = opendir(directoryName);
    if (directory == NULL) {
        return;
    }

    // Lee los ficheros del directorio
    while ((entry = readdir(directory)) != NULL) {
        char ruta[1024] = "";
        strcat(ruta, directoryName);
        handler(directoryName, entry->d_name, args);
    }

    // Cierra el directorio
    closedir(directory);
}

void createConfigMap(char *ruta, char *name, void *args) {
    if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) return;

    FILE *f = fopen((char*)args, "a");
    unsigned char md5Hash[MD5_DIGEST_LENGTH];
    char rutaCompleta[1024] = "";
    strcat(rutaCompleta, ruta);
    strcat(rutaCompleta, "/");
    strcat(rutaCompleta, name);

    if(isFile(rutaCompleta)) {
        calcularMD5Archivo(rutaCompleta, md5Hash);
        fprintf(f, "%s %s\n", rutaCompleta, MD5ToString(md5Hash));
    }
    else {
        directoryMap(rutaCompleta, createConfigMap, args);
    }

    fclose(f);
}

int isFile(char *directory) {
    struct stat st;

    if (stat(directory, &st) == 0) {
       if (S_ISREG(st.st_mode)) {
           return 1;
       }
    }

   return 0;
}

int isSubdirectory(char *directory, char *subdirectory) {
    return strncmp(directory, subdirectory, strlen(subdirectory)) == 0;
}
