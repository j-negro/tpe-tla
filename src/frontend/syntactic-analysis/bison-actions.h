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
Program *ProgramGrammarAction(Block* block);

// Expresión.
Expression* AdditionExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* SubtractionExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* MultiplicationExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* DivisionExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* ExpressionGetterGrammarAction(Getter* getter);
Expression* ConstantExpressionGrammarAction(Constant * constant);

//Sentences
Sentence*  SentenceTypeDefinitionGrammarAction(TypeDefinition* typeDefintion);
Sentence*  SentenceAssignmentGrammarAction(Assigment* assignment);
Sentence*  SentenceMusicTypeDefinitionGrammarAction(MusicTypeDefinition* musicTypeDefinition);
Sentence*  SentenceMusicAssignmentDefinitionGrammarAction(MusicAssignment* musicAssignment);
Sentence*  SentenceAddNoteGrammarAction(AddNote* addNote);
Sentence*  SentenceIfStatementGrammarAction(IfStatement* ifStatement);
Sentence*  SentenceWhileStatementGrammarAction(WhileStatement* whileStatement);
Sentence*  SentenceReturnLineGrammarAction(ReturnLine* returnLine);

//Statements
IfStatement *ifStatementGrammarAction(Expression * expression, Block* block);
IfStatement *ifElseStatementGrammarAction(IfStatement * ifS, Block* block);

WhileStatement *WhileStatementGrammarAction(Expression *expression, Block* block);

//Expresion booleana
Expression* BooleanAndExpressionGrammarAction(Expression* leftValue,Expression* rightValue);
Expression* BooleanOrExpressionGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* BooleanNotExpressionGrammarAction(Expression* expression);

//Comparacion
Expression* ExpressionEqualComparisonGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* ExpressionNotEqualComparisonGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* ExpressionLowerComparisonGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* ExpressionGreaterComparisonGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* ExpressionGreaterEqualComparisonGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* ExpressionLowerEqualComparisonGrammarAction(Expression* leftValue, Expression* rightValue);
Expression* ParenthesisExpressionGrammarAction(Expression* expression);
Expression* VariableNameExpressionGrammarAction(VariableName* variableName);

//Assignments
MusicAssignment* MusicTypeToneDefinitionGrammarAction(MusicTypeDefinition* value, tone Tone);
MusicAssignment *MusicTypeRythmDefinitionGrammarAction(MusicTypeDefinition* musicTypeDefinition, rythm Rythm);
MusicAssignment *MusicTypeDefinitionGrammarAction(MusicTypeDefinition* musicTypeDefinition, Expression * Bpm);
MusicAssignment *VariableToneTypeDefinitionGrammarAction(VariableName* variableName, tone tone);
MusicAssignment * VariableRythmTypeDefinitionGrammarAction(VariableName * variableName, rythm rythm);
MusicAssignment* VariableBpmTypeDefinitionGrammarAction(VariableName* variableName, Expression* expression);
MusicAssignment* MusicAssigmentToneDefinitionGrammarAction(MusicAssignment* ms, tone tone);
MusicAssignment* MusicAssigmentRythmDefinitionGrammarAction(MusicAssignment* ms, rythm rythm);
MusicAssignment* MusicAssigmentBpmDefinitionGrammarAction(MusicAssignment* leftValue,Expression* rightValue);
MusicAssignment* VariableRaiseOctaveTypeDefinitionGrammarAction(VariableName* variableName);
MusicAssignment* VariableLowerToneDefinitionGrammarAction(VariableName* variableName);
MusicAssignment* VariableRemoveExpressionGrammarAction(VariableName* variableName, Expression* expression);
MusicAssignment* VariableRemoveIntegerDefinitionGrammarAction(VariableName* variableName, Expression* value);
MusicAssignment* VariableAdditionTypeDefinitionGrammarAction(VariableName* left, VariableName* right, Expression* expression);


Assigment* typeDefinitionAssignmentGrammarAction(TypeDefinition* leftValue, Expression* rightValue);
Assigment* variableNameAssignmentGrammarAction(VariableName* leftValue, Expression* rightValue);

// TypeDefinitions
TypeDefinition * BooleanTypeDefinitionGrammarAction(VariableName * variableName);
TypeDefinition * IntegerTypeDefinitionGrammarAction(VariableName * variableName);

// MusicTypeDefinitions
MusicTypeDefinition * MelodyMusicDefinitionTypeGrammarAction(VariableName * variableName);
MusicTypeDefinition * NoteMusicDefinitionTypeGrammarAction(VariableName * variableName);


// Constantes.
Constant* IntegerConstantGrammarAction(int value);
Constant* BooleanConstantGrammarAction(boolean value);
Constant* ToneConstantGrammarAction(tone tone);
Constant* RythmConstantGrammarAction(rythm rythm);

//Getter
Getter * RythymGetterGrammarAction(VariableName * variableName);
Getter * ToneGetterGrammarAction(VariableName * variableName);
Getter * BpmGetterGrammarAction(VariableName * variableName);
Getter * DurationGetterGrammarAction(VariableName * variableName);

// Add note
AddNote* AddNoteGrammarAction(VariableName *melody, VariableName *note);

// Return Line
ReturnLine* ReturnVariableNameGrammarAction(VariableName *melody);
ReturnLine* ReturnMusicTypeDefinitionGrammarAction(MusicTypeDefinition *musicTypeDefinition);

// Block
Block * BlockSentenceGrammarAction(Sentence *sentence, Block *block);

//
VariableName * VariableNameGrammarAction(char * variable);

Block* EmptyBlockSentenceGrammarAction();
#endif