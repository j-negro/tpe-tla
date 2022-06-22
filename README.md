# TPE Teoría de lenguajes y automatas

## Requerimientos
para construir el compilador se requieren de las siguientes dependencias:

- Bison v3.8.2
- Cmake v3.22.2
- flex v2.6.4
- GCC V11.1.0
- Make v4.3
- Maven (cualquier version)
- Java v1.8

Es importante que la version de java sea 1.8 ya que es necesario poder utilizar JavaX para obtener el ejecutable de audio.

## Construccion

Para construir el proyecto por completo, ejecute en la raíz del repositorio el siguiente comando:

```sh
user@machine:path/ $ cmake -S . -B bin
user@machine:path/ $ cd bin
user@machine:path/ $ make 
```
En un entorno Microsoft Windows, en lugar de ejecutar el comando `make`, se deberá abrir la solución generada `bin/Compiler.sln` con el IDE Microsoft Visual Studio 2022. Los ejecutables que este sistema construye se depositan dentro del directorio `bin/Debug` y `bin/Release` según corresponda.

## Ejecución

Para poder compilar programas en nuestro lenguaje y poder ejecutarlos, se provee un archivo llamado 




