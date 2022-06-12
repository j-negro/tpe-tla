%{

#include "bison-actions.h"

%}

%union{
	// No terminales
	Program program;
	Block block;
	Sentence sentence;
	ReturnLine returnLine;
	WhileStatement whileStatement;
	IfStatement ifStatement;
	Expression expression;
	AddNote addNote;
	MusicAssignment musicAssignment;
	Assigment assignment;
	TypeDefinition typeDefinition;
	MusicTypeDefinition musicTypeDefinition;
	Getter getter;
	Constant constant;
	VariableName variableName;

	// Terminales
	token token;
	int integer;
	boolean boolean;
	tone tone;
	rythm rythm;
	char *string;
}

%type <variableName> variableName
%type <constant> constant
%type <getter> getter
%type <musicTypeDefinition> musicTypeDefinition
%type <typeDefinition> typeDefinition
%type <assignment> assignment
%type <musicAssignment> musicAssignment
%type <addNote> addNote
%type <expression> expression
%type <ifStatement> ifStatement
%type <whileStatement> whileStatement
%type <returnLine> returnLine
%type <sentence> sentence
%type <block> block
%type <program> program


 /* IDs de los tokens generados desde Flex:
 Operadores aritméticos. */
%token <token> PLUS
%token <token> SUB
%token <token> MUL
%token <token> DIV

 /* Operadores lógicos */
%token <token> AND
%token <token> OR
%token <token> NOT
%token <token> EQUAL
%token <token> EQUAL_EQUAL
%token <token> NOTEQUAL
%token <token> LOWER
%token <token> GREATER
%token <token> LOWER_EQUAL
%token <token> GREATER_EQUAL

 /* Control de flujo */
%token <token> IF
%token <token> ELSE
%token <token> WHILE
%token <token> RETURN
	
 /* Punctuación */
%token <token> SEMICOLON
%token <token> DOT

 /* Paréntesis */
%token <token> OPEN_PARENTHESIS
%token <token> CLOSE_PARENTHESIS

%token <token> OPEN_BRACKETS
%token <token> CLOSE_BRACKETS

 /* Palabras reservadas */
%token <tone> TONE
%token <token> TONE_DEF
%token <rythm> RYTHM
%token <token> RYTHM_DEF
%token <token> BPM
%token <token> ADD
%token <token> RAISE_OCTAVE
%token <token> LOWER_TONE
%token <token> REMOVE
%token <token> DURATION

 /* Tipos de dato. */
%token <token> INTEGER_DEF
%token <integer> INTEGER
%token <token> MELODY
%token <token> NOTE
%token <token> BOOLEAN_DEF
%token <boolean> BOOLEAN
%token <string> VARIABLE

 /* Reglas de asociatividad y precedencia (de menor a mayor): */
%left AND OR
%left LOWER LOWER_EQUAL GREATER GREATER_EQUAL EQUAL EQUAL_EQUAL NOTEQUAL
%left PLUS SUB
%left MUL DIV

%right NOT

%%

program: block	{ ProgramGrammarAction($1); }
	;
	
block: sentence block
	| %empty
	;

sentence: typeDefinition SEMICOLON			{$$ = SentenceTypeDefinitionGrammarAction($1);}
	| assignment SEMICOLON					{$$ = SentenceAssignmentGrammarAction($1);}
	| musicTypeDefinition SEMICOLON			{$$ = SentenceMusicTypeDefinitionGrammarAction($1);}
	| musicAssignment SEMICOLON				{$$ = SentenceMusicAssignmentDefinitionGrammarAction($1);}
	| addNote SEMICOLON						{$$ = SentenceAddNoteGrammarAction($1);}
	| ifStatement							{$$ = SentenceIfStatementGrammarAction($1);}
	| whileStatement						{$$ = SentenceWhileStatementGrammarAction($1);}
	| returnLine SEMICOLON					{$$ = SentenceReturnLineGrammarAction($1);}
	;

returnLine: RETURN variableName 
	| RETURN musicTypeDefinition
	;

ifStatement: IF OPEN_PARENTHESIS expression CLOSE_PARENTHESIS OPEN_BRACKETS block CLOSE_BRACKETS	 {$$ = ifStatementGrammarAction($3,$5);}
	| ifStatement ELSE OPEN_BRACKETS block CLOSE_BRACKETS											 {$$ = ifElseStatementGrammarAction($1,$4);}           
	;

