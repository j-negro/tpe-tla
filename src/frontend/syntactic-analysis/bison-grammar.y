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
%token RAISE_OCTAVE
%token LOWER_TONE
%token REMOVE
%token DURATION

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
	| variableName									{$$ = VariableNameExpressionGrammarAction($1);}
	| comparison									{$$ = ComparisonExpressionGrammarAction($1);}
	| expression AND expression						{$$ = BooleanAndExpressionGrammarAction($1, $3);}
	| expression OR expression						{$$ = BooleanOrExpressionGrammarAction($1, $3);}
	| NOT expression								{$$ = BooleanNotExpressionGrammarAction($2);}
	| OPEN_PARENTHESIS expression CLOSE_PARENTHESIS
	;

comparison: rythm EQUAL_EQUAL rythm 				{$$ = RythmEqualComparisonGrammarAction($1, $3 );}
	| rythm NOTEQUAL rythm							{$$ = RythmNotEqualComparisonGrammarAction($1, $3);}
	| tone EQUAL_EQUAL tone							{$$ = ToneEqualComparisonGrammarAction($1, $3);}
	| tone NOTEQUAL tone							{$$ = ToneNotEqualComparisonGrammarAction($1, $3);}
	| tone LOWER tone								{$$ = ToneLowerComparisonGrammarAction($1, $3);}
	| tone GREATER tone								{$$ = ToneGreaterComparisonGrammarAction($1, $3);}
	| tone LOWER_EQUAL tone							{$$ = ToneLowerEqualComparisonGrammarAction($1, $3);}
	| tone GREATER_EQUAL tone						{$$ = ToneGreaterEqualComparisonGrammarAction($1, $3);}
	| calculation EQUAL_EQUAL calculation			{$$ = CalculationEqualComparisonGrammarAction($1, $3);}
	| calculation NOTEQUAL calculation				{$$ = CalculationNotEqualComparisonGrammarAction($1, $3);}
	| calculation LOWER calculation					{$$ = CalculationLowerComparisonGrammarAction($1, $3);}
	| calculation GREATER calculation				{$$ = CalculationGreaterComparisonGrammarAction($1, $3);}
	| calculation LOWER_EQUAL calculation			{$$ = CalculationLowerEqualComparisonGrammarAction($1, $3);}
	| calculation GREATER_EQUAL calculation			{$$ = CalculationGreaterEqualComparisonGrammarAction($1, $3);}
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
	| variableName RAISE_OCTAVE
	| variableName LOWER_TONE
	| variableName REMOVE integer
	| variableName ADD variableName integer
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
	| variableName DURATION
	;

variableName: VARIABLE
	;

%%