# TPE Teoría de lenguajes y autómatas

## Autoría
+ Gonzalo Rossin - 60135
+ Alberto Abancens - 62581
+ Mauro Daniel Sambartolomeo - 61279
+ Juan Negro - 61225


## Requerimientos
Para construir el compilador, se requieren de las siguientes dependencias:

- _Bison_ v3.8.2
- _Cmake_ v3.22.2
- _flex_ v2.6.4
- _GCC_ V11.1.0
- _Make_ v4.3
- _Maven_ (cualquier version)
- _Java_ v1.8

Es importante que la version de _Java_ sea 1.8, ya que es necesario poder utilizar _JavaX_ para reproducir
los sonidos resultantes. Luego, si no se compila usando _Java_ 1.8, no se podrá correr el programa
final.

## Construcción

Para construir el proyecto por completo, ejecute en la raíz del repositorio el siguiente comando:

```sh
user@machine:path/ $ cmake -S . -B bin
user@machine:path/ $ cd bin
user@machine:path/ $ make 
```
En un entorno _Microsoft Windows_, en lugar de ejecutar el comando `make`, se deberá abrir la solución generada `bin/Compiler.sln` con el IDE Microsoft Visual Studio 2022. Los ejecutables que este sistema construye se depositan dentro del directorio `bin/Debug` y `bin/Release` según corresponda.

## Ejecución

El resultado de la compilación de un programa de nuestro lenguaje es un **Proyecto _Maven_** que incluye las dependencias
necesarias para poder correr el programa. Estas son la dependencia _JFugue_ y la librería nuestra para el lenguaje. 

Para poder compilar programas en nuestro lenguaje y poder ejecutarlos, se provee un archivo llamado
`compile.sh`, que toma los siguientes parámetros **en orden**:
1. El nombre del archivo a compilar.
2. El _path_ donde se quiera copiar el directorio resultante.
   
Luego, si se quiere ejecutar el programa, se debe entrar al proyecto resultante y ejecutar los siguientes comandos:
1. `mvn clean package`
2. `java -jar target/TLA-Compiler-jar-with-dependencies.jar`

Es importante recordar que si no se corren estos archivos con _Java_ 1.8, entonces el programa fallará.



