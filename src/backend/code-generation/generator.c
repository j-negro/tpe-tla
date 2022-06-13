#include "../support/logger.h"
#include "generator.h"

/**
 * Implementación de "generator.h".
 */

void Generator(Program * program) {
    LogInfo("Generando codigo...");
    GenerateBlock(program->block);

    LogInfo("Fin.");
}

void GenerateBlock(Block * block) {
    switch (block->type) {
        case EMPTY_BLOCK:
            return; // TODO: Verificar
        case FILLED_BLOCK:
            GenerateSentence(block->sentence);
            GenerateBlock(block->block);
            break;
    }
}

void GenerateSentence(Sentence * sentence) {
    switch (sentence->type) {
        case TYPE_DEFINITION_SENTENCE:
            GenerateTypeDefinition(sentence->sentence);
            break;
        case ASSIGNMENT_SENTENCE:
            GenerateAssigment(sentence->sentence);
            break;
        case MUSIC_TYPE_DEFINITION_SENTENCE:
            GenerateMusicTypeDefinition(sentence->sentence);
            break;
        case MUSIC_ASSIGNMENT_SENTENCE:
            GenerateMusicAssignment(sentence->sentence);
            break;
        case ADD_NOTE_SENTENCE:
            GenerateAddNote(sentence->sentence);
            break;
        case IF_STATEMENT_SENTENCE:
            GenerateIfStatement(sentence->sentence);
            break;
        case WHILE_STATEMENT_SENTENCEM:
            GenerateWhileStatement(sentence->sentence);
            break;
        case RETURN_LINE_SENTENCE:
            GenerateReturnLine(sentence->sentence);
            break;
    }
}

void GenerateReturnLine(ReturnLine * returnLine) {
    switch (returnLine->type) {
        case VARIABLE_NAME_RETURN:
            GenerateVariableName(returnLine->value);
            break;
        case MUSIC_TYPE_DEFINITION_RETURN:
            GenerateMusicTypeDefinition(returnLine->value);
            break;
    }
}

void GenerateWhileStatement(WhileStatement * whileStatement) {
    GenerateExpression(whileStatement->expression);
    GenerateBlock(whileStatement->block);
}

void GenerateIfStatement(IfStatement * ifStatement) {
    switch (ifStatement->type) {
        case IF_TYPE:
            GenerateExpression(ifStatement->expression);
            break;
        case IF_ELSE_TYPE:
            GenerateIfStatement(ifStatement->expression);
            break;
    }
    GenerateBlock(ifStatement->block);
}

void GenerateExpression(Expression * expression) {
    switch (expression->type) {
        case AND_EXPRESSION:
            GenerateExpression(expression->expression1);
            GenerateExpression(expression->expression2);
            break;
        case OR_EXPRESSION:
            GenerateExpression(expression->expression1);
            GenerateExpression(expression->expression2);
            break;
        case NOT_EXPRESSION:
            GenerateExpression(expression->expression1);
            break;
        case PLUS_EXPRESSION:
            GenerateExpression(expression->expression1);
            GenerateExpression(expression->expression2);
            break;
        case SUB_EXPRESSION:
            GenerateExpression(expression->expression1);
            GenerateExpression(expression->expression2);
            break;
        case MUL_EXPRESSION:
            GenerateExpression(expression->expression1);
            GenerateExpression(expression->expression2);
            break;
        case DIV_EXPRESSION:
            GenerateExpression(expression->expression1);
            GenerateExpression(expression->expression2);
            break;
        case EQUAL_EQUAL_EXPRESSION:
            GenerateExpression(expression->expression1);
            GenerateExpression(expression->expression2);
            break;
        case NOTEQUAL_EXPRESSION:
            GenerateExpression(expression->expression1);
            GenerateExpression(expression->expression2);
            break;
        case LOWER_EXPRESSION:
            GenerateExpression(expression->expression1);
            GenerateExpression(expression->expression2);
            break;
        case LOWER_EQUAL_EXPRESSION:
            GenerateExpression(expression->expression1);
            GenerateExpression(expression->expression2);
            break;
        case GREATER_EXPRESSION:
            GenerateExpression(expression->expression1);
            GenerateExpression(expression->expression2);
            break;
        case GREATER_EQUAL_EXPRESSION:
            GenerateExpression(expression->expression1);
            GenerateExpression(expression->expression2);
            break;
        case PARENTHESIS_EXPRESSION:
            GenerateExpression(expression->expression1);
            break;
        case VARIABLE_EXPRESSION:
            GenerateVariableName(expression->value);
            break;
        case CONSTANT_EXPRESSION:
            GenerateConstant(expression->value);
            break;
        case GETTER_EXPRESSION:
            GenerateGetter(expression->value);
            break;
    }
}

