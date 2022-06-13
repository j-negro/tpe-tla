#ifndef SHARED_HEADER
#define SHARED_HEADER

#include <stdio.h>

typedef struct Expression Expression;
typedef struct Block Block;

// Emular tipo "boolean".
typedef enum {
    false = 0,
    true = 1
} boolean;


#define MAX_TABLE 1024

typedef enum VariableType {
    VAR_INT,
    VAR_BOOL,
    VAR_MELODY,
    VAR_NOTE,
} VariableType;

typedef struct Symbol {
    char *name;
    VariableType type;
} Symbol;

typedef struct Table {
    int size;
    Symbol symbols[MAX_TABLE];
} Table;

typedef struct Stack {
    Table *array[MAX_TABLE];
    int current;
    int itemCount;
} Stack;

void init_stack(Stack *stack);
Table *peek(Stack *stack);
boolean push(Stack *stack);
boolean pop(Stack *stack);
void init_table(Table *table);
boolean add_symbol(Table *table, char *name, VariableType type);
VariableType find_symbol_in_stack(Stack *stack, char *name);

// Descriptor del archivo de entrada que utiliza Bison.
extern FILE * yyin;

// Descriptor del archivo de salida que utiliza Bison.
extern FILE * yyout;

// Variable global que contiene el número de la línea analizada.
extern int yylineno;

// extern int yylval;
// extern YYSTYPE yylval;

// Token actual en el tope de la pila del analizador Bison.
extern char * yytext;

// Función global de manejo de errores en Bison.
extern void yyerror(const char * string);

// Función global del analizador léxico Flex.
extern int yylex(void);

// Función global del analizador sintáctico Bison.
extern int yyparse(void);

typedef int token;

typedef enum {
	NORMAL,
	FLAT,
	SHARP
} NoteType;

typedef enum {
    EMPTY_BLOCK,
    FILLED_BLOCK
} BlockType;

typedef enum {
	C,
	D,
	E,
	F,
	G,
	A,
	B
} NoteName;

// Emular tipo TONE.
typedef struct {
	int octave;
	NoteName name;
	NoteType type;
} tone;

// Emular tipo RYTHM.
typedef enum rythm {
	WHOLE,
	HALF,
	QUARTER,
	EIGHTH,
	SIXTEENTH,
	THIRTYSECOND,
	SIXTYFOURTH
} rythm;

// Definiciones de nodos del arbol.

typedef struct {
	char *name;
} VariableName;

typedef enum {
	INTEGER_CONSTANT,
	RYTHM_CONSTANT,
	BOOLEAN_CONSTANT,
	TONE_CONSTANT
} ConstantType;

typedef union {
	int integer;
	rythm rythm;
	boolean boolean;
	tone tone;
} ConstantValue;


typedef struct {
	ConstantType type;
	ConstantValue value;
} Constant;

typedef enum {
	RYTHM_GETTER,
	TONE_GETTER,
	BPM_GETTER,
	DURATION_GETTER,
} GetterType;

typedef struct {
	GetterType type;
	VariableName *name;
} Getter;

typedef enum {
	MELODY_DEFINITION,
	NOTE_DEFINITION
} MusicTypeDefinitionType;

typedef struct {
	MusicTypeDefinitionType type;
	VariableName *name;
} MusicTypeDefinition;

typedef enum {
	BOOLEAN_DEFINITION,
	INTEGER_DEFINITION
} TypeDefinitionType;

typedef struct {
	TypeDefinitionType type;
	VariableName * name;
} TypeDefinition;

typedef enum {
	TYPE_DEFINITION_ASSIGNMENT,
	VARIABLE_NAME_ASSIGNMENT,
} AssignmentType;

typedef struct {
	AssignmentType type;

	// puntero que depende del type (typeDefinition o variableName)
	void * variable;

	Expression * expression;
} Assigment;

