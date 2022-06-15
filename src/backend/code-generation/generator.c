#include "../support/logger.h"
#include "generator.h"

/**
 * Implementación de "generator.h".
 */
void GenerateBlock(Block * block);
void GenerateSentence(Sentence * sentence);
void GenerateReturnLine(ReturnLine * returnLine);
void GenerateWhileStatement(WhileStatement * whileStatement);
void GenerateIfStatement(IfStatement * ifStatement);
void GenerateExpression(Expression * expression);
void GenerateAddNote(AddNote * addNote);
void GenerateMusicAssignment(MusicAssignment * musicAssignment);
void GenerateAssignment(Assignment * assignment);
void GenerateTypeDefinition(TypeDefinition * typeDefinition);
void GenerateMusicTypeDefinition(MusicTypeDefinition * musicTypeDefinition);
void GenerateGetter(Getter * getter);
void GenerateConstant(Constant * constant);
void GenerateVariableName(VariableName * variableName);


static void write_file(char * text) {
    fprintf(yyout, "%s", text);
}


void Generator(Program * program) {
    LogInfo("Generando código...");
    yyout = fopen("Output.java", "w");
    if (yyout == NULL) {
        LogError("No se pudo abrir el archivo Output.java");
        return;
    }
    write_file("import org.jfugue.player.Player;\n");
    write_file("public class Output {\n");
    write_file("public static void main(String[] args) {\n");
    write_file("String result;\n");

    GenerateBlock(program->block);

    write_file("new Player().play(result);\n");
    write_file("}\n");
    write_file("}\n");

    LogInfo("Fin.");
}

void GenerateBlock(Block * block) {
    switch (block->type) {
        case EMPTY_BLOCK:
            break;
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
            write_file(";\n");
            break;
        case ASSIGNMENT_SENTENCE:
            GenerateAssignment(sentence->sentence);
            write_file(";\n");
            break;
        case MUSIC_TYPE_DEFINITION_SENTENCE:
            GenerateMusicTypeDefinition(sentence->sentence);
            write_file(";\n");
            break;
        case MUSIC_ASSIGNMENT_SENTENCE:
            GenerateMusicAssignment(sentence->sentence);
            write_file(";\n");
            break;
        case ADD_NOTE_SENTENCE:
            GenerateAddNote(sentence->sentence);
            write_file(";\n");
            break;
        case IF_STATEMENT_SENTENCE:
            GenerateIfStatement(sentence->sentence);
            write_file("}\n");
            break;
        case WHILE_STATEMENT_SENTENCEM:
            GenerateWhileStatement(sentence->sentence);
            write_file("}\n");
            break;
        case RETURN_LINE_SENTENCE:
            GenerateReturnLine(sentence->sentence);
            write_file(";\n");
            break;
    }
}

void GenerateReturnLine(ReturnLine * returnLine) {
    write_file("result = ");
    switch (returnLine->type) {
        // TODO: Hacer cuando funcione bien el resto
        case VARIABLE_NAME_RETURN:
            GenerateVariableName(returnLine->value);
            break;
        case MUSIC_TYPE_DEFINITION_RETURN:
            GenerateMusicTypeDefinition(returnLine->value);
            break;
    }
    write_file(".toString()");
}

void GenerateWhileStatement(WhileStatement * whileStatement) {
    write_file("while (");
    GenerateExpression(whileStatement->expression);
    write_file(") {\n");
    GenerateBlock(whileStatement->block);
}

void GenerateIfStatement(IfStatement * ifStatement) {
    switch (ifStatement->type) {
        case IF_TYPE:
            write_file("if (");
            GenerateExpression(ifStatement->expression);
            write_file(") {\n");
            break;
        case IF_ELSE_TYPE:
            write_file("else ");
            GenerateIfStatement(ifStatement->expression);
            write_file(") {\n");
            break;
    }
    GenerateBlock(ifStatement->block);
}

