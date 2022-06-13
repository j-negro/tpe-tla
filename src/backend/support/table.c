#include "shared.h"
#include <string.h>
#include <stdlib.h>
#include "logger.h"

void init_table(Table *table) {
    table->size = 0;
}

static boolean symbol_already_exists(Table *table, char *name) {
    int i;
    for (i = 0; i < table->size; i++) {
        if (strcmp(table->symbols[i].name, name) == 0) {
            LogDebug("Symbol %s already exists", name);
            return true;
        }
    }
    return false;
}

boolean add_symbol(Table *table, char *name, VariableType type) {
    LogDebug("add_symbol(%s, %d)", name, type);
    if (table->size == MAX_TABLE || symbol_already_exists(table, name)) {
        LogDebug("Table is full or symbol already exists");
        return false;
    }
    Symbol symbol;
    symbol.name = name;
    symbol.type = type;
    table->symbols[table->size] = symbol;
    table->size++;
    return true;
}

static VariableType find_symbol(Table *table, char *name) {
    for (int i = 0; i < table->size; i++) {
        if (strcmp(table->symbols[i].name, name) == 0) {
            return table->symbols[i].type;
        }
    }
    return -1;
}

VariableType find_symbol_in_stack(Stack *stack, char *name) {
    LogDebug("find_symbol_in_stack(%s)", name);
    for (int i = stack->current; i >= 0; i--) {
        VariableType type = find_symbol(stack->array[i], name);
        if (type != -1) {
            LogDebug("Symbol %s found in stack", name);
            return type;
        }
    }
    LogDebug("find_symbol_in_stack(%s) FAILED", name);
    return -1;
}

void init_stack(Stack *stack) {
    stack->current = -1;
    stack->itemCount = 0;
}

Table *peek(Stack *stack) {
    return stack->array[stack->current];
}

boolean push(Stack *stack) {
    if(stack->itemCount != MAX_TABLE) {
        stack->current++;
        stack->array[stack->current] = malloc(sizeof(Table));
        if (stack->array[stack->current] == NULL) {
            LogError("Error al reservar memoria");
            return false;
        }
        init_table(stack->array[stack->current]);
        stack->itemCount++;
        return true;
    }
    return false;
}

boolean pop(Stack *stack) {
    if (stack->itemCount > 0) {
        free(stack->array[stack->current--]);
        stack->itemCount--;
        return true;
    }
    return false;
}