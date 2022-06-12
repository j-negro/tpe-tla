#include "../../backend/domain-specific/calculator.h"
#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdio.h>
#include <string.h>

/**
 * Implementación de "bison-grammar.h".
 */

void yyerror(const char * string) {
	LogError("Mensaje: '%s' debido a '%s' (linea %d).", string, yytext, yylineno);
	LogError("En ASCII es:");
	LogErrorRaw("\t");
	const int length = strlen(yytext);
	for (int i = 0; i < length; ++i) {
		LogErrorRaw("[%d]", yytext[i]);
	}
	LogErrorRaw("\n\n");
}

int ProgramGrammarAction(const int value) {
	LogDebug("ProgramGrammarAction(%d)", value);
	state.succeed = true;
	state.result = value;
	return value;
}

Expression* AdditionExpressionGrammarAction(Expression* leftValue, Expression* rightValue) {
	//LogDebug("AdditionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = PLUS_EXPRESSION;
	return toReturn;
}

Expression* SubtractionExpressionGrammarAction(Expression* leftValue, Expression* rightValue) {
	//LogDebug("SubtractionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = SUB_EXPRESSION;
	return toReturn;
}

Expression* MultiplicationExpressionGrammarAction(Expression* leftValue, Expression* rightValue) {
	//LogDebug("MultiplicationExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = MUL_EXPRESSION;
	return toReturn;
}

Expression* DivisionExpressionGrammarAction(Expression* leftValue, Expression* rightValue) {
	//LogDebug("DivisionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = DIV_EXPRESSION;
	return toReturn;
}

int FactorExpressionGrammarAction(const int value) {
	LogDebug("FactorExpressionGrammarAction(%d)", value);
	return value;
}
//--------------------------------------------Statements------------------------------------------------------------
int ifStatementGrammarAction(const int leftValue,const int rightValue){
	LogDebug("IfStatementGrammarAction(%d, %d)", leftValue, rightValue);
	return 0;
}

int WhileStatementGrammarAction(const int leftValue,const int rightValue){
	LogDebug("WhileStatementGrammarAction(%d, %d)", leftValue, rightValue);
	return 0;
}
//--------------------------------------------Expression---------------------------------------------------
int VariableNameExpressionGrammarAction(const int value){
	LogDebug("VariableNameExpressionGrammarAction(%d)", value);
	return value;
}

int ComparisonExpressionGrammarAction(const int value){
	LogDebug("ComparisonExpressionGrammarAction(%d)", value);
	return value;
}

Expression* BooleanAndExpressionGrammarAction(Expression * leftValue,Expression * rightValue){
	//LogDebug("BooleanAndExpressionGrammarAction(%d, %d)", leftValue->value, rightValue->value);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = AND_EXPRESSION;
	return toReturn;
}

Expression* BooleanOrExpressionGrammarAction(Expression* leftValue, Expression* rightValue){
	//LogDebug("BooleanOrExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = OR_EXPRESSION;
	return toReturn;
}

Expression* BooleanNotExpressionGrammarAction(Expression* expression){
	//LogDebug("BooleanNotExpressionGrammarAction(%d)", value);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = expression;
	toReturn->type = NOT_EXPRESSION;
	return toReturn;
}
//-------------------------------------------Assignments----------------------------------------------

MusicAssignment* MusicTypeToneDefinitionGrammarAction(MusicTypeDefinition* value){
	LogDebug("MusicTypeToneDefinitionGrammarAction(%d)", value);
	MusicAssignment* musicAssignment = (MusicAssignment*) malloc(sizeof(MusicAssignment));
	musicAssignment->type = TYPE_DEFINITION_MUSIC_ASSIGNMENT;
	musicAssignment->musicAssignmentType = TONE_ASSIGNMENT;
	musicAssignment->variable = value;
	//musicAssignment->value = tone; a chequear porque tone lo definimos como un token
	return musicAssignment;
}

int MusicTypeRythmDefinitionGrammarAction(const int value){
	LogDebug("MusicTypeRythmDefinitionGrammarAction(%d)", value);
	return 0;
}

int MusicTypeDefinitionGrammarAction(const int value){
	LogDebug("MusicTypeDefinitionGrammarAction(%d)", value);
	return 0;
}

int VariableToneTypeDefinitionGrammarAction(const int value){
	LogDebug("VariableToneTypeDefinitionGrammarAction(%d)", value);
	return 0;
}

int VariableRythmTypeDefinitionGrammarAction(const int value){
	LogDebug("VariableRythmTypeDefinitionGrammarAction(%d)", value);
	return 0;
}

int VariableBpmTypeDefinitionGrammarAction(const int value){
	LogDebug("VariableBpmTypeDefinitionGrammarAction(%d)", value);
	return 0;
}

int MusicAssigmentToneDefinitionGrammarAction(const int value){
	LogDebug("MusicAssigmentToneDefinitionGrammarAction(%d)", value);
	return 0;
}

int MusicAssigmentRythmDefinitionGrammarAction(const int value){
	LogDebug("MusicAssigmentRythmDefinitionGrammarAction(%d)", value);
	return 0;
}

MusicAssignment* MusicAssigmentBpmDefinitionGrammarAction(MusicAssignment* musicAsignment,Expression* bpm){
	//LogDebug("MusicAssigmentBpmDefinitionGrammarAction(%d)", value);
	MusicAssignment* musicAssignment = (MusicAssignment*) malloc(sizeof(MusicAssignment));
	MusicAssignmentValue value;
	value.bpm = bpm;
	musicAssignment->musicAssignmentType = BPM_ASSIGNMENT;
	musicAssignment->type = ASSIGNMENT_MUSIC_ASSIGNMENT;
	musicAssignment->variable = musicAsignment;
	musicAssignment->value = value;
	return musicAssignment;
}

