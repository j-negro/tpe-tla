#include "semantic-analysis.h"

static Stack stack;

static boolean validate_music_type_definition(MusicTypeDefinition *ptr);
static boolean validate_type_definition(TypeDefinition *ptr);
static boolean validate_add_note(AddNote *ptr);
static boolean validate_return_line(ReturnLine *ptr);
static boolean validate_assignment(Assigment *ptr);
static boolean validate_expression(Expression *expression, VariableType type);
static boolean validate_constant(Constant *constant, VariableType type);
static boolean validate_getter(Getter *ptr, VariableType type);
static boolean validate_if_statement(IfStatement *ptr);
static boolean validate_block(Block *block);
static boolean validate_while_statement(WhileStatement *ptr);
static boolean validate_music_assignment(MusicAssignment *ptr, VariableType *saved_type);

static boolean validate_variable_type(VariableName *name, VariableType type) {
    VariableType variable_type = find_symbol_in_stack(&stack, name->name);
    if (variable_type == -1 || variable_type != type) {
        return false;
    }
    return true;
}

static boolean validate_sentence(Sentence *sentence) {
    switch (sentence->type) {
        case TYPE_DEFINITION_SENTENCE:
            return validate_type_definition((TypeDefinition *) sentence->sentence);
        case ASSIGNMENT_SENTENCE:
            return validate_assignment((Assigment *) sentence->sentence);
        case MUSIC_TYPE_DEFINITION_SENTENCE:
            return validate_music_type_definition((MusicTypeDefinition *) sentence->sentence);
        case MUSIC_ASSIGNMENT_SENTENCE:
            return validate_music_assignment((MusicAssignment *) sentence->sentence, NULL);
        case ADD_NOTE_SENTENCE:
            return validate_add_note((AddNote *) sentence->sentence);
        case IF_STATEMENT_SENTENCE:
            return validate_if_statement((IfStatement *) sentence->sentence);
        case WHILE_STATEMENT_SENTENCEM:
            return validate_while_statement((WhileStatement *) sentence->sentence);
        case RETURN_LINE_SENTENCE:
            return validate_return_line((ReturnLine *) sentence->sentence);
        default:
            return false;
    }
}

static boolean validate_music_assignment(MusicAssignment *ptr, VariableType *saved_type) {
    VariableType variable_type;
    switch (ptr->type) {
        case TYPE_DEFINITION_MUSIC_ASSIGNMENT:
            if (!validate_type_definition((TypeDefinition *) ptr->variable)) {
                return false;
            }
            variable_type = find_symbol_in_stack(&stack, ((TypeDefinition *) ptr->variable)->name->name);
            break;
        case VARIABLE_NAME_MUSIC_ASSIGNMENT:
            variable_type = find_symbol_in_stack(&stack, ((VariableName *) ptr->variable)->name);
            break;
        case ASSIGNMENT_MUSIC_ASSIGNMENT:
            if (!validate_music_assignment((MusicAssignment *) ptr->variable, &variable_type)) {
                return false;
            }
            break;
    }

    if (variable_type != VAR_NOTE && variable_type != VAR_MELODY) return false;

    if (saved_type != NULL) {
        *saved_type = variable_type;
    }

    switch (ptr->musicAssignmentType) {
        case TONE_ASSIGNMENT:
        case RYTHM_ASSIGNMENT:
        case RAISE_OCTAVE_ASSIGNMENT:
            return variable_type == VAR_NOTE;
        case BPM_ASSIGNMENT:
        case REMOVE_ASSIGNMENT:
            return variable_type == VAR_MELODY && validate_expression(ptr->value.bpm, VAR_INT);
        case LOWER_TONE_ASSIGNMENT:
            return variable_type == VAR_MELODY;
        case ADD_ASSIGNMENT:
            return variable_type == VAR_MELODY && validate_expression(ptr->value.bpm, VAR_INT)
                    && (validate_variable_type(ptr->variableRight, VAR_NOTE) || validate_variable_type(ptr->variableRight, VAR_MELODY));
    }
}

static boolean validate_while_statement(WhileStatement *ptr) {
    push(&stack);
    boolean ret = validate_expression(ptr->expression, VAR_BOOL) && validate_block(ptr->block);
    pop(&stack);
    return ret;
}

static boolean validate_if_statement(IfStatement *ptr) {
    push(&stack);
    boolean ret;
    switch (ptr->type) {
        case IF_TYPE:
            ret = validate_expression((Expression *) ptr->expression, VAR_BOOL) && validate_block(ptr->block);
            break;
        case IF_ELSE_TYPE:
            ret = validate_if_statement((IfStatement *) ptr->expression) && validate_block(ptr->block);
            break;
        default:
            ret = false;
    }
    pop(&stack);
    return ret;
}

static boolean validate_assignment(Assigment *ptr) {
    VariableType variable_type;
    switch (ptr->type) {
        case TYPE_DEFINITION_ASSIGNMENT:
            if (validate_type_definition((TypeDefinition *) ptr->variable)) {
                variable_type = find_symbol_in_stack(&stack, ((TypeDefinition *) ptr->variable)->name->name);
                return validate_expression((Expression *) ptr->expression, variable_type);
            }
            return false;
        case VARIABLE_NAME_ASSIGNMENT:
            variable_type = find_symbol_in_stack(&stack, ((VariableName *) ptr->variable)->name);
            return validate_expression((Expression *) ptr->expression, variable_type);
        default:
            return false;
    }
}

static boolean validate_expression(Expression *expression, VariableType type) {
    switch (expression->type) {
        case PLUS_EXPRESSION:
        case SUB_EXPRESSION:
        case MUL_EXPRESSION:
        case DIV_EXPRESSION:
            return type == VAR_INT && validate_expression((Expression *) expression->expression1, type) &&
                   validate_expression((Expression *) expression->expression2, type);
        case EQUAL_EQUAL_EXPRESSION:
        case NOTEQUAL_EXPRESSION:
        case LOWER_EXPRESSION:
        case LOWER_EQUAL_EXPRESSION:
        case GREATER_EXPRESSION:
        case GREATER_EQUAL_EXPRESSION:
            return type == VAR_BOOL && validate_expression((Expression *) expression->expression1, VAR_INT) &&
                   validate_expression((Expression *) expression->expression2, VAR_INT);
        case AND_EXPRESSION:
        case OR_EXPRESSION:
            return type == VAR_BOOL && validate_expression((Expression *) expression->expression1, type) &&
                   validate_expression((Expression *) expression->expression2, type);
        case NOT_EXPRESSION:
            return type == VAR_BOOL && validate_expression((Expression *) expression->expression1, type);
        case PARENTHESIS_EXPRESSION:
            return validate_expression((Expression *) expression->expression1, type);
        case VARIABLE_EXPRESSION:
            return validate_variable_type((VariableName *) expression->value, type);
        case CONSTANT_EXPRESSION:
            return validate_constant((Constant *) expression->value, type);
        case GETTER_EXPRESSION:
            return validate_getter((Getter *) expression->value, type);
        default:
            return false;
    }
}

static boolean validate_getter(Getter *ptr, VariableType type) {
    switch (ptr->type) {
        case BPM_GETTER:
        case DURATION_GETTER:
            return type == VAR_INT;
        case RYTHM_GETTER:
        case TONE_GETTER:
        default: // TODO: ver si los casos de arriba tienen sentido
            return false;
    }
}

static boolean validate_constant(Constant *constant, VariableType type) {
    switch (constant->type) {
        case INTEGER_CONSTANT:
            return type == VAR_INT;
        case BOOLEAN_CONSTANT:
            return type == VAR_BOOL;
        case RYTHM_CONSTANT:
        case TONE_CONSTANT:
        default:
            return false;
    }
}

static boolean validate_return_line(ReturnLine *ptr) {
    switch (ptr->type) {
        case VARIABLE_NAME_RETURN:
            return validate_variable_type((VariableName *) ptr->value, VAR_MELODY);
        case MUSIC_TYPE_DEFINITION_RETURN:
            return ((MusicTypeDefinition *) ptr->value)->type == MELODY_DEFINITION;
        default:
            return false;
    }
}

static boolean validate_add_note(AddNote *ptr) {
    if (!validate_variable_type(ptr->melody, VAR_MELODY)) {
        return false;
    }
    if (!validate_variable_type(ptr->melody, VAR_NOTE)) {
        return false;
    }
    return true;
}

static boolean validate_type_definition(TypeDefinition *ptr) {
    VariableType type;
    switch (ptr->type) {
        case BOOLEAN_DEFINITION:
            type = VAR_BOOL;
            break;
        case INTEGER_DEFINITION:
            type = VAR_INT;
            break;
    }
    return add_symbol(peek(&stack), ptr->name->name, type);
}

static boolean validate_music_type_definition(MusicTypeDefinition *ptr) {
    VariableType type;
    switch (ptr->type) {
        case MELODY_DEFINITION:
            type = VAR_MELODY;
            break;
        case NOTE_DEFINITION:
            type = VAR_NOTE;
            break;
    }
    return add_symbol(peek(&stack), ptr->name->name, type);
}

static boolean validate_block(Block *block) {
    if (validate_sentence(block->sentence) == false) {
        return false;
    }
    return validate_block(block->block);
}

boolean validate_semantics(Program *program) {
    init_stack(&stack);
    push(&stack);
    boolean ret = validate_block(program->block);
    pop(&stack);
    return ret;
}
