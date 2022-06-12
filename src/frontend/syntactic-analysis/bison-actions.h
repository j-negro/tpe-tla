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
Expression* AdditionExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* SubtractionExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* MultiplicationExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* DivisionExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
int FactorExpressionGrammarAction(const int value);

//Statements
int ifStatementGrammarAction(const int leftValue,const int rightValue);
int WhileStatementGrammarAction(const int leftValue,const int rightValue);

//Expresion booleana
int VariableNameExpressionGrammarAction(const int value);
int ComparisonExpressionGrammarAction(const int value);
Expression* BooleanAndExpressionGrammarAction(Expression* leftValue,Expression* rightValue);
Expression* BooleanOrExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* BooleanNotExpressionGrammarAction(Expression* expression);

//Comparacion
int RythmEqualComparisonGrammarAction(const int leftValue, const int rightValue );
int RythmNotEqualComparisonGrammarAction(const int leftValue, const int rightValue);
int ToneEqualComparisonGrammarAction(const int leftValue, const int rightValue);
int ToneNotEqualComparisonGrammarAction(const int leftValue, const int rightValue);
int ToneLowerComparisonGrammarAction(const int leftValue, const int rightValue);
int ToneGreaterComparisonGrammarAction(const int leftValue, const int rightValue);
int ToneLowerEqualComparisonGrammarAction(const int leftValue, const int rightValue);
int ToneGreaterEqualComparisonGrammarAction(const int leftValue, const int rightValue);
Expression* ExpressionEqualComparisonGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* ExpressionNotEqualComparisonGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* ExpressionLowerComparisonGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* ExpressionGreaterComparisonGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* ExpressionGreaterEqualComparisonGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* ExpressionLowerEqualComparisonGrammarAction(Expression* leftValue, Expression* rightValue);

//Assignments
MusicAssignment* MusicTypeToneDefinitionGrammarAction(MusicTypeDefinition* value);
int MusicTypeRythmDefinitionGrammarAction(const int value);
int MusicTypeDefinitionGrammarAction(const int value);
int VariableToneTypeDefinitionGrammarAction(const int value);
int VariableRythmTypeDefinitionGrammarAction(const int value);
int VariableBpmTypeDefinitionGrammarAction(const int value);
int MusicAssigmentToneDefinitionGrammarAction(const int value);
int MusicAssigmentRythmDefinitionGrammarAction(const int value);
MusicAssignment* MusicAssigmentBpmDefinitionGrammarAction(MusicAssignment* leftValue,Expression* rightValue);
int VariableRaiseOctaveTypeDefinitionGrammarAction(const int value);
int VariableLowerToneDefinitionGrammarAction(const int value);
MusicAssignment* VariableRemoveIntegerDefinitionGrammarAction(VariableName* variableName, Expression* value);
int VariableAdditionTypeDefinitionGrammarAction(const int value);

Assigment* typeDefinitionAssignmentGrammarAction(TypeDefinition* leftValue, Expression* rightValue);
Assigment* variableNameAssignmentGrammarAction(VariableName* leftValue, Expression* rightValue);

// Factores.
int ExpressionFactorGrammarAction(const int value);
int ConstantFactorGrammarAction(const int value);
int VariableFactorGrammarAction(const int value);

// Constantes.
Constant* IntegerConstantGrammarAction(int value);
Constant* BooleanConstantGrammarAction(boolean value);

// Variables.
int NoteVariableGrammarAction(const int value);

#endif