#ifndef AI_SDK_H
#define AI_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AIClient AIClient;

#define AI_MAX_SYSTEMS 13

AIClient *ai_client_create(const char *api_key, const char *base_url);
void ai_client_destroy(AIClient *client);

void ai_client_set_system(AIClient *client, int index);
int ai_client_send_prompt_system(AIClient *client, int index, const char *prompt, char **response);

int ai_client_send_prompt(AIClient *client, const char *prompt, char **response);

void ai_client_set_base_url(AIClient *client, int index, const char *base_url);
void ai_client_set_api_key(AIClient *client, int index, const char *api_key);

#ifdef __cplusplus
}
#endif

#endif // AI_SDK_H