void GenerateExpression(Expression * expression) {
    switch (expression->type) {
        case AND_EXPRESSION:
            GenerateExpression(expression->expression1);
            write_file(" && ");
            GenerateExpression(expression->expression2);
            break;
        case OR_EXPRESSION:
            GenerateExpression(expression->expression1);
            write_file(" || ");
            GenerateExpression(expression->expression2);
            break;
        case NOT_EXPRESSION:
            write_file("!");
            GenerateExpression(expression->expression1);
            break;
        case PLUS_EXPRESSION:
            GenerateExpression(expression->expression1);
            write_file(" + ");
            GenerateExpression(expression->expression2);
            break;
        case SUB_EXPRESSION:
            GenerateExpression(expression->expression1);
            write_file(" - ");
            GenerateExpression(expression->expression2);
            break;
        case MUL_EXPRESSION:
            GenerateExpression(expression->expression1);
            write_file(" * ");
            GenerateExpression(expression->expression2);
            break;
        case DIV_EXPRESSION:
            GenerateExpression(expression->expression1);
            write_file(" / ");
            GenerateExpression(expression->expression2);
            break;
        case EQUAL_EQUAL_EXPRESSION:
            GenerateExpression(expression->expression1);
            write_file(" == ");
            GenerateExpression(expression->expression2);
            break;
        case NOTEQUAL_EXPRESSION:
            GenerateExpression(expression->expression1);
            write_file(" != ");
            GenerateExpression(expression->expression2);
            break;
        case LOWER_EXPRESSION:
            GenerateExpression(expression->expression1);
            write_file(" < ");
            GenerateExpression(expression->expression2);
            break;
        case LOWER_EQUAL_EXPRESSION:
            GenerateExpression(expression->expression1);
            write_file(" <= ");
            GenerateExpression(expression->expression2);
            break;
        case GREATER_EXPRESSION:
            GenerateExpression(expression->expression1);
            write_file(" > ");
            GenerateExpression(expression->expression2);
            break;
        case GREATER_EQUAL_EXPRESSION:
            GenerateExpression(expression->expression1);
            write_file(" >= ");
            GenerateExpression(expression->expression2);
            break;
        case PARENTHESIS_EXPRESSION:
            write_file("(");
            GenerateExpression(expression->expression1);
            write_file(")");
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
    write_file(".addNote(");
    GenerateVariableName(addNote->note);
    write_file(")");
}

void GenerateMusicAssignment(MusicAssignment * musicAssignment) {
    switch (musicAssignment->type) {
        case TYPE_DEFINITION_MUSIC_ASSIGNMENT:
            switch (musicAssignment->musicAssignmentType) {
                case TONE_ASSIGNMENT:
                    GenerateMusicTypeDefinition(musicAssignment->variable);
                    fprintf(yyout, ".setTone('%c')", musicAssignment->value.tone.name);
                    fprintf(yyout, ".setOctave('%c')", musicAssignment->value.tone.octave);
                    if (musicAssignment->value.tone.type != '0')
                        fprintf(yyout, ".setType('%c')", musicAssignment->value.tone.type);
                    break;
                case RYTHM_ASSIGNMENT:
                    GenerateMusicTypeDefinition(musicAssignment->variable);
                    fprintf(yyout, ".setRythm(%d)", musicAssignment->value.rythm);
                    break;
                case BPM_ASSIGNMENT:
                    GenerateMusicTypeDefinition(musicAssignment->variable);
                    write_file(".setBpm(");
                    GenerateExpression(musicAssignment->value.expression);
                    write_file(")");
                    break;
                default:
                    LogError("Tipo de asignación de música no reconocido");
                    break;
            }
            break;

        case VARIABLE_NAME_MUSIC_ASSIGNMENT:
            GenerateVariableName(musicAssignment->variable);
            switch (musicAssignment->musicAssignmentType) {
                case TONE_ASSIGNMENT:
                    fprintf(yyout, ".setTone('%c')", musicAssignment->value.tone.name);
                    fprintf(yyout, ".setOctave('%c')", musicAssignment->value.tone.octave);
                    if (musicAssignment->value.tone.type != '0')
                        fprintf(yyout, ".setType('%c')", musicAssignment->value.tone.type);
                    break;
                case RYTHM_ASSIGNMENT:
                    fprintf(yyout, ".setRythm(%d)", musicAssignment->value.rythm);
                    break;
                case BPM_ASSIGNMENT:
                    write_file(".setBpm(");
                    GenerateExpression(musicAssignment->value.expression);
                    write_file(")");
                    break;
                case RAISE_OCTAVE_ASSIGNMENT:
                    write_file(".raiseOctave()");
                    break;
                case LOWER_TONE_ASSIGNMENT:
                    write_file(".lowerTone()");
                    break;
                case REMOVE_ASSIGNMENT:
                    write_file(".removeNote(");
                    GenerateExpression(musicAssignment->value.expression);
                    write_file(")");
                    break;
                case ADD_ASSIGNMENT:
                    write_file(".addNote(");
                    GenerateVariableName(musicAssignment->variableRight);
                    write_file(", ");
                    GenerateExpression(musicAssignment->value.expression);
                    write_file(")");
                    break;
            }
            break;

        case ASSIGNMENT_MUSIC_ASSIGNMENT:
            switch (musicAssignment->musicAssignmentType) {
                case RYTHM_ASSIGNMENT:
                    GenerateMusicAssignment(musicAssignment->variable);
                    fprintf(yyout, ".setRythm(%d)", musicAssignment->value.rythm);
                    break;
                case TONE_ASSIGNMENT:
                    GenerateMusicAssignment(musicAssignment->variable);
                    fprintf(yyout, ".setTone('%c')", musicAssignment->value.tone.name);
                    fprintf(yyout, ".setOctave('%c')", musicAssignment->value.tone.octave);
                    if (musicAssignment->value.tone.type != '0') {
                        fprintf(yyout, ".setType('%c')", musicAssignment->value.tone.type);
                    }
                    break;
                case BPM_ASSIGNMENT:
                    GenerateMusicAssignment(musicAssignment->variable);
                    fprintf(yyout, ".setBpm(");
                    GenerateExpression(musicAssignment->value.expression);
                    write_file(")");
                    break;
                default:
                    // TODO: Error
                    break;
            }
            break;
    }
}

void GenerateAssignment(Assignment * assignment) {
    switch (assignment->type) {
        case TYPE_DEFINITION_ASSIGNMENT:
            GenerateTypeDefinition(assignment->variable);
            break;
        case VARIABLE_NAME_ASSIGNMENT:
            GenerateVariableName(assignment->variable);
            break;
    }
    write_file(" = ");
    GenerateExpression(assignment->expression);
}

void GenerateTypeDefinition(TypeDefinition * typeDefinition) {
    switch (typeDefinition->type) {
        case BOOLEAN_DEFINITION:
            write_file("boolean ");
            break;
        case INTEGER_DEFINITION:
            write_file("int ");
            break;
    }
    GenerateVariableName(typeDefinition->name);
}

void GenerateMusicTypeDefinition(MusicTypeDefinition * musicTypeDefinition) {
    switch (musicTypeDefinition->type) {
        case MELODY_DEFINITION:
            write_file("MelodyWrapper ");
            GenerateVariableName(musicTypeDefinition->name);
            write_file(" = new MelodyWrapper()\n");
            break;
        case NOTE_DEFINITION:
            write_file("Note ");
            GenerateVariableName(musicTypeDefinition->name);
            write_file(" = new Note()\n");
            break;
    }
}

void GenerateGetter(Getter * getter) {
    GenerateVariableName(getter->name);
    switch (getter->type) {
        case RYTHM_GETTER:
            write_file(".getRythm()");
            break;
        case TONE_GETTER:
            write_file(".getTone()");
            break;
        case BPM_GETTER:
            write_file(".getBpm()");
            break;
        case DURATION_GETTER:
            write_file(".getDuration()");
            break;
    }
}

void GenerateConstant(Constant * constant) {
    switch (constant->type) {
        case INTEGER_CONSTANT:
            fprintf(yyout, "%d", constant->value.integer);
            break;
        case RYTHM_CONSTANT:
            fprintf(yyout, "%d", constant->value.rythm);
            break;
        case BOOLEAN_CONSTANT:
            fprintf(yyout, "%s", constant->value.boolean ? "true" : "false");
            break;
        case TONE_CONSTANT:
            fprintf(yyout, "'%c'", constant->value.tone.name);
            break;
    }
}

void GenerateVariableName(VariableName * variableName) {
    write_file(variableName->name);
}