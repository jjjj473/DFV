#include "ai_sdk.h"
#include "system_manager.h"
#include "ai_tools.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *api_key = getenv("AI_API_KEY_1");
    if (!api_key) api_key = getenv("OPENAI_API_KEY");
    if (!api_key) {
        ai_stop_on_error("Please set AI_API_KEY_1 or OPENAI_API_KEY environment variable");
    }
    AIClient *client = ai_client_create(api_key, "https://api.openai.com/v1");
    /* Example of overriding the base URL for system 0 at runtime */
    const char *custom_url = getenv("AI_API_URL_1");
    if (!custom_url) custom_url = getenv("OPENAI_API_URL");
    if (custom_url) {
        ai_client_set_base_url(client, 0, custom_url);
    }
    printf("System 0 URL: %s\n", ai_client_get_base_url(client, 0));
    printf("Configured systems: %d\n", ai_count_available_systems(client));
    char *response = NULL;
    if (ai_client_send_prompt_system(client, 0, "Hello from C", &response) == 0) {
        printf("AI: %s\n", response);
        free(response);
    } else {
        fprintf(stderr, "API call failed\n");
    }

    if (ai_tool_summarize_text(client, "This is a long piece of text that needs summarising.", 0, &response) == 0 && response) {
        printf("Summary: %s\n", response);
        free(response);
    }
    if (ai_tool_fix_grammar(client, "This sentence are bad.", 0, &response) == 0 && response) {
        printf("Fixed: %s\n", response);
        free(response);
    }

    const char *gkey = getenv("GEMINI_API_KEY");
    if (gkey) {
        const char *gurl = getenv("GEMINI_API_URL");
        if (gurl)
            ai_client_set_base_url(client, 1, gurl);
        ai_client_set_api_key(client, 1, gkey);
        if (ai_client_send_prompt_system(client, 1, "Hello Gemini", &response) == 0 && response) {
            printf("Gemini: %s\n", response);
            free(response);
        }
    }
    ai_client_destroy(client);
    return 0;
}
