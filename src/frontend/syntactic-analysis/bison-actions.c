#include "../../backend/support/logger.h"
#include "bison-actions.h"
#include <stdlib.h>
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

Program *ProgramGrammarAction(Block* value) {
	LogDebug("ProgramGrammarAction(%d)", value);
	Program * program = (Program*) malloc(sizeof(Program));
    program->block =value;
    state.succeed = true;
    state.program = program;
	return program;
}

Expression* AdditionExpressionGrammarAction(Expression* leftValue, Expression* rightValue) {
	LogDebug("AdditionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = PLUS_EXPRESSION;
	return toReturn;
}

Expression* SubtractionExpressionGrammarAction(Expression* leftValue, Expression* rightValue) {
	LogDebug("SubtractionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = SUB_EXPRESSION;
	return toReturn;
}

Expression* MultiplicationExpressionGrammarAction(Expression* leftValue, Expression* rightValue) {
	LogDebug("MultiplicationExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = MUL_EXPRESSION;
	return toReturn;
}

Expression* DivisionExpressionGrammarAction(Expression* leftValue, Expression* rightValue) {
	LogDebug("DivisionExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = DIV_EXPRESSION;
	return toReturn;
}

Expression* ConstantExpressionGrammarAction(Constant * constant) {
    LogDebug("ConstantExpressionGrammarAction");
    Expression* toReturn = (Expression*) malloc(sizeof(Expression));
    toReturn->type = CONSTANT_EXPRESSION;
    toReturn->value = constant;
    return toReturn;
}
//--------------------------------------------Sentences-------------------------------------------------------------

Sentence*  SentenceTypeDefinitionGrammarAction(TypeDefinition* typeDefintion){
    LogDebug("SentenceTypeDefinitionGrammarAction");
	Sentence* sentence = (Sentence*) malloc(sizeof(Sentence));
	sentence->type = TYPE_DEFINITION_SENTENCE;
	sentence->sentence = typeDefintion;
	return sentence;
}

Sentence*  SentenceAssignmentGrammarAction(Assignment* assignment){
    LogDebug("SentenceAssignmentGrammarAction");
	Sentence* sentence = (Sentence*) malloc(sizeof(Sentence));
	sentence->type = ASSIGNMENT_SENTENCE;
	sentence->sentence = assignment;
	return sentence;
}

Sentence* SentenceMusicTypeDefinitionGrammarAction(MusicTypeDefinition* musicTypeDefinition){
    LogDebug("SentenceMusicTypeDefinitionGrammarAction");
	Sentence* sentence = (Sentence*) malloc(sizeof(Sentence));
	sentence->type = MUSIC_TYPE_DEFINITION_SENTENCE;
	sentence->sentence = musicTypeDefinition;
	return sentence;
}

Sentence*  SentenceMusicAssignmentDefinitionGrammarAction(MusicAssignment* musicAssignment){
    LogDebug("SentenceMusicAssignmentDefinitionGrammarAction");
	Sentence* sentence = (Sentence*) malloc(sizeof(Sentence));
	sentence->type = MUSIC_ASSIGNMENT_SENTENCE;
	sentence->sentence = musicAssignment;
	return sentence;
}

Sentence*  SentenceAddNoteGrammarAction(AddNote* addNote){
    LogDebug("SentenceAddNoteGrammarAction");
	Sentence* sentence = (Sentence*) malloc(sizeof(Sentence));
	sentence->type = ADD_NOTE_SENTENCE;
	sentence->sentence = addNote;
	return sentence;
}

Sentence*  SentenceIfStatementGrammarAction(IfStatement* ifStatement){
    LogDebug("SentenceIfStatementGrammarAction");
	Sentence* sentence = (Sentence*) malloc(sizeof(Sentence));
	sentence->type = IF_STATEMENT_SENTENCE;
	sentence->sentence = ifStatement;
	return sentence;
}

Sentence*  SentenceWhileStatementGrammarAction(WhileStatement* whileStatement){
    LogDebug("SentenceWhileStatementGrammarAction");
	Sentence* sentence = (Sentence*) malloc(sizeof(Sentence));
	sentence->type = WHILE_STATEMENT_SENTENCEM;
	sentence->sentence = whileStatement;
	return sentence;
}

Sentence*  SentenceReturnLineGrammarAction(ReturnLine* returnLine){
    LogDebug("SentenceReturnLineGrammarAction");
	Sentence* sentence = (Sentence*) malloc(sizeof(Sentence));
	sentence->type = RETURN_LINE_SENTENCE;
	sentence->sentence = returnLine;
	return sentence;
}
//--------------------------------------------Statements------------------------------------------------------------
IfStatement *ifStatementGrammarAction(Expression * expression, Block* block){
    LogDebug("ifStatementGrammarAction");
	//LogDebug("IfStatementGrammarAction(%d, %d)", leftValue, rightValue);
    IfStatement * ifStatement = (IfStatement*) malloc(sizeof (IfStatement));
    ifStatement->expression = expression;
    ifStatement->block = block;
    ifStatement->type = IF_TYPE;
	return ifStatement;
}

IfStatement *ifElseStatementGrammarAction(IfStatement * ifS, Block* block) {
    LogDebug("ifElseStatementGrammarAction");
    IfStatement * ifStatement = (IfStatement*) malloc(sizeof (IfStatement));
    ifStatement->block = block;
    ifStatement->type = IF_ELSE_TYPE;
    ifStatement->expression = ifS;

    return ifStatement;
}

WhileStatement *WhileStatementGrammarAction(Expression *expression, Block* block){
    LogDebug("WhileStatementGrammarAction");
    WhileStatement * whileStatement = (WhileStatement*) malloc(sizeof (WhileStatement));
    whileStatement->expression = expression;
    whileStatement->block = block;
    return whileStatement;
}
//--------------------------------------------Expression---------------------------------------------------

Expression* BooleanAndExpressionGrammarAction(Expression * leftValue,Expression * rightValue){
    LogDebug("BooleanAndExpressionGrammarAction");
	//LogDebug("BooleanAndExpressionGrammarAction(%d, %d)", leftValue->value, rightValue->value);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = AND_EXPRESSION;
	return toReturn;
}

Expression* BooleanOrExpressionGrammarAction(Expression* leftValue, Expression* rightValue){
    LogDebug("BooleanOrExpressionGrammarAction");
	//LogDebug("BooleanOrExpressionGrammarAction(%d, %d)", leftValue, rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = OR_EXPRESSION;
	return toReturn;
}

Expression* BooleanNotExpressionGrammarAction(Expression* expression){
    LogDebug("BooleanNotExpressionGrammarAction");
	//LogDebug("BooleanNotExpressionGrammarAction(%d)", value);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = expression;
	toReturn->type = NOT_EXPRESSION;
	return toReturn;
}

Expression* ExpressionGetterGrammarAction(Getter* getter){
    LogDebug("ExpressionGetterGrammarAction");
    Expression* toReturn = (Expression*) malloc(sizeof(Expression));
    toReturn->type = GETTER_EXPRESSION;
    toReturn->value = getter;
    return toReturn;
}
//-------------------------------------------Assignments----------------------------------------------

MusicAssignment* MusicTypeToneDefinitionGrammarAction(MusicTypeDefinition* value, tone tone){
	LogDebug("MusicTypeToneDefinitionGrammarAction(%d)", value);
	MusicAssignment* musicAssignment = (MusicAssignment*) malloc(sizeof(MusicAssignment));
	musicAssignment->type = TYPE_DEFINITION_MUSIC_ASSIGNMENT;
	musicAssignment->musicAssignmentType = TONE_ASSIGNMENT;
	musicAssignment->variable = value;
	musicAssignment->value.tone = tone;
	return musicAssignment;
}

MusicAssignment *MusicTypeRythmDefinitionGrammarAction(MusicTypeDefinition* musicTypeDefinition, rythm Rythm){
    LogDebug("MusicTypeRythmDefinitionGrammarAction");
    MusicAssignment* musicAssignment = (MusicAssignment*) malloc(sizeof(MusicAssignment));
    musicAssignment->type = TYPE_DEFINITION_MUSIC_ASSIGNMENT;
    musicAssignment->musicAssignmentType = RYTHM_ASSIGNMENT;
    musicAssignment->variable = musicTypeDefinition;
    musicAssignment->value.rythm = Rythm;
    return musicAssignment;
}

MusicAssignment *MusicTypeDefinitionGrammarAction(MusicTypeDefinition* musicTypeDefinition, Expression * bpm){
    LogDebug("MusicTypeDefinitionGrammarAction");
    MusicAssignment* musicAssignment = (MusicAssignment*) malloc(sizeof(MusicAssignment));
    musicAssignment->type = TYPE_DEFINITION_MUSIC_ASSIGNMENT;
    musicAssignment->musicAssignmentType = BPM_ASSIGNMENT;
    musicAssignment->variable = musicTypeDefinition;
    musicAssignment->value.expression = bpm;
    return musicAssignment;
}

MusicAssignment *VariableToneTypeDefinitionGrammarAction(VariableName* variableName, tone tone){
    LogDebug("VariableToneTypeDefinitionGrammarAction");
    MusicAssignment* musicAssignment = (MusicAssignment*) malloc(sizeof(MusicAssignment));
    musicAssignment->type = VARIABLE_NAME_MUSIC_ASSIGNMENT;
    musicAssignment->musicAssignmentType = TONE_ASSIGNMENT;
    musicAssignment->variable = variableName;
    musicAssignment->value.tone = tone;
    return musicAssignment;
}

MusicAssignment *VariableRythmTypeDefinitionGrammarAction(VariableName * variableName, rythm rythm) {
    LogDebug("VariableRythmTypeDefinitionGrammarAction");
    MusicAssignment* musicAssignment = (MusicAssignment*) malloc(sizeof(MusicAssignment));
    musicAssignment->musicAssignmentType = RYTHM_ASSIGNMENT;
    musicAssignment->type = VARIABLE_NAME_MUSIC_ASSIGNMENT;
    musicAssignment->value.rythm = rythm;
    musicAssignment->variable = variableName;

	return musicAssignment;
}

MusicAssignment* VariableBpmTypeDefinitionGrammarAction(VariableName* variableName, Expression* bpm){
    LogDebug("VariableBpmTypeDefinitionGrammarAction");
    MusicAssignment* musicAssignment = (MusicAssignment*) malloc(sizeof(MusicAssignment));
    musicAssignment->musicAssignmentType = BPM_ASSIGNMENT;
    musicAssignment->type = VARIABLE_NAME_MUSIC_ASSIGNMENT;
    musicAssignment->value.expression = bpm;
    musicAssignment->variable = variableName;

	return musicAssignment;
}

MusicAssignment* MusicAssignmentToneDefinitionGrammarAction(MusicAssignment* ma, tone tone) {
    LogDebug("MusicAssignmentToneDefinitionGrammarAction");
    MusicAssignment* musicAssignment = (MusicAssignment*) malloc(sizeof(MusicAssignment));
	musicAssignment->musicAssignmentType = TONE_ASSIGNMENT;
    musicAssignment->type = ASSIGNMENT_MUSIC_ASSIGNMENT;
    musicAssignment->variable = ma;
    musicAssignment->value.tone = tone;

	return musicAssignment;
}

MusicAssignment* MusicAssignmentRythmDefinitionGrammarAction(MusicAssignment* ma, rythm rythm) {
    LogDebug("MusicAssignmentRythmDefinitionGrammarAction");
    MusicAssignment* musicAssignment = (MusicAssignment*) malloc(sizeof(MusicAssignment));
    musicAssignment->type = ASSIGNMENT_MUSIC_ASSIGNMENT;
    musicAssignment->musicAssignmentType = RYTHM_ASSIGNMENT;
    musicAssignment->variable = ma;
    musicAssignment->value.rythm = rythm;

	return musicAssignment;
}

MusicAssignment* MusicAssignmentBpmDefinitionGrammarAction(MusicAssignment* ma,Expression* bpm){
    LogDebug("MusicAssignmentBpmDefinitionGrammarAction");
	MusicAssignment* musicAssignment = (MusicAssignment*) malloc(sizeof(MusicAssignment));
	musicAssignment->musicAssignmentType = BPM_ASSIGNMENT;
	musicAssignment->type = ASSIGNMENT_MUSIC_ASSIGNMENT;
	musicAssignment->variable = ma;
	musicAssignment->value.expression = bpm;
	return musicAssignment;
}

Assignment* typeDefinitionAssignmentGrammarAction(TypeDefinition* leftValue, Expression* rightvalue){
    LogDebug("typeDefinitionAssignmentGrammarAction");
	Assignment * assignment =(Assignment*) malloc(sizeof(Assignment));
	assignment->expression = rightvalue;
	assignment->variable = leftValue;
	assignment->type = TYPE_DEFINITION_ASSIGNMENT;
	return assignment;
}

Assignment* variableNameAssignmentGrammarAction(VariableName* leftValue, Expression* rightValue){
    LogDebug("variableNameAssignmentGrammarAction");
	Assignment * assignment =(Assignment*) malloc(sizeof(Assignment));
	assignment->expression = rightValue;
	assignment->variable = leftValue;
	assignment->type = VARIABLE_NAME_ASSIGNMENT;
	return assignment;
}

MusicAssignment* VariableRaiseOctaveTypeDefinitionGrammarAction(VariableName* variableName){
    LogDebug("VariableRaiseOctaveTypeDefinitionGrammarAction");
    MusicAssignment* musicAssignment = (MusicAssignment*) malloc(sizeof(MusicAssignment));
    musicAssignment->type = VARIABLE_NAME_MUSIC_ASSIGNMENT;
    musicAssignment->musicAssignmentType = RAISE_OCTAVE_ASSIGNMENT;
    musicAssignment->variable = variableName;
    return musicAssignment;
}
MusicAssignment* VariableRemoveExpressionGrammarAction(VariableName* variableName, Expression* expression){
    LogDebug("VariableRemoveExpressionGrammarAction");
	MusicAssignment* musicAssignment = (MusicAssignment*) malloc(sizeof(MusicAssignment));
	musicAssignment->musicAssignmentType = REMOVE_ASSIGNMENT;
	musicAssignment->type = VARIABLE_NAME_MUSIC_ASSIGNMENT;
	musicAssignment->variable = variableName;
	musicAssignment->value.expression = expression;
	return musicAssignment;
}

MusicAssignment* VariableLowerToneDefinitionGrammarAction(VariableName* variableName){
    LogDebug("VariableLowerToneDefinitionGrammarAction");
	MusicAssignment* musicAssignment = (MusicAssignment*) malloc(sizeof(MusicAssignment));
	musicAssignment->musicAssignmentType = LOWER_TONE_ASSIGNMENT;
	musicAssignment->type = VARIABLE_NAME_MUSIC_ASSIGNMENT;
	musicAssignment->variable = variableName;
	return musicAssignment;
}

MusicAssignment* VariableAdditionTypeDefinitionGrammarAction(VariableName* left, VariableName* right, Expression* expression) {
    LogDebug("VariableAdditionTypeDefinitionGrammarAction");
    MusicAssignment* musicAssignment = (MusicAssignment*) malloc(sizeof(MusicAssignment));
    musicAssignment->type = VARIABLE_NAME_MUSIC_ASSIGNMENT;
    musicAssignment->musicAssignmentType = ADD_ASSIGNMENT;
    musicAssignment->variable = left;
    musicAssignment->variableRight = right;
    musicAssignment->value.expression = expression;

    return musicAssignment;
}
//--------------------------------------------Comparison---------------------------------------------------

Expression* ExpressionEqualComparisonGrammarAction(Expression* leftValue, Expression* rightValue){
    LogDebug("ExpressionEqualComparisonGrammarAction");
	//LogDebug("CalculationEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = EQUAL_EQUAL_EXPRESSION;
	return toReturn;
}

Expression* ExpressionNotEqualComparisonGrammarAction(Expression* leftValue, Expression* rightValue){
    LogDebug("ExpressionNotEqualComparisonGrammarAction");
	//LogDebug("CalculationNotEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = NOTEQUAL_EXPRESSION;
	return toReturn;
}

Expression* ExpressionLowerComparisonGrammarAction(Expression* leftValue, Expression* rightValue){
    LogDebug("ExpressionLowerComparisonGrammarAction");
	//LogDebug("CalculationLowerComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = LOWER_EXPRESSION;
	return toReturn;
}

Expression* ExpressionGreaterComparisonGrammarAction(Expression* leftValue, Expression* rightValue){
    LogDebug("ExpressionGreaterComparisonGrammarAction");
	//LogDebug("CalculationGreaterComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = GREATER_EXPRESSION;
	return toReturn;
}

Expression* ExpressionGreaterEqualComparisonGrammarAction(Expression* leftValue, Expression* rightValue){
    LogDebug("ExpressionGreaterEqualComparisonGrammarAction");
	//LogDebug("CalculationGreaterEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = GREATER_EQUAL_EXPRESSION;
	return toReturn;
}

Expression* ExpressionLowerEqualComparisonGrammarAction(Expression* leftValue, Expression* rightValue){
    LogDebug("ExpressionLowerEqualComparisonGrammarAction");
	//LogDebug("CalculationLowerEqualComparisonGrammarAction(%d,%d)",leftValue,rightValue);
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->expression1 = leftValue;
	toReturn->expression2 = rightValue;
	toReturn->type = LOWER_EQUAL_EXPRESSION;
	return toReturn;
}

Expression* ParenthesisExpressionGrammarAction(Expression* expression){
    LogDebug("ParenthesisExpressionGrammarAction");
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->type = PARENTHESIS_EXPRESSION;
	toReturn->expression1 = expression;
	return toReturn;
}

Expression* VariableNameExpressionGrammarAction(VariableName* variableName){
    LogDebug("VariableNameExpressionGrammarAction");
	Expression* toReturn = (Expression*) malloc(sizeof(Expression));
	toReturn->type = VARIABLE_EXPRESSION;
	toReturn->value = variableName;
	return toReturn;
}
//-------------------------------------------TypeDefinitionType--------------------------------------------
TypeDefinition * BooleanTypeDefinitionGrammarAction(VariableName * variableName) {
    LogDebug("BooleanTypeDefinitionGrammarAction");
	TypeDefinition * typeDef = malloc(sizeof(TypeDefinition));
	typeDef->type = BOOLEAN_DEFINITION;
	typeDef->name = variableName;
	return typeDef;
}

TypeDefinition * IntegerTypeDefinitionGrammarAction(VariableName * variableName) {
    LogDebug("IntegerTypeDefinitionGrammarAction");
	TypeDefinition * typeDef = malloc(sizeof(TypeDefinition));
	typeDef->type = INTEGER_DEFINITION;
	typeDef->name = variableName;
	return typeDef;
}

//-------------------------------------------MusicTypeDefinitionType--------------------------------------------
MusicTypeDefinition * MelodyMusicDefinitionTypeGrammarAction(VariableName * variableName) {
    LogDebug("MelodyMusicDefinitionTypeGrammarAction");
	MusicTypeDefinition * musicTypeDef = malloc(sizeof(MusicTypeDefinition));
	musicTypeDef->type = MELODY_DEFINITION;
	musicTypeDef->name = variableName;
	return musicTypeDef;
}

MusicTypeDefinition * NoteMusicDefinitionTypeGrammarAction(VariableName * variableName) {
    LogDebug("NoteMusicDefinitionTypeGrammarAction");
	MusicTypeDefinition * musicTypeDef = malloc(sizeof(MusicTypeDefinition));
	musicTypeDef->type = NOTE_DEFINITION;
	musicTypeDef->name = variableName;
	return musicTypeDef;
}


//-------------------------------------------ConstantType--------------------------------------------

Constant* IntegerConstantGrammarAction(int value) {
    LogDebug("IntegerConstantGrammarAction");
	Constant* constant = (Constant*) malloc(sizeof(Constant));
	constant->type = INTEGER_CONSTANT;
	constant->value.integer = value;
	return constant;
}

Constant* BooleanConstantGrammarAction(boolean value){
    LogDebug("BooleanConstantGrammarAction");
	Constant* constant = (Constant*) malloc(sizeof(Constant));
	constant->type = BOOLEAN_CONSTANT;
	constant->value.boolean = value;
	return constant;
}

Constant* ToneConstantGrammarAction(tone tone) {
    LogDebug("ToneConstantGrammarAction");
	Constant* constant = (Constant*) malloc(sizeof(Constant));
	constant->type = TONE_CONSTANT;
	constant->value.tone = tone;
    return constant;
}

Constant* RythmConstantGrammarAction(rythm rythm) {
    LogDebug("RythmConstantGrammarAction");
	Constant* constant = (Constant*) malloc(sizeof(Constant));
	constant->type = RYTHM_CONSTANT;
	constant->value.rythm = rythm;

    return constant;
}

//-------------------------------------------AddNoteType--------------------------------------------

AddNote* AddNoteGrammarAction(VariableName *melody, VariableName *note) {
    LogDebug("AddNoteGrammarAction");
	AddNote* addNote = (AddNote*) malloc(sizeof(AddNote));
	addNote->melody = melody;
	addNote->note = note;

    return addNote;
}

//-------------------------------------------ReturnLineType--------------------------------------------

ReturnLine* ReturnVariableNameGrammarAction(VariableName *melody) {
    LogDebug("ReturnVariableNameGrammarAction");
	ReturnLine* returnLine = (ReturnLine*) malloc(sizeof(ReturnLine));
	returnLine->type = VARIABLE_NAME_RETURN;
	returnLine->value = melody;

    return returnLine;
}

ReturnLine* ReturnMusicTypeDefinitionGrammarAction(MusicTypeDefinition *musicTypeDefinition) {
    LogDebug("ReturnMusicTypeDefinitionGrammarAction");
	ReturnLine* returnLine = (ReturnLine*) malloc(sizeof(ReturnLine));
	returnLine->type = MUSIC_TYPE_DEFINITION_RETURN;
	returnLine->value = musicTypeDefinition;

    return returnLine;
}

//-------------------------------------------BlockType--------------------------------------------

Block * BlockSentenceGrammarAction(Sentence *sentence, Block *otherBlock) {
    LogDebug("BlockSentenceGrammarAction %s", otherBlock->type == EMPTY_BLOCK ? "EMPTY_BLOCK" : "FILLED_BLOCK");
    Block* block = (Block*) malloc(sizeof(Block));
    block->block = otherBlock;
    block->sentence = sentence;
    block->type = FILLED_BLOCK;

    return block;
}
//-------------------------------------------Getters--------------------------------------------

Getter * RythymGetterGrammarAction(VariableName * variableName) {
    LogDebug("RythymGetterGrammarAction");
    Getter * getter = malloc(sizeof(Getter));
    getter->name = variableName;
    getter->type = RYTHM_GETTER;
    return getter;
}
Getter * ToneGetterGrammarAction(VariableName * variableName) {
    LogDebug("ToneGetterGrammarAction");
    Getter * getter = malloc(sizeof(Getter));
    getter->name = variableName;
    getter->type = TONE_GETTER;
    return getter;
}
Getter * BpmGetterGrammarAction(VariableName * variableName) {
    LogDebug("BpmGetterGrammarAction");
    Getter * getter = malloc(sizeof(Getter));
    getter->name = variableName;
    getter->type = BPM_GETTER;
    return getter;
}
Getter * DurationGetterGrammarAction(VariableName * variableName) {
    LogDebug("DurationGetterGrammarAction");
    Getter * getter = malloc(sizeof(Getter));
    getter->name = variableName;
    getter->type = DURATION_GETTER;
    return getter;
}

//-------------------------------------------Variable--------------------------------------------

VariableName * VariableNameGrammarAction(char * variable) {
    LogDebug("VariableNameGrammarAction: '%s'.", variable);
	VariableName * variableName = malloc(sizeof(VariableName));
    variableName->name = (char*) malloc(strlen(variable));
    strcpy(variableName->name, variable);
	return variableName;
}

//----------------------------------------------------------------------------------------------------
Block* EmptyBlockSentenceGrammarAction(){
    LogDebug("EmptyBlockSentenceGrammarAction");
    Block * block = malloc(sizeof(Block));
    block->type = EMPTY_BLOCK;
    return block;
}