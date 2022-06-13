#ifndef GENERATOR_HEADER
#define GENERATOR_HEADER

#include "../support/shared.h"

void Generator(Program * program);



void GenerateBlock(Block * block);
void GenerateSentence(Sentence * sentence);
void GenerateReturnLine(ReturnLine * returnLine);
void GenerateWhileStatement(WhileStatement * whileStatement);
void GenerateIfStatement(IfStatement * ifStatement);
void GenerateExpression(Expression * expression);
void GenerateAddNote(AddNote * addNote);
void GenerateMusicAssignment(MusicAssignment * musicAssignment);
void GenerateAssigment(Assigment * assigment);
void GenerateTypeDefinition(TypeDefinition * typeDefinition);
void GenerateMusicTypeDefinition(MusicTypeDefinition * musicTypeDefinition);
void GenerateGetter(Getter * getter);
void GenerateConstant(Constant * constant);
void GenerateVariableName(VariableName * variableName);

#endif