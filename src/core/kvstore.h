#ifndef KVSTORE_H
#define KVSTORE_H

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
KVStore* kv_store_init(size_t capacity);

// Function to create or update a key-value pair
void kv_store_set(KVStore *store, const char *key, const char *value);

// Function to retrieve a value by key
const char* kv_store_get(KVStore *store, const char *key);

// Function to delete a key-value pair
void kv_store_delete(KVStore *store, const char *key);

// Function to save the key-value store to disk
void kv_store_save(KVStore *store, const char *filename);

// Function to load the key-value store from disk
KVStore* kv_store_load(const char *filename, size_t capacity);

#endif // KVSTORE_H