Assigment* typeDefinitionAssignmentGrammarAction(TypeDefinition* leftValue, Expression* rightvalue){
	Assigment * assigment =(Assigment*) malloc(sizeof(Assigment));
	assigment->expression = rightvalue;
	assigment->variable = leftValue;
	assigment->type = TYPE_DEFINITION_ASSIGNMENT;
	return assigment;
}

Assigment* variableNameAssignmentGrammarAction(VariableName* leftValue, Expression* rightValue){
	Assigment * assigment =(Assigment*) malloc(sizeof(Assigment));
	assigment->expression = rightValue;
	assigment->variable = leftValue;
	assigment->type = VARIABLE_NAME_ASSIGNMENT;
	return assigment;
}

int VariableRaiseOctaveTypeDefinitionGrammarAction(const int value){
	LogDebug("VariableRaiseOctaveTypeDefinitionGrammarAction(%d)", value);
	return 0;
}

int VariableLowerToneDefinitionGrammarAction(const int value){
	LogDebug("VariableLowerToneDefinitionGrammarAction(%d)", value);
	return 0;
}

MusicAssignment* VariableRemoveIntegerDefinitionGrammarAction(VariableName* variableName, Expression* expression){
	//LogDebug("VariableRemoveIntegerDefinitionGrammarAction(%d)", value);
	MusicAssignment* musicAssignment = (MusicAssignment*) malloc(sizeof(MusicAssignment));
	MusicAssignmentValue value;
	value.bpm = expression;
	musicAssignment->musicAssignmentType = REMOVE_ASSIGNMENT;
	musicAssignment->type = VARIABLE_NAME_ASSIGNMENT;
	musicAssignment->variable = variableName;
	musicAssignment->value = value;
	return musicAssignment;
}

int VariableAdditionTypeDefinitionGrammarAction(const int value){
	LogDebug("VariableAdditionTypeDefinitionGrammarAction(%d)", value);
	return 0;
}
//--------------------------------------------Comparison---------------------------------------------------
int RythmEqualComparisonGrammarAction(const int leftValue, const int rightValue ){
	LogDebug("RythmEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	return 0;
}

int RythmNotEqualComparisonGrammarAction(const int leftValue, const int rightValue ){
	LogDebug("RythmNotEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	return 0;
}

int ToneEqualComparisonGrammarAction(const int leftValue, const int rightValue){
	LogDebug("ToneEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	return 0;
}

int ToneNotEqualComparisonGrammarAction(const int leftValue, const int rightValue){
	LogDebug("ToneNotEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	return 0;
}

int ToneLowerComparisonGrammarAction(const int leftValue, const int rightValue ){
	LogDebug("ToneLowerComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	return 0;
}

int ToneGreaterComparisonGrammarAction(const int leftValue, const int rightValue ){
	LogDebug("ToneGreaterComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	return 0;
}

int ToneLowerEqualComparisonGrammarAction(const int leftValue, const int rightValue ){
	LogDebug("ToneLowerEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	return 0;
}

int ToneGreaterEqualComparisonGrammarAction(const int leftValue, const int rightValue ){
	LogDebug("ToneGreaterEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	return 0;
}

Expression* ExpressionEqualComparisonGrammarAction(Expression* leftValue, Expression* rightValue){
	//LogDebug("CalculationEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = EQUAL_EQUAL_EXPRESSION;
	return toReturn;
}

Expression* ExpressionNotEqualComparisonGrammarAction(Expression* leftValue, Expression* rightValue){
	//LogDebug("CalculationNotEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = NOTEQUAL_EXPRESSION;
	return toReturn;
}

Expression* ExpressionLowerComparisonGrammarAction(Expression* leftValue, Expression* rightValue){
	//LogDebug("CalculationLowerComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = LOWER_EXPRESSION;
	return toReturn;
}

Expression* ExpressionGreaterComparisonGrammarAction(Expression* leftValue, Expression* rightValue){
	//LogDebug("CalculationGreaterComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = GREATER_EXPRESSION;
	return toReturn;
}

Expression* ExpressionGreaterEqualComparisonGrammarAction(Expression* leftValue, Expression* rightValue){
	//LogDebug("CalculationGreaterEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = GREATER_EQUAL_EXPRESSION;
	return toReturn;
}

Expression* ExpressionLowerEqualComparisonGrammarAction(Expression* leftValue, Expression* rightValue){
	//LogDebug("CalculationLowerEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = LOWER_EQUAL_EXPRESSION;
	return toReturn;
}
//-------------------------------------------Insert section here--------------------------------------------
int ExpressionFactorGrammarAction(const int value) {
	LogDebug("ExpressionFactorGrammarAction(%d)", value);
	return value;
}

int ConstantFactorGrammarAction(const int value) {
	LogDebug("ConstantFactorGrammarAction(%d)", value);
	return value;
}

Constant* IntegerConstantGrammarAction(int value) {
	Constant* constant = (Constant*) malloc(sizeof(Constant));
	ConstantValue constantValue;
	constantValue.integer = value;
	constant->type = INTEGER_CONSTANT;
	constant->value = constantValue;
	return constant;
}

Constant* BooleanConstantGrammarAction(boolean value){
	Constant* constant = (Constant*) malloc(sizeof(Constant));
	ConstantValue constantValue;
	constantValue.boolean = value;
	constant->type = BOOLEAN_CONSTANT;
	constant->value = constantValue;
	return constant;
}

int NoteVariableGrammarAction(const int value) {
	LogDebug("NoteVariableGrammarAction(%d)", value);
	return value;
}

int VariableFactorGrammarAction(const int value) {
	LogDebug("VariableFactorGrammarAction(%d)", value);
	return value;
}
