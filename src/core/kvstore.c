#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_KEY_SIZE 256
#define MAX_VALUE_SIZE 1024

// Key-Value pair structure
typedef struct {
    char key[MAX_KEY_SIZE];
    char value[MAX_VALUE_SIZE];
} KeyValuePair;

// Simple in-memory hash map (array of key-value pairs)
typedef struct {
    KeyValuePair *pairs;
    size_t size;
    size_t capacity;
} KVStore;

// Function to initialize a new key-value store
KVStore* kv_store_init(size_t capacity) {
    KVStore *store = (KVStore*)malloc(sizeof(KVStore));
    store->pairs = (KeyValuePair*)malloc(sizeof(KeyValuePair) * capacity);
    store->size = 0;
    store->capacity = capacity;
    return store;
}

// Function to create or update a key-value pair
void kv_store_set(KVStore *store, const char *key, const char *value) {
    for (size_t i = 0; i < store->size; ++i) {
        if (strcmp(store->pairs[i].key, key) == 0) {
            strcpy(store->pairs[i].value, value);
            return;
        }
    }
    if (store->size < store->capacity) {
        strcpy(store->pairs[store->size].key, key);
        strcpy(store->pairs[store->size].value, value);
        store->size++;
    } else {
        printf("Store is full.\n");
    }
}

// Function to retrieve a value by key
const char* kv_store_get(KVStore *store, const char *key) {
    for (size_t i = 0; i < store->size; ++i) {
        if (strcmp(store->pairs[i].key, key) == 0) {
            return store->pairs[i].value;
        }
    }
    return NULL;
}

// Function to delete a key-value pair
void kv_store_delete(KVStore *store, const char *key) {
    for (size_t i = 0; i < store->size; ++i) {
        if (strcmp(store->pairs[i].key, key) == 0) {
            for (size_t j = i; j < store->size - 1; ++j) {
                store->pairs[j] = store->pairs[j + 1];
            }
            store->size--;
            return;
        }
    }
}

// Function to save the key-value store to disk
void kv_store_save(KVStore *store, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Failed to open file");
        return;
    }
    for (size_t i = 0; i < store->size; ++i) {
        fprintf(file, "%s=%s\n", store->pairs[i].key, store->pairs[i].value);
    }
    fclose(file);
}

// Function to load the key-value store from disk
KVStore* kv_store_load(const char *filename, size_t capacity) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Failed to open file");
        return NULL;
    }
    KVStore *store = kv_store_init(capacity);
    char buffer[MAX_KEY_SIZE + MAX_VALUE_SIZE + 2]; // 2 extra for '=' and '\n'
    while (fgets(buffer, sizeof(buffer), file)) {
        char *key = strtok(buffer, "=");
        char *value = strtok(NULL, "\n");
        if (key && value) {
            kv_store_set(store, key, value);
        }
    }
    fclose(file);
    return store;
}
