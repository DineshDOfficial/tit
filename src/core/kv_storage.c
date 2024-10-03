#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "storage.h"

#define KV_STORE_FILE "data/kv_store.txt"

static void save_kv_to_file(const char* key, const char* value) {
    FILE *file = fopen(KV_STORE_FILE, "a");
    if (file) {
        fprintf(file, "%s:%s\n", key, value);
        fclose(file);
    }
}

static void load_kv_from_file(StorageContext* ctx) {
    FILE *file = fopen(KV_STORE_FILE, "r");
    if (file) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            char* key = strtok(line, ":");
            char* value = strtok(NULL, "\n");
            if (key && value) {
                kv_create(ctx, key, value);
            }
        }
        fclose(file);
    }
}

void kv_create(StorageContext* ctx, const char* key, const char* value) {
    save_kv_to_file(key, value);
}

char* kv_read(StorageContext* ctx, const char* key) {
    // Read the KV store file to find the value
    FILE *file = fopen(KV_STORE_FILE, "r");
    static char value[256];  // Static to return address
    if (file) {
        char line[256];
        while (fgets(line, sizeof(line), file)) {
            char* k = strtok(line, ":");
            char* v = strtok(NULL, "\n");
            if (strcmp(k, key) == 0) {
                strncpy(value, v, sizeof(value));
                fclose(file);
                return value;
            }
        }
        fclose(file);
    }
    return NULL;  // Not found
}

void kv_update(StorageContext* ctx, const char* key, const char* value) {
    // Read all entries, update the specified key and write back
    FILE *file = fopen(KV_STORE_FILE, "r");
    FILE *temp = fopen("data/temp_kv_store.txt", "w");
    char line[256];

    if (file && temp) {
        while (fgets(line, sizeof(line), file)) {
            char* k = strtok(line, ":");
            if (strcmp(k, key) == 0) {
                fprintf(temp, "%s:%s\n", key, value);  // Update value
            } else {
                fprintf(temp, "%s", line);  // Copy original line
            }
        }
        fclose(file);
        fclose(temp);
        remove(KV_STORE_FILE);
        rename("data/temp_kv_store.txt", KV_STORE_FILE);
    }
}

void kv_delete(StorageContext* ctx, const char* key) {
    // Read all entries, skip the specified key and write back
    FILE *file = fopen(KV_STORE_FILE, "r");
    FILE *temp = fopen("data/temp_kv_store.txt", "w");
    char line[256];

    if (file && temp) {
        while (fgets(line, sizeof(line), file)) {
            char* k = strtok(line, ":");
            if (strcmp(k, key) != 0) {
                fprintf(temp, "%s", line);  // Copy original line if key does not match
            }
        }
        fclose(file);
        fclose(temp);
        remove(KV_STORE_FILE);
        rename("data/temp_kv_store.txt", KV_STORE_FILE);
    }
}

void kv_init(StorageContext* ctx) {
    load_kv_from_file(ctx);
}
