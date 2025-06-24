#include "ai_sdk.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *api_key = getenv("AI_API_KEY_1");
    if (!api_key) {
        fprintf(stderr, "Please set AI_API_KEY_1 environment variable\n");
        return 1;
    }
    AIClient *client = ai_client_create(api_key, "https://api.openai.com/v1");
    /* Example of overriding the base URL for system 0 at runtime */
    const char *custom_url = getenv("AI_API_URL_1");
    if (custom_url) {
        ai_client_set_base_url(client, 0, custom_url);
    }
    char *response = NULL;
    if (ai_client_send_prompt_system(client, 0, "Hello from C", &response) == 0) {
        printf("AI: %s\n", response);
        free(response);
    } else {
        fprintf(stderr, "API call failed\n");
    }
    ai_client_destroy(client);
    return 0;
}
