%{

#include "flex-actions.h"

%}

/* Obliga a crear una regla explícita para manejar lexemas desconocidos. */
%option nodefault

/* Escanea un único archivo y se detiene. */
%option noyywrap

/* Dispone una variable global "yylineno" con el número de línea actual. */
%option yylineno

/* Patrones reutilizables. */
crlf			\r\n
digit			[0-9]
endline			\n
whitespace		[ \f\n\r\t\v]
char            [a-zA-Z_]

%%

"{"                                         { return OPEN_BRACKETS; }
"}"                                         { return CLOSE_BRACKETS; }
"("											{ return OPEN_PARENTHESIS; }
")"											{ return CLOSE_PARENTHESIS; }

"."                                         { return DOT; }

"+"											{ return ADD; }
"-"											{ return SUB; }
"*"											{ return MUL; }
"/"										    { return DIV; }

"&"                                         { return AND; }
"!"                                         { return NOT; }
"="                                         { return EQUAL; }
"<"                                         { return LOWER; }
">"                                         { return GREATER; }
"<="                                        { return LOWER_EQUAL; }
">="                                        { return GREATER_EQUAL; }

";"                                         { return SEMICOLON; }

"if"                                        { return IF; }
"else"                                      { return ELSE; }
"while"                                     { return WHILE; }
"return"                                    { return RETURN;}    

"TONE"                                      { return TONE; }
"BPM"                                       { return BPM; }
"RYTHM"                                     { return RYTHM;}

"int"                                       { return INTEGER; }
"boolean"                                   { return BOOLEAN; }
"melody"                                    { return MELODY; }
"note"                                      { return NOTE; }

[A-G][2-6]                                  { return NotePatternAction(yytext); }

{char}+                                     { return VariablePatternAction(yytext) }

{digit}+									{ return IntegerPatternAction(yytext); }

{whitespace}								{ IgnoredPatternAction(yytext); }

.											{ return UnknownPatternAction(yytext); }

%%
