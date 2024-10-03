#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"

#define RELATIONAL_STORE_FILE "data/relational_store.txt"

static void save_table_to_file(const char* table_name, const char* values) {
    FILE *file = fopen(RELATIONAL_STORE_FILE, "a");
    if (file) {
        fprintf(file, "%s:%s\n", table_name, values);
        fclose(file);
    }
}

static void load_tables_from_file(StorageContext* ctx) {
    FILE *file = fopen(RELATIONAL_STORE_FILE, "r");
    if (file) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            char* table_name = strtok(line, ":");
            char* values = strtok(NULL, "\n");
            if (table_name && values) {
                relational_insert(ctx, table_name, values);
            }
        }
        fclose(file);
    }
}

void relational_create(StorageContext* ctx, const char* table_name) {
    // For simplicity, table creation can be a no-op here; 
    // it’s just about ensuring the table is referenced in future inserts
}

void relational_insert(StorageContext* ctx, const char* table_name, const char* values) {
    save_table_to_file(table_name, values);
}

void relational_select(StorageContext* ctx, const char* table_name) {
    FILE *file = fopen(RELATIONAL_STORE_FILE, "r");
    if (file) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            char* tn = strtok(line, ":");
            char* v = strtok(NULL, "\n");
            if (strcmp(tn, table_name) == 0) {
                printf("Table %s: %s\n", tn, v);
            }
        }
        fclose(file);
    }
}

void relational_delete(StorageContext* ctx, const char* table_name) {
    // Implement delete logic (optional)
}

void relational_init(StorageContext* ctx) {
    load_tables_from_file(ctx);
}
