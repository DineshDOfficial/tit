#include <stdio.h>
#include <microhttpd.h>

enum MHD_Result send_response(struct MHD_Connection *connection, const char *message, int status_code);

const char *html_form = "<html><body>"
                        "<form action='/set' method='POST'>"
                        "Key: <input type='text' name='key'><br>"
                        "Value: <input type='text' name='value'><br>"
                        "<input type='submit' value='Store'>"
                        "</form>"
                        "</body></html>";

// Serve the web UI
static enum MHD_Result web_request_handler(void *cls, struct MHD_Connection *connection, const char *url,
                                           const char *method, const char *version, const char *upload_data,
                                           size_t *upload_data_size, void **con_cls)
{
    return send_response(connection, html_form, MHD_HTTP_OK);
}

// Start the web UI
void start_web_ui()
{
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8080, NULL, NULL, &web_request_handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
    {
        fprintf(stderr, "Error starting Web UI.\n");
        return;
    }

    printf("Web UI running on port 8080...\n");

    getchar();

    MHD_stop_daemon(daemon);
}
