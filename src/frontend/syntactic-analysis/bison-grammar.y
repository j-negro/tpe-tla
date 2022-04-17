%{

#include "bison-actions.h"

%}

// IDs de los tokens generados desde Flex:
// Operadores aritméticos.
%token ADD
%token SUB
%token MUL
%token DIV

// Operadores lógicos
%token AND
%token OR
%token NOT
%token EQUAL
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

// Tipos de dato.
%token INTEGER_DEF
%token INTEGER
%token MELODY
%token NOTE
%token BOOLEAN_DEF
%token BOOLEAN
%token VARIABLE

// Reglas de asociatividad y precedencia (de menor a mayor):
%left ADD SUB
%left MUL DIV

// TODO No estoy seguro si esta bien
%left AND OR
%left NOT

%%

program: code returnLine									{ ProgramGrammarAction($1); }
	;

returnLine: RETURN variableName SEMICOLON
	| RETURN musicTypeDefinition SEMICOLON
	;

code: line code
	| line
	;

line: typeDefinition SEMICOLON
	| assigment SEMICOLON
	| musicTypeDefinition SEMICOLON
	| musicAssigment SEMICOLON
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
	| expression AND expression
	| expression OR expression
	| NOT expression
	| OPEN_PARENTHESIS expression CLOSE_PARENTHESIS
	;

assigment: typeDefinition EQUAL value
	| variableName EQUAL value
	;

musicAssigment: musicTypeDefinition TONE_DEF TONE
	| musicTypeDefinition RYTHM_DEF RYTHM
	| musicTypeDefinition BPM INTEGER
	| variableName TONE_DEF TONE
	| variableName RYTHM_DEF RYTHM
	| variableName BPM INTEGER
	| musicAssigment TONE_DEF TONE
	| musicAssigment RYTHM_DEF RYTHM
	| musicAssigment BPM INTEGER
	;

typeDefinition: BOOLEAN_DEF variableName
	| INTEGER_DEF variableName
	;

musicTypeDefinition: MELODY variableName
	| NOTE variableName
	;

value: INTEGER
	| BOOLEAN
	;

variableName: VARIABLE
	;

%%