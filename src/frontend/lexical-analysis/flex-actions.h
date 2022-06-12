#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"
#include "../syntactic-analysis/bison-parser.h"

/**
 * Se definen los diferentes IDs de cada token disponible para el scanner Flex.
 */

#define UNKNOWN 0
#define YYUNDEF 257

// TODO: esto ahora se saca porque lo define bison parece

//typedef enum TokenID {
//
//	// Por defecto, el valor "0" hace fallar el analizador sintáctico.
//	UNKNOWN = 0,
//
//	// Código de error de Bison, que permite abortar el escaneo de lexemas cuando
//	// se presente un patrón desconocido. El número "257" coincide con el valor
//	// que Bison le otorga por defecto, pero además permite que el resto de
//	// tokens continúen desde el valor "258" lo que permite proteger los IDs
//	// internos que Bison reserva para crear "tokens literales":
//	YYUNDEF = 257,
//
//	// Operadores aritméticos.
//	PLUS,
//	SUB,
//	MUL,
//	DIV,
//
//	// Operadores lógicos
//	AND,
//	OR,
//	NOT,
//	EQUAL,
//	EQUAL_EQUAL,
//	NOTEQUAL,
//	LOWER,
//	GREATER,
//	LOWER_EQUAL,
//	GREATER_EQUAL,
//
//	// Control de flujo
//	IF,
//	ELSE,
//	WHILE,
//	RETURN,
//
//	// Punctuación
//	SEMICOLON,
//	DOT,
//
//	// Paréntesis.
//	OPEN_PARENTHESIS,
//	CLOSE_PARENTHESIS,
//	OPEN_BRACKETS,
//	CLOSE_BRACKETS,
//
//	// Palabras reservadas
//	TONE,
//	TONE_DEF,
//	RYTHM,
//	RYTHM_DEF,
//	BPM,
//	ADD,
//	RAISE_OCTAVE,
//	LOWER_TONE,
//	REMOVE,
//	DURATION,
//
//	// Tipos de dato.
//	INTEGER_DEF,
//	INTEGER,
//	MELODY,
//	NOTE,
//	BOOLEAN_DEF,
//	BOOLEAN,
//	VARIABLE
//
//} TokenID;

/**
 * Se definen las acciones a ejecutar sobre cada patrón hallado mediante el
 * analizador léxico Flex. Este analizador solo puede identificar
 * construcciones regulares, ya que utiliza un autómata finito determinístico
 * (a.k.a. DFA), como mecanismo de escaneo y reconocimiento.
 */

token IntegerPatternAction(const char * lexeme);

void IgnoredPatternAction(const char * lexeme);

token UnknownPatternAction(const char * lexeme);

token TonePatternAction(const char * lexeme);

token RythmPatternAction(const char * lexeme);

token VariablePatternAction(const char * lexeme);

token PlusOperatorPatternAction(const char * lexeme);

token SubOperatorPatternAction(const char * lexeme);

token MulOperatorPatternAction(const char * lexeme);

token DivOperatorPatternAction(const char * lexeme);
#endif