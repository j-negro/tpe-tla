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

int AdditionExpressionGrammarAction(const int leftValue, const int rightValue) {
	LogDebug("AdditionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Add(leftValue, rightValue);
}

int SubtractionExpressionGrammarAction(const int leftValue, const int rightValue) {
	LogDebug("SubtractionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Subtract(leftValue, rightValue);
}

int MultiplicationExpressionGrammarAction(const int leftValue, const int rightValue) {
	LogDebug("MultiplicationExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Multiply(leftValue, rightValue);
}

int DivisionExpressionGrammarAction(const int leftValue, const int rightValue) {
	LogDebug("DivisionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return Divide(leftValue, rightValue);
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

int BooleanAndExpressionGrammarAction(const int leftValue,const int rightValue){
	LogDebug("BooleanAndExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return 0;
}

int BooleanOrExpressionGrammarAction(const int leftValue,const int rightValue){
	LogDebug("BooleanOrExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	return 0;
}

int BooleanNotExpressionGrammarAction(const int value){
	LogDebug("BooleanNotExpressionGrammarAction(%d)", value);
	return 0;
}
//-------------------------------------------Music Assignment----------------------------------------------

int MusicTypeToneDefinitionGrammarAction(const int value){
	LogDebug("MusicTypeToneDefinitionGrammarAction(%d)", value);
	return 0;
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

int MusicAssigmentBpmDefinitionGrammarAction(const int value){
	LogDebug("MusicAssigmentBpmDefinitionGrammarAction(%d)", value);
	return 0;
}

int VariableRaiseOctaveTypeDefinitionGrammarAction(const int value){
	LogDebug("VariableRaiseOctaveTypeDefinitionGrammarAction(%d)", value);
	return 0;
}

int VariableLowerToneDefinitionGrammarAction(const int value){
	LogDebug("VariableLowerToneDefinitionGrammarAction(%d)", value);
	return 0;
}

int VariableRemoveIntegerDefinitionGrammarAction(const int value){
	LogDebug("VariableRemoveIntegerDefinitionGrammarAction(%d)", value);
	return 0;
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

int CalculationEqualComparisonGrammarAction(const int leftValue, const int rightValue){
	LogDebug("CalculationEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	return 0;
}

int CalculationNotEqualComparisonGrammarAction(const int leftValue, const int rightValue){
	LogDebug("CalculationNotEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	return 0;
}

int CalculationLowerComparisonGrammarAction(const int leftValue, const int rightValue){
	LogDebug("CalculationLowerComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	return 0;
}

int CalculationGreaterComparisonGrammarAction(const int leftValue, const int rightValue){
	LogDebug("CalculationGreaterComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	return 0;
}

int CalculationGreaterEqualComparisonGrammarAction(const int leftValue, const int rightValue){
	LogDebug("CalculationGreaterEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	return 0;
}

int CalculationLowerEqualComparisonGrammarAction(const int leftValue, const int rightValue){
	LogDebug("CalculationLowerEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	return 0;
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

int IntegerConstantGrammarAction(const int value) {
	LogDebug("IntegerConstantGrammarAction(%d)", value);
	return value;
}

int NoteVariableGrammarAction(const int value) {
	LogDebug("NoteVariableGrammarAction(%d)", value);
	return value;
}

int VariableFactorGrammarAction(const int value) {
	LogDebug("VariableFactorGrammarAction(%d)", value);
	return value;
}
