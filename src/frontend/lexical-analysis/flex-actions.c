#include "../../backend/support/logger.h"
#include "flex-actions.h"
#include <stdlib.h>

/**
 * Implementación de "flex-rules.h".
 */

TokenID IntegerPatternAction(const char * lexeme) {
	LogDebug("IntegerPatternAction: '%s'.", lexeme);
	yylval = atoi(lexeme);
	return INTEGER;
}


TokenID NotePatternAction(const char * lexeme) {
	LogDebug("NotePatternAction: '%s'.", lexeme);
	// yylval = atoi(lexeme);
	return NOTE;
}

void IgnoredPatternAction(const char * lexeme) {
	LogDebug("IgnoredPatternAction: '%s'.", lexeme);
}

TokenID UnknownPatternAction(const char * lexeme) {
	LogDebug("UnknownPatternAction: '%s'.", lexeme);
	return YYUNDEF;
}

TokenID VariablePatternAction(const char * lexeme) {
	LogDebug("VariablePatternAction: '%s'.", lexeme);
	return VARIABLE;
}
