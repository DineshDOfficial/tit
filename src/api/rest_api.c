#include <microhttpd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <kvstore.h>

#define PORT 8888

// Simple response handler
static enum MHD_Result send_response(struct MHD_Connection *connection, const char *message, int status_code)
{
    struct MHD_Response *response;
    enum MHD_Result ret;

    response = MHD_create_response_from_buffer(strlen(message), (void *)message, MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, status_code, response);
    MHD_destroy_response(response);

    return ret;
}

// Handle incoming requests
static enum MHD_Result request_handler(void *cls, struct MHD_Connection *connection, const char *url,
                                       const char *method, const char *version, const char *upload_data,
                                       size_t *upload_data_size, void **con_cls)
{
    const char *response_message;

    // Example: handling database creation
    if (strcmp(url, "/create-db") == 0 && strcmp(method, "POST") == 0)
    {
        // Create a new table (in-memory for now, but will persist)
        KVStore *store = kv_store_init(100); // Initialize with capacity 100
        kv_store_save(store, "database.kv"); // Save the new table to disk

        response_message = "Database created.";
        return send_response(connection, response_message, MHD_HTTP_OK);
    }

    // Example: handling key-value store retrieval
    if (strncmp(url, "/get/", 5) == 0 && strcmp(method, "GET") == 0)
    {
        const char *key = url + 5;                          // Get the key from URL
        KVStore *store = kv_store_load("database.kv", 100); // Load the KV store from disk
        const char *value = kv_store_get(store, key);

        if (value)
        {
            return send_response(connection, value, MHD_HTTP_OK);
        }
        else
        {
            response_message = "Key not found.";
            return send_response(connection, response_message, MHD_HTTP_NOT_FOUND);
        }
    }

    // Handle POST request to set a key-value pair
    if (strcmp(url, "/set") == 0 && strcmp(method, "POST") == 0)
    {
        // Parse the key and value from upload_data
        char key[256], value[1024];
        sscanf(upload_data, "key=%s&value=%s", key, value);

        // Load the store, set the value, and save it
        KVStore *store = kv_store_load("database.kv", 100);
        kv_store_set(store, key, value);
        kv_store_save(store, "database.kv");

        response_message = "Key-Value pair set successfully.";
        return send_response(connection, response_message, MHD_HTTP_OK);
    }

    // Handle DELETE request to remove a key-value pair
    if (strncmp(url, "/delete/", 8) == 0 && strcmp(method, "DELETE") == 0)
    {
        const char *key = url + 8;

        KVStore *store = kv_store_load("database.kv", 100);
        kv_store_delete(store, key);
        kv_store_save(store, "database.kv");

        response_message = "Key-Value pair deleted.";
        return send_response(connection, response_message, MHD_HTTP_OK);
    }

    response_message = "Invalid Request.";
    return send_response(connection, response_message, MHD_HTTP_BAD_REQUEST);
}

// Start the server
void start_rest_api()
{
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &request_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
    {
        fprintf(stderr, "Error starting REST API.\n");
        return;
    }

    printf("REST API running on port %d...\n", PORT);

    // Wait indefinitely, the server will keep running until terminated
    getchar();

    MHD_stop_daemon(daemon);
}
