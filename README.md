# Dont Angry This Kid
Seguro que te has encontrado con el típico programador al que no le gusta que toquen
su código.

Cada vez que te toca modificar algo tienes miedo de que al commitear lea los cambios
y vea que su codigo no esta igual que cuando el lo subió.

Este programa permite saber cuantos ficheros han cambiado desde que te bajaste el código
de esta persona hasta que decides darle al botón de `push` y así saber cuan probable
es que se de cuenta de tus chapuzas.

## Instalación
1. Descargar el codigo fuente.
2. Abrir la terminal linux y ejecutar el siguiente comando
```bash
make all
```    
Ahora ya tienes el programa compilado dentro de la carpeta bin con el nombre de `main`.
Para usarlo lo puedes mover al directorio que tu quieras y usarlo como se indica
en la próxima sección.

## USO
El modo de uso del programa es mediante el comando:
```bash
./main <dir1> <dir2>
```
donde se pueden dar 4 opciones:
- No se introduce ninguno de los dos directorios

<ul><li style="list-style:none;">Solución: Se imprime un mensaje de funcionamiento
del programa.</li></ul>

- Se introduce unicamente el primer directorio pero existe un fichero de configuración

<ul><li style="list-style:none;">Solución: Se recoge la configuracion del fichero
y se compara con el directorio.</li></ul>

- Se introduce unicamente el primer directorio pero no existe un fichero de
configuración

<ul><li style="list-style:none;">Solución: Se crea un fichero de configuración a
partir del directorio.</li></ul>

- Se introducen los dos directorios

<ul><li style="list-style:none;">Solución: Se crea un fichero de configuración a
partir del primer directorio y se compara con el segundo directorio.</li></ul>

Cuando termina la ejecucion aparece la siguiente pantalla:
```
usuario@ordenador:/ruta$ ./main src src
CONFIG: config.txt
directorio: ./src
diferencia: 0
ficheros: 3
indice de cambios: 0.00%
```
A mas indice de cambios mas enfadado estará el niño, así que procura que no se
cabree.