void GenerateAddNote(AddNote * addNote) {
    GenerateVariableName(addNote->melody);
    GenerateVariableName(addNote->note);
}

void GenerateMusicAssignment(MusicAssignment * musicAssignment) {
    switch (musicAssignment->type) {


        case TYPE_DEFINITION_MUSIC_ASSIGNMENT:
            switch (musicAssignment->musicAssignmentType) {
                case TONE_ASSIGNMENT:
                    break;
                case RYTHM_ASSIGNMENT:
                    break;
                case BPM_ASSIGNMENT:
                    break;
                default:
                    // TODO: Error
                    break;
            }
            break;


        case VARIABLE_NAME_MUSIC_ASSIGNMENT:
            GenerateVariableName(musicAssignment->variable);
            switch (musicAssignment->musicAssignmentType) {
                case RYTHM_ASSIGNMENT:
                    break;
                case TONE_ASSIGNMENT:
                    break;
                case ADD_ASSIGNMENT:
                    break;
                case REMOVE_ASSIGNMENT:
                    break;
                default:
                    // TODO: Error
                    break;
            }
            break;


        case ASSIGNMENT_MUSIC_ASSIGNMENT:
            switch (musicAssignment->musicAssignmentType) {
                case RYTHM_ASSIGNMENT:
                    break;
                case TONE_ASSIGNMENT:
                    break;
                case BPM_ASSIGNMENT:
                    break;
                default:
                    // TODO: Error
                    break;
            }
            break;
    }

}

void GenerateAssigment(Assigment * assigment) {
    switch (assigment->type) {
        case TYPE_DEFINITION_ASSIGNMENT:
            GenerateTypeDefinition(assigment->variable);
            break;
        case VARIABLE_NAME_ASSIGNMENT:
            GenerateVariableName(assigment->variable);
            break;
    }
    GenerateExpression(assigment->expression);
}

void GenerateTypeDefinition(TypeDefinition * typeDefinition) {
    switch (typeDefinition->type) {
        case BOOLEAN_DEFINITION:
            // TODO: Write "boolean"
            break;
        case INTEGER_DEFINITION:
            // TODO: Write "int"
            break;
    }
    GenerateVariableName(typeDefinition->name);
}

void GenerateMusicTypeDefinition(MusicTypeDefinition * musicTypeDefinition) {
    switch (musicTypeDefinition->type) {
        case MELODY_DEFINITION:
            // TODO: Write "melody"
            break;
        case NOTE_DEFINITION:
            // TODO: Write "note"
            break;
    }
    GenerateVariableName(musicTypeDefinition->name);
}

void GenerateGetter(Getter * getter) {
    GenerateVariableName(getter->name);
    switch (getter->type) {
        case RYTHM_GETTER:
            // TODO: Write "rythm"
            break;
        case TONE_GETTER:
            // TODO: Write "tone"
            break;
        case BPM_GETTER:
            // TODO: Write "bpm"
            break;
        case DURATION_GETTER:
            // TODO: Write "duration"
            break;
    }
}

void GenerateConstant(Constant * constant) {
    // TODO: Write constant->value
}

void GenerateVariableName(VariableName * variableName) {
    // TODO: Write variableName->name
}