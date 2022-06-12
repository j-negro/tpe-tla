#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>

/**
 * Implementación de "flex-rules.h".
 */

token IntegerPatternAction(const char * lexeme) {
	LogDebug("IntegerPatternAction: '%s'.", lexeme);
    //yylval.integer = atoi(lexeme);
	return INTEGER;
}


token TonePatternAction(const char * lexeme) {
	LogDebug("TonePatternAction: '%s'.", lexeme);
	// yylval = atoi(lexeme);
	return TONE;
}

token RythmPatternAction(const char * lexeme) {
	LogDebug("RythmPatternAction: '%s'.", lexeme);
	// yylval = atoi(lexeme);
	return RYTHM;
}

void IgnoredPatternAction(const char * lexeme) {
	// LogDebug("IgnoredPatternAction: '%s'.", lexeme);
}

token UnknownPatternAction(const char * lexeme) {
	LogDebug("UnknownPatternAction: '%s'.", lexeme);
	return YYUNDEF;
}

token VariablePatternAction(const char * lexeme) {
	LogDebug("VariablePatternAction: '%s'.", lexeme);
	return VARIABLE;
}

token PlusOperatorPatternAction(const char * lexeme){
	LogDebug("PlusOperatorPatternAction: '%s'.", lexeme);
	//yylval.token = PLUS;
	return PLUS;
}

token SubOperatorPatternAction(const char * lexeme){
	LogDebug("SubOperatorPatternAction: '%s'.", lexeme);
	//yylval.token = SUB;
	return SUB;
}

token MulOperatorPatternAction(const char * lexeme){
	LogDebug("MulOperatorPatternAction: '%s'.", lexeme);
	//yylval.token = MUL;
	return MUL;
}