whileStatement: WHILE OPEN_PARENTHESIS expression CLOSE_PARENTHESIS OPEN_BRACKETS block CLOSE_BRACKETS {$$ = WhileStatementGrammarAction($3,$5);}
	;

expression: expression AND expression						{$$ = BooleanAndExpressionGrammarAction($1, $3);}
	| expression OR expression						{$$ = BooleanOrExpressionGrammarAction($1, $3);}
	| NOT expression								{$$ = BooleanNotExpressionGrammarAction($2);}
	| expression PLUS expression					{$$ = PlusExpressionGrammarAction($1, $3);}
	| expression SUB expression						{$$ = SubExpressionGrammarAction($1, $3);}
	| expression MUL expression						{$$ = MulExpressionGrammarAction($1, $3);}
	| expression DIV expression						{$$ = DivExpressionGrammarAction($1, $3);}
	| expression EQUAL_EQUAL expression			{$$ = ExpressionEqualComparisonGrammarAction($1, $3);}
	| expression NOTEQUAL expression				{$$ = ExpressionNotEqualComparisonGrammarAction($1, $3);}
	| expression LOWER expression					{$$ = ExpressionLowerComparisonGrammarAction($1, $3);}
	| expression GREATER expression				{$$ = ExpressionGreaterComparisonGrammarAction($1, $3);}
	| expression LOWER_EQUAL expression			{$$ = ExpressionLowerEqualComparisonGrammarAction($1, $3);}
	| expression GREATER_EQUAL expression			{$$ = ExpressionGreaterEqualComparisonGrammarAction($1, $3);}
	| OPEN_PARENTHESIS expression CLOSE_PARENTHESIS
	| variableName
	| constant
	| getter
	;

addNote: variableName ADD variableName
	;

assignment: typeDefinition EQUAL expression  	{$$ = typeDefinitionAssignmentGrammarAction($1, $3)}
	| variableName EQUAL expression				{$$ = variableNameAssignmentGrammarAction($1, $3)}
	;

musicAssignment: musicTypeDefinition TONE_DEF TONE			{$$ = MusicTypeToneDefinitionGrammarAction($1);}
	| musicTypeDefinition RYTHM_DEF RYTHM					{$$ = MusicTypeRythmDefinitionGrammarAction($1);}
	| musicTypeDefinition BPM expression					{$$ = MusicTypeDefinitionGrammarAction($1);}
	| variableName TONE_DEF TONE							{$$ = VariableToneTypeDefinitionGrammarAction($1);}
	| variableName RYTHM_DEF RYTHM							{$$ = VariableRythmTypeDefinitionGrammarAction($1);}
	| variableName BPM expression							{$$ = VariableBpmTypeDefinitionGrammarAction($1, $3);}
	| musicAssignment TONE_DEF TONE							{$$ = MusicAssigmentToneDefinitionGrammarAction($1);}
	| musicAssignment RYTHM_DEF RYTHM						{$$ = MusicAssigmentRythmDefinitionGrammarAction($1);}
	| musicAssignment BPM expression						{$$ = MusicAssigmentBpmDefinitionGrammarAction($1, $3);}
	| variableName RAISE_OCTAVE								{$$ = VariableRaiseOctaveTypeDefinitionGrammarAction($1);}
	| variableName LOWER_TONE								{$$ = VariableLowerToneDefinitionGrammarAction($1);}
	| variableName REMOVE expression						{$$ = VariableRemoveIntegerDefinitionGrammarAction($1, $3);}
	| variableName ADD variableName expression				{$$ = VariableAdditionTypeDefinitionGrammarAction($1, $3, $4);}
	;

typeDefinition: BOOLEAN_DEF variableName
	| INTEGER_DEF variableName
	;

musicTypeDefinition: MELODY variableName
	| NOTE variableName
	;

constant: RYTHM												{$$ = RythmConstantGrammarAction($1);}
	| TONE													{$$ = ToneConstantGrammarAction($1);}
	| INTEGER												{$$ = IntegerConstantGrammarAction($1);}
	| BOOLEAN												{$$ = BooleanConstantGrammarAction($1);}
	;

getter: variableName DOT RYTHM_DEF
	| variableName DOT TONE_DEF
	| variableName DOT BPM
	| variableName DURATION
	;

variableName: VARIABLE
	;

%%