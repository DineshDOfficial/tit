#include <stdio.h>
#include "core/storage.h"

int main() {
    StorageContext ctx;

    // Initialize both storage paradigms
    kv_init(&ctx);
    relational_init(&ctx);

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
