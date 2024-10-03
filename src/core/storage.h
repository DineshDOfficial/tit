#ifndef STORAGE_H
#define STORAGE_H

typedef struct StorageContext {
    // Add any necessary context fields
} StorageContext;

void kv_create(StorageContext* ctx, const char* key, const char* value);
char* kv_read(StorageContext* ctx, const char* key);
void kv_update(StorageContext* ctx, const char* key, const char* value);
void kv_delete(StorageContext* ctx, const char* key);
void kv_init(StorageContext* ctx);

void relational_create(StorageContext* ctx, const char* table_name);
void relational_insert(StorageContext* ctx, const char* table_name, const char* values);
void relational_select(StorageContext* ctx, const char* table_name);
void relational_delete(StorageContext* ctx, const char* table_name);
void relational_init(StorageContext* ctx);

#endif // STORAGE_H
