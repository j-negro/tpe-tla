#ifndef FLEX_ACTIONS_HEADER
#define FLEX_ACTIONS_HEADER

#include "../../backend/support/shared.h"

/**
 * Se definen los diferentes IDs de cada token disponible para el scanner Flex.
 */
typedef enum TokenID {

	// Por defecto, el valor "0" hace fallar el analizador sintáctico.
	UNKNOWN = 0,

	// Código de error de Bison, que permite abortar el escaneo de lexemas cuando
	// se presente un patrón desconocido. El número "257" coincide con el valor
	// que Bison le otorga por defecto, pero además permite que el resto de
	// tokens continúen desde el valor "258" lo que permite proteger los IDs
	// internos que Bison reserva para crear "tokens literales":
	YYUNDEF = 257,

	// Operadores aritméticos.
	ADD,
	SUB,
	MUL,
	DIV,

	// Operadores lógicos
	AND,
	OR,
	NOT,
	EQUAL,
	LOWER,
	GREATER,
	LOWER_EQUAL,
	GREATER_EQUAL,

	// Control de flujo
	IF,
	ELSE,
	WHILE,
	RETURN,
	
	// Punctuación
	SEMICOLON,
	DOT,

	// Paréntesis.
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	OPEN_BRACKETS,
	CLOSE_BRACKETS,

	// Palabras reservadas
	TONE,
	TONE_DEF,
	RYTHM,
	RYTHM_DEF,
	BPM,

	// Tipos de dato.
	INTEGER_DEF,
	INTEGER,
	MELODY,
	NOTE,
	BOOLEAN_DEF,
	BOOLEAN,
	VARIABLE

} TokenID;

/**
 * Se definen las acciones a ejecutar sobre cada patrón hallado mediante el
 * analizador léxico Flex. Este analizador solo puede identificar
 * construcciones regulares, ya que utiliza un autómata finito determinístico
 * (a.k.a. DFA), como mecanismo de escaneo y reconocimiento.
 */

TokenID IntegerPatternAction(const char * lexeme);

void IgnoredPatternAction(const char * lexeme);

TokenID UnknownPatternAction(const char * lexeme);

TokenID TonePatternAction(const char * lexeme);

TokenID RythmPatternAction(const char * lexeme);

TokenID VariablePatternAction(const char * lexeme);

#endif