#ifndef BISON_ACTIONS_HEADER
#define BISON_ACTIONS_HEADER

#include "../../backend/support/shared.h"

/**
 * Se definen las acciones a ejecutar sobre cada regla de producción de la
 * gramática. El objetivo de cada acción debe ser el de construir el nodo
 * adecuado que almacene la información requerida en el árbol de sintaxis
 * abstracta (i.e., el AST).
 */

// Programa.
int ProgramGrammarAction(const int value);

// Expresión.
int AdditionExpressionGrammarAction(const int leftValue, const int rightValue);
int SubtractionExpressionGrammarAction(const int leftValue, const int rightValue);
int MultiplicationExpressionGrammarAction(const int leftValue, const int rightValue);
int DivisionExpressionGrammarAction(const int leftValue, const int rightValue);
int FactorExpressionGrammarAction(const int value);

//Statements
int ifStatementGrammarAction(const int leftValue,const int rightValue);
int WhileStatementGrammarAction(const int leftValue,const int rightValue);

//Expresion booleana
int VariableNameExpressionGrammarAction(const int value);
int ComparisonExpressionGrammarAction(const int value);
int BooleanAndExpressionGrammarAction(const int leftValue,const int rightValue);
int BooleanOrExpressionGrammarAction(const int leftValue,const int rightValue);
int BooleanNotExpressionGrammarAction(const int value);

//Comparacion
int RythmEqualComparisonGrammarAction(const int leftValue, const int rightValue );
int RythmNotEqualComparisonGrammarAction(const int leftValue, const int rightValue);
int ToneEqualComparisonGrammarAction(const int leftValue, const int rightValue);
int ToneNotEqualComparisonGrammarAction(const int leftValue, const int rightValue);
int ToneLowerComparisonGrammarAction(const int leftValue, const int rightValue);
int ToneGreaterComparisonGrammarAction(const int leftValue, const int rightValue);
int ToneLowerEqualComparisonGrammarAction(const int leftValue, const int rightValue);
int ToneGreaterEqualComparisonGrammarAction(const int leftValue, const int rightValue);
int CalculationEqualComparisonGrammarAction(const int leftValue, const int rightValue);
int CalculationNotEqualComparisonGrammarAction(const int leftValue, const int rightValue);
int CalculationLowerComparisonGrammarAction(const int leftValue, const int rightValue);
int CalculationGreaterComparisonGrammarAction(const int leftValue, const int rightValue);
int CalculationGreaterEqualComparisonGrammarAction(const int leftValue, const int rightValue);
int CalculationLowerEqualComparisonGrammarAction(const int leftValue, const int rightValue);

//MusicAssignment
int MusicTypeToneDefinitionGrammarAction(const int value);
int MusicTypeRythmDefinitionGrammarAction(const int value);
int MusicTypeDefinitionGrammarAction(const int value);
int VariableToneTypeDefinitionGrammarAction(const int value);
int VariableRythmTypeDefinitionGrammarAction(const int value);
int VariableBpmTypeDefinitionGrammarAction(const int value);
int MusicAssigmentToneDefinitionGrammarAction(const int value);
int MusicAssigmentRythmDefinitionGrammarAction(const int value);
int MusicAssigmentBpmDefinitionGrammarAction(const int value);
int VariableRaiseOctaveTypeDefinitionGrammarAction(const int value);
int VariableLowerToneDefinitionGrammarAction(const int value);
int VariableRemoveIntegerDefinitionGrammarAction(const int value);
int VariableAdditionTypeDefinitionGrammarAction(const int value);

// Factores.
int ExpressionFactorGrammarAction(const int value);
int ConstantFactorGrammarAction(const int value);
int VariableFactorGrammarAction(const int value);

// Constantes.
int IntegerConstantGrammarAction(const int value);

// Variables.
int NoteVariableGrammarAction(const int value);

#endif