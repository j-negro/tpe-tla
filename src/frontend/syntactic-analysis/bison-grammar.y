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
%token RYTHM
%token BPM

// Tipos de dato.
%token INTEGER,
%token MELODY,
%token NOTE,
%token BOOLEAN,
%token CONST

// Reglas de asociatividad y precedencia (de menor a mayor):
%left ADD SUB
%left MUL DIV

%%

program: block RETURN MELODY SEMICOLON											{ $$ = ProgramGrammarAction($1); }
	;

block: OPEN_BRACKETS block CLOSE_BRACKETS
	| OPEN_BRACKETS expression CLOSE_BRACKETS
	| 
	;
	
sentence: NOTE variable EQUAL expression SEMICOLON
	;

declaration: NOTE VARIABLE EQUAL 
	;
 

expression: expression ADD expression							{ $$ = AdditionExpressionGrammarAction($1, $3); }
	| expression SUB expression									{ $$ = SubtractionExpressionGrammarAction($1, $3); }
	| expression MUL expression									{ $$ = MultiplicationExpressionGrammarAction($1, $3); }
	| expression DIV expression									{ $$ = DivisionExpressionGrammarAction($1, $3); }
	| 
	| factor													{ $$ = FactorExpressionGrammarAction($1); }
	;


factor: OPEN_PARENTHESIS expression CLOSE_PARENTHESIS			{ $$ = ExpressionFactorGrammarAction($2); }
	| constant													{ $$ = ConstantFactorGrammarAction($1); }
	| variable													{ $$ = VariableFactorGrammarAction($1); }
	;

constant: INTEGER 												{ $$ = IntegerConstantGrammarAction($1); }
	| BOOLEAN
	| MELODY
	| NOTE

	;

variable: NOTE 													{ $$ = NoteVariableGrammarAction($1); }
	| MELODY
	;


%%