typedef enum {
	TYPE_DEFINITION_MUSIC_ASSIGNMENT,
	VARIABLE_NAME_MUSIC_ASSIGNMENT,
	ASSIGNMENT_MUSIC_ASSIGNMENT,
} MusicAssignmentVariableType;

typedef enum {
	TONE_ASSIGNMENT,
	RYTHM_ASSIGNMENT,
	BPM_ASSIGNMENT,
	RAISE_OCTAVE_ASSIGNMENT,
	LOWER_TONE_ASSIGNMENT,
	REMOVE_ASSIGNMENT,
	ADD_ASSIGNMENT, 
} MusicAssignmentType;

typedef union {
	tone tone;
	rythm rythm;
	Expression * bpm;
} MusicAssignmentValue;

typedef struct {
	MusicAssignmentVariableType type;
	// puntero que depende del type (musicTypeDefinition, variableName, musicAssignment)
	void * variable;
    void * variableRight;

	MusicAssignmentType musicAssignmentType;

	// depende del valor que queres guardar dependiendo del type (tone, rythm, bpm)
	MusicAssignmentValue value;
} MusicAssignment;

typedef struct {
	VariableName *melody;
	VariableName *note;
} AddNote;

typedef enum {
	AND_EXPRESSION,
	OR_EXPRESSION,
	NOT_EXPRESSION,
	PLUS_EXPRESSION,
	SUB_EXPRESSION,
	MUL_EXPRESSION,
	DIV_EXPRESSION,
	EQUAL_EQUAL_EXPRESSION,
	NOTEQUAL_EXPRESSION,
	LOWER_EXPRESSION,
	LOWER_EQUAL_EXPRESSION,
	GREATER_EXPRESSION,
	GREATER_EQUAL_EXPRESSION,
	PARENTHESIS_EXPRESSION,
	VARIABLE_EXPRESSION,
	CONSTANT_EXPRESSION,
	GETTER_EXPRESSION,
} ExpressionType;

struct Expression {
	ExpressionType type;
	struct Expression *expression1;
	struct Expression *expression2;
	// puede ser variableName constant o getter dependiendo del type
	void * value;
};

typedef enum {
	IF_TYPE,
	IF_ELSE_TYPE
} IfType;

typedef struct {
	IfType type;

	// puede ser una expresion o un ifStatement dependiendo del type
	void * expression;
	
	Block * block;
} IfStatement;

typedef struct {
	Expression * expression;
	Block * block;
} WhileStatement;

typedef enum {
	VARIABLE_NAME_RETURN,
	MUSIC_TYPE_DEFINITION_RETURN
} ReturnLineType;

typedef struct {
	ReturnLineType type;
	// puede ser variableName o musicTypeDefinition segun el type
	void * value;
} ReturnLine;

typedef enum {
	TYPE_DEFINITION_SENTENCE,
	ASSIGNMENT_SENTENCE,
	MUSIC_TYPE_DEFINITION_SENTENCE,
	MUSIC_ASSIGNMENT_SENTENCE,
	ADD_NOTE_SENTENCE,
	IF_STATEMENT_SENTENCE,
	WHILE_STATEMENT_SENTENCEM,
	RETURN_LINE_SENTENCE
} SentenceType;

typedef struct {
	SentenceType type;

	// puede ser typeDefinition, musicTypeDefinition, assignment, musicAssignment, addNote, ifStatement, whileStatement, returnLine
	void * sentence;
} Sentence;

struct Block {
	Sentence * sentence;
    BlockType type;
	struct Block * block;
};

typedef struct {
	Block * block;
} Program;

// Estado global de toda la aplicación.
typedef struct {

	// Indica si la compilación tuvo problemas hasta el momento:
	boolean succeed;

	// Indica el resultado de la compilación:
	int result;

	// Agregar una pila para almacenar tokens/nodos.
	// Nodo hacia la raíz del árbol de sintaxis abstracta.
	Program * program;

	// Agregar una tabla de símbolos.
	// ...

} CompilerState;

// El estado se define e inicializa en el archivo "main.c":
extern CompilerState state;

#endif
