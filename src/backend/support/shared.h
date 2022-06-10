#ifndef SHARED_HEADER
#define SHARED_HEADER

#include <stdio.h>

// Descriptor del archivo de entrada que utiliza Bison.
extern FILE * yyin;

// Descriptor del archivo de salida que utiliza Bison.
extern FILE * yyout;

// Variable global que contiene el número escaneado.
extern int yylval;

// Variable global que contiene el número de la línea analizada.
extern int yylineno;

// Token actual en el tope de la pila del analizador Bison.
extern char * yytext;

// Función global de manejo de errores en Bison.
extern void yyerror(const char * string);

// Función global del analizador léxico Flex.
extern int yylex(void);

// Función global del analizador sintáctico Bison.
extern int yyparse(void);

// Emular tipo "boolean".
typedef enum {
	false = 0,
	true = 1
} boolean;

typedef struct {
	char *name;
	void *value;
	int type;
} t_variable;

typedef struct {
	void *value;
	int type;
} t_constant;

typedef struct {
	t_variable * variable;
	int type;
} t_getter;

typedef struct {
	t_variable *variable;
	int type;
} t_musicTypeDefinition;

typedef struct {
	t_variable *variable;
	int type;
} t_typeDefinition;

typedef struct {
	t_musicTypeDefinition * musicTypeDefinition;
	t_typeDefinition * typeDefinition;
	t_variable * variable;

	int defType;
	void *value;

	struct t_musicAssignment * musicAssignment;
} t_musicAssignment;

typedef struct {
	t_typeDefinition * typeDefinition;
	t_variable * variable;
	void *value;
	int type;

} t_assignment;

typedef struct {
	t_variable * variable1;
	t_variable * variable2;
} t_addNote;

typedef struct {
	t_variable * variable;
	t_constant * constant;
	t_getter * getter;

	int type;
	struct t_expression * expression1;
	struct t_expression * expression2;
} t_expression;

typedef struct t_ifStatement{
	t_expression * expression;
	t_block * block;
	struct t_ifStatement * ifStatement;
} t_ifStatement;

typedef struct t_whileStatement{
	t_expression * expression;
	t_block * block;
} t_whileStatement;

typedef struct t_sentence {
	t_typeDefinition * typeDefinition;
	t_musicTypeDefinition * musicTypeDefinition;
	t_assignment * assignment;
	t_musicAssignment * musicAssignment;
	t_addNote * addNote;
	t_ifStatement * ifStatement;
	t_whileStatement * whileStatement;
} t_sentence;

typedef struct t_code {
	t_sentence * sentence;
	t_code * code;
} t_code;

typedef struct t_block {
	t_code * code;
} t_block;


typedef struct t_returnLine{
	t_variable * variable;
	t_musicTypeDefinition * musicTypeDefinition;
} t_returnLine;

typedef struct t_program{
	t_sentence * sentence;
	t_program * program;
} t_program;

// Estado global de toda la aplicación.
typedef struct {

	// Indica si la compilación tuvo problemas hasta el momento:
	boolean succeed;

	// Indica el resultado de la compilación:
	int result;

	// Agregar una pila para almacenar tokens/nodos.
	// Agregar un nodo hacia la raíz del árbol de sintaxis abstracta.
	// Agregar una tabla de símbolos.
	// ...

} CompilerState;

// El estado se define e inicializa en el archivo "main.c":
extern CompilerState state;

#endif
