#include "shared.h"
#include <string.h>

void init_table(Table *table) {
    table->size = 0;
}

boolean add_symbol(Table *table, char *name, VariableType type) {
    if (table->size == MAX_TABLE) {
        return false;
    }
    Symbol symbol;
    symbol.name = name;
    symbol.type = type;
    table->symbols[table->size] = symbol;
    table->size++;
    return true;
}

VariableType find_symbol(Table *table, char *name) {
    for (int i = 0; i < table->size; i++) {
        if (strcmp(table->symbols[i].name, name) == 0) {
            return table->symbols[i].type;
        }
    }
    return -1;
}