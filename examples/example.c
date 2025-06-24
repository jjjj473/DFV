#include "ai_sdk.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *api_key = getenv("OPENAI_API_KEY");
    if (!api_key) {
        fprintf(stderr, "Please set OPENAI_API_KEY environment variable\n");
        return 1;
    }
    AIClient *client = ai_client_create(api_key, "https://api.openai.com/v1");
    char *response = NULL;
    if (ai_client_send_prompt(client, "Hello from C", &response) == 0) {
        printf("AI: %s\n", response);
        free(response);
    } else {
        fprintf(stderr, "API call failed\n");
    }
    ai_client_destroy(client);
    return 0;
}
