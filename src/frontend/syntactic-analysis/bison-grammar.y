%{

#include "bison-actions.h"

%}

// IDs de los tokens generados desde Flex:
// Operadores aritméticos.
%token PLUS
%token SUB
%token MUL
%token DIV

// Operadores lógicos
%token AND
%token OR
%token NOT
%token EQUAL
%token EQUAL_EQUAL
%token NOTEQUAL
%token LOWER
%token GREATER
%token LOWER_EQUAL
%token GREATER_EQUAL

// Control de flujo
%token IF
%token ELSE
%token WHILE
%token RETURN
	
// Punctuación
%token SEMICOLON
%token DOT

// Paréntesis
%token OPEN_PARENTHESIS
%token CLOSE_PARENTHESIS

%token OPEN_BRACKETS
%token CLOSE_BRACKETS

// Palabras reservadas
%token TONE
%token TONE_DEF
%token RYTHM
%token RYTHM_DEF
%token BPM
%token ADD

// Tipos de dato.
%token INTEGER_DEF
%token INTEGER
%token MELODY
%token NOTE
%token BOOLEAN_DEF
%token BOOLEAN
%token VARIABLE

// Reglas de asociatividad y precedencia (de menor a mayor):
%left AND OR
%left NOT
%left LOWER LOWER_EQUAL GREATER GREATER_EQUAL EQUAL EQUAL_EQUAL NOTEQUAL
%left PLUS SUB
%left MUL DIV

%%

program: code returnLine									{ ProgramGrammarAction($1); }
	;

returnLine: RETURN variableName SEMICOLON
	| RETURN musicTypeDefinition SEMICOLON
	;

code: %empty
	| line code
	;

line: typeDefinition SEMICOLON
	| assigment SEMICOLON
	| musicTypeDefinition SEMICOLON
	| musicAssigment SEMICOLON
	| addNote SEMICOLON
	| ifStatement
	| whileStatement
	;

ifStatement: IF OPEN_PARENTHESIS expression CLOSE_PARENTHESIS block
	| ifStatement ELSE block
	;

whileStatement: WHILE OPEN_PARENTHESIS expression CLOSE_PARENTHESIS block
	;

block: OPEN_BRACKETS code CLOSE_BRACKETS
	;

expression: BOOLEAN
	| variableName
	| comparison
	| expression AND expression
	| expression OR expression
	| NOT expression
	| OPEN_PARENTHESIS expression CLOSE_PARENTHESIS
	;

comparison: rythm EQUAL_EQUAL rythm
	| rythm NOTEQUAL rythm
	| tone EQUAL_EQUAL tone
	| tone NOTEQUAL tone
	| tone LOWER tone
	| tone GREATER tone
	| tone LOWER_EQUAL tone
	| tone GREATER_EQUAL tone
	| calculation EQUAL_EQUAL calculation
	| calculation NOTEQUAL calculation
	| calculation LOWER calculation
	| calculation GREATER calculation
	| calculation LOWER_EQUAL calculation
	| calculation GREATER_EQUAL calculation
	;

// Backend chequea que las variables existan y sean la primera de tipo melody y la segunda de tipo note.
addNote: variableName ADD variableName
	;

// Esto tira un conflicto de reduce/reduce porque no tanto expression como calculation pueden ser un variableName, no se como solucionarlo.
assigment: BOOLEAN_DEF variableName EQUAL expression
	| INTEGER_DEF variableName EQUAL calculation
	| variableName EQUAL expression
	| variableName EQUAL calculation
	;

musicAssigment: musicTypeDefinition TONE_DEF TONE
	| musicTypeDefinition RYTHM_DEF RYTHM
	| musicTypeDefinition BPM calculation
	| variableName TONE_DEF TONE
	| variableName RYTHM_DEF RYTHM
	| variableName BPM calculation
	| musicAssigment TONE_DEF TONE
	| musicAssigment RYTHM_DEF RYTHM
	| musicAssigment BPM calculation
	;

typeDefinition: BOOLEAN_DEF variableName
	| INTEGER_DEF variableName
	;

musicTypeDefinition: MELODY variableName
	| NOTE variableName
	;

rythm: RYTHM
	| variableName DOT RYTHM_DEF
	;

tone: TONE
	| variableName DOT TONE_DEF
	;

calculation: calculation PLUS calculation
	| calculation SUB calculation
	| calculation MUL calculation
	| calculation DIV calculation
	| OPEN_PARENTHESIS calculation OPEN_PARENTHESIS
	| integer
	;

integer: INTEGER
	| variableName DOT BPM
	| variableName
	;

variableName: VARIABLE
	;

%%