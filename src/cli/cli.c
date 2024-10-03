#include <stdio.h>
#include <string.h>
#include "core/storage.h"

void display_menu() {
    printf("Select Storage Paradigm:\n");
    printf("1. Key-Value\n");
    printf("2. Relational\n");
    printf("3. Exit\n");
}

void handle_kv_commands(StorageContext* ctx) {
    char command[256];
    printf("KV Mode: Enter command (create/read/update/delete): ");
    while (1) {
        fgets(command, sizeof(command), stdin);
        if (strncmp(command, "exit", 4) == 0) break;

        // Handle KV commands
        // Use strtok to parse command
    }
}

void handle_relational_commands(StorageContext* ctx) {
    char command[256];
    printf("Relational Mode: Enter command (create/insert/select/delete): ");
    while (1) {
        fgets(command, sizeof(command), stdin);
        if (strncmp(command, "exit", 4) == 0) break;

        // Handle relational commands
    }
}

int main() {
    StorageContext ctx;

    while (1) {
        display_menu();
        int choice;
        scanf("%d", &choice);
        getchar(); // consume newline

        switch (choice) {
            case 1:
                handle_kv_commands(&ctx);
                break;
            case 2:
                handle_relational_commands(&ctx);
                break;
            case 3:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid option, try again.\n");
        }
    }
    return 0;
}
#include <stdio.h>
#include <string.h>
#include "storage.h"

void display_menu() {
    printf("Select Storage Paradigm:\n");
    printf("1. Key-Value\n");
    printf("2. Relational\n");
    printf("3. Exit\n");
}

void handle_kv_commands(StorageContext* ctx) {
    char command[256];
    char key[128], value[128];

    while (1) {
        printf("KV Mode: Enter command (create/read/update/delete/exit): ");
        fgets(command, sizeof(command), stdin);
        
        if (strncmp(command, "exit", 4) == 0) break;

        sscanf(command, "%s %s %s", command, key, value);

        if (strcmp(command, "create") == 0) {
            kv_create(ctx, key, value);
        } else if (strcmp(command, "read") == 0) {
            char* result = kv_read(ctx, key);
            if (result) {
                printf("Value: %s\n", result);
            } else {
                printf("Key not found.\n");
            }
        } else if (strcmp(command, "update") == 0) {
            kv_update(ctx, key, value);
        } else if (strcmp(command, "delete") == 0) {
            kv_delete(ctx, key);
        } else {
            printf("Invalid KV command.\n");
        }
    }
}

void handle_relational_commands(StorageContext* ctx) {
    char command[256];
    char table_name[128], values[128];

    while (1) {
        printf("Relational Mode: Enter command (create/insert/select/delete/exit): ");
        fgets(command, sizeof(command), stdin);
        
        if (strncmp(command, "exit", 4) == 0) break;

        sscanf(command, "%s %s %[^\n]", command, table_name, values);

        if (strcmp(command, "create") == 0) {
            relational_create(ctx, table_name);
        } else if (strcmp(command, "insert") == 0) {
            relational_insert(ctx, table_name, values);
        } else if (strcmp(command, "select") == 0) {
            relational_select(ctx, table_name);
        } else {
            printf("Invalid relational command.\n");
        }
    }
}
