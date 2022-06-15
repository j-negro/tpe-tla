#include "backend/code-generation/generator.h"
#include "backend/support/logger.h"
#include "backend/support/shared.h"
#include "frontend/syntactic-analysis/bison-parser.h"
#include <stdio.h>
#include "backend/domain-specific/semantic-analysis.h"

//Estado de la aplicación.
CompilerState state;

// Punto de entrada principal del compilador.
const int main(const int argumentCount, const char ** arguments) {
	// Inicializar estado de la aplicación.
	state.result = 0;
    state.program = NULL;
	state.succeed = false;

	// Mostrar parámetros recibidos por consola.
	for (int i = 0; i < argumentCount; ++i) {
		LogInfo("Argumento %d: '%s'", i, arguments[i]);
	}

	// Compilar el programa de entrada.
	LogInfo("Compilando...\n");
	const int result = yyparse();
	switch (result) {
		case 0:
			if (state.succeed) {
				LogInfo("El analisis sintactico fue exitoso.");
                if (validate_semantics(state.program)) {
                    LogInfo("El analisis semantico fue exitoso.");
                    LogInfo("La compilacion fue exitosa.");
    				Generator(state.program);
                } else {
                    LogError("Se produjo un error en el analisis semantico.");
                    return -1;
                }
			}
			else {
				LogError("Se produjo un error en el analisis sintactico.");
				return -1;
			}
			break;
		case 1:
			LogError("Bison finalizo debido a un error de sintaxis.");
			break;
		case 2:
			LogError("Bison finalizo abruptamente debido a que ya no hay memoria disponible.");
			break;
		default:
			LogError("Error desconocido mientras se ejecutaba el analizador Bison (codigo %d).", result);
	}
	LogInfo("Fin.");
	return result;
}