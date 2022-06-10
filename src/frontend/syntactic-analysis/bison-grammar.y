%{

#include "bison-actions.h"

%}
 %union{
 	t_variable * variable;
 	t_constant * constant;
 	t_getter * getter;
 	t_musicTypeDefinition * musicTypeDefinition;
 	t_typeDefinition * typeDefinition;
 	t_musicAssignment *musicAssignment;
 	t_assignment * assignment;
 	t_addNote * addNote;
 	t_expression * expression;
 	t_block * block;
 	t_code * code;
 	t_line * line;
 	t_ifStatement * ifStatement;
 	t_while * whileStatement;
 	t_returnLine * returnLine;
 	t_program * program;
 	char * string;
 	int integer;
 	double floatNumber;
 	boolean boolean;
 	int token;
 }%

 %type <variable> variableName
 %type <constant> constant
 %type <getter> getter
 %type <musicTypeDefinition> musicTypeDefinition
 %type <typeDefinition> typeDefinition
 %type <assignment> assignment
 %type <addNote> addNote
 %type <expression> expression
 %type <code> code
 %type <line> line
 %type <ifStatement> ifStatement
 %type <whileStatement> whileStatement
 %type <returnLine> returnLine
 %type <program> program


 /* IDs de los tokens generados desde Flex:
 Operadores aritméticos. */
%token  PLUS
%token  SUB
%token  MUL
%token  DIV

 /* Operadores lógicos */
%token  AND
%token  OR
%token  NOT
%token  EQUAL
%token  EQUAL_EQUAL
%token  NOTEQUAL
%token  LOWER
%token  GREATER
%token  LOWER_EQUAL
%token  GREATER_EQUAL

 /* Control de flujo */
%token  IF
%token  ELSE
%token  WHILE
%token  RETURN
	
 /* Punctuación */
%token  SEMICOLON
%token  DOT

 /* Paréntesis */
%token  OPEN_PARENTHESIS
%token  CLOSE_PARENTHESIS

%token  OPEN_BRACKETS
%token  CLOSE_BRACKETS

 /* Palabras reservadas */
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
%token COMMENT

 /* Tipos de dato. */
%token INTEGER_DEF
%token INTEGER
%token MELODY
%token NOTE
%token BOOLEAN_DEF
%token BOOLEAN
%token VARIABLE

 /* Reglas de asociatividad y precedencia (de menor a mayor): */
%left AND OR
%left LOWER LOWER_EQUAL GREATER GREATER_EQUAL EQUAL EQUAL_EQUAL NOTEQUAL
%left PLUS SUB
%left MUL DIV

%right NOT

%%

program: sentence program	{ ProgramGrammarAction($1); }
	| %empty						
	;

 returnLine: 
 	;

 code: %empty
 	| sentence code
 	;

block: OPEN_BRACKETS code CLOSE_BRACKETS
	;

sentence: typeDefinition SEMICOLON
	| assigment SEMICOLON
	| musicTypeDefinition SEMICOLON
	| musicAssigment SEMICOLON
	| addNote SEMICOLON
	| ifStatement
	| whileStatement
	| RETURN variableName SEMICOLON
	| RETURN musicTypeDefinition SEMICOLON
	| COMMENT
	;

ifStatement: IF OPEN_PARENTHESIS expression CLOSE_PARENTHESIS block	 {$$ = ifStatementGrammarAction($3,$5);}
	| ifStatement ELSE block                      
	;

whileStatement: WHILE OPEN_PARENTHESIS expression CLOSE_PARENTHESIS block  {$$ = WhileStatementGrammarAction($3,$5);}
	;

expression: expression AND expression						{$$ = BooleanAndExpressionGrammarAction($1, $3);}
	| expression OR expression						{$$ = BooleanOrExpressionGrammarAction($1, $3);}
	| NOT expression								{$$ = BooleanNotExpressionGrammarAction($2);}
	| expression PLUS expression
	| expression SUB expression
	| expression MUL expression
	| expression DIV expression
	| expression EQUAL_EQUAL expression			{$$ = CalculationEqualComparisonGrammarAction($1, $3);}
	| expression NOTEQUAL expression				{$$ = CalculationNotEqualComparisonGrammarAction($1, $3);}
	| expression LOWER expression					{$$ = CalculationLowerComparisonGrammarAction($1, $3);}
	| expression GREATER expression				{$$ = CalculationGreaterComparisonGrammarAction($1, $3);}
	| expression LOWER_EQUAL expression			{$$ = CalculationLowerEqualComparisonGrammarAction($1, $3);}
	| expression GREATER_EQUAL expression			{$$ = CalculationGreaterEqualComparisonGrammarAction($1, $3);}
	| OPEN_PARENTHESIS expression CLOSE_PARENTHESIS
	| variableName
	| constant
	| getter
	;

addNote: variableName ADD variableName
	;

assigment: typeDefinition EQUAL expression
	| variableName EQUAL expression
	;

musicAssigment: musicTypeDefinition TONE_DEF TONE			{$$ = MusicTypeToneDefinitionGrammarAction($1);}
	| musicTypeDefinition RYTHM_DEF RYTHM					{$$ = MusicTypeRythmDefinitionGrammarAction($1);}
	| musicTypeDefinition BPM expression					{$$ = MusicTypeDefinitionGrammarAction($1);}
	| variableName TONE_DEF TONE							{$$ = VariableToneTypeDefinitionGrammarAction($1);}
	| variableName RYTHM_DEF RYTHM							{$$ = VariableRythmTypeDefinitionGrammarAction($1);}
	| variableName BPM expression							{$$ = VariableBpmTypeDefinitionGrammarAction($1);}
	| musicAssigment TONE_DEF TONE							{$$ = MusicAssigmentToneDefinitionGrammarAction($1);}
	| musicAssigment RYTHM_DEF RYTHM						{$$ = MusicAssigmentRythmDefinitionGrammarAction($1);}
	| musicAssigment BPM expression							{$$ = MusicAssigmentBpmDefinitionGrammarAction($1);}
	| variableName RAISE_OCTAVE								{$$ = VariableRaiseOctaveTypeDefinitionGrammarAction($1);}
	| variableName LOWER_TONE								{$$ = VariableLowerToneDefinitionGrammarAction($1);}
	| variableName REMOVE expression						{$$ = VariableRemoveIntegerDefinitionGrammarAction($1);}
	| variableName ADD variableName expression				{$$ = VariableAdditionTypeDefinitionGrammarAction($1);}
	;

typeDefinition: BOOLEAN_DEF variableName
	| INTEGER_DEF variableName
	;

musicTypeDefinition: MELODY variableName
	| NOTE variableName
	;

constant: RYTHM
	| TONE
	| INTEGER
	| BOOLEAN
	;

getter: variableName DOT RYTHM_DEF
	| variableName DOT TONE_DEF
	| variableName DOT BPM
	| variableName DURATION
	;

variableName: VARIABLE
	;

%%