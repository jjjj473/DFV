#ifndef AI_SDK_H
#define AI_SDK_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct AIClient AIClient;

AIClient *ai_client_create(const char *api_key, const char *base_url);
void ai_client_destroy(AIClient *client);

int ai_client_send_prompt(AIClient *client, const char *prompt, char **response);

#ifdef __cplusplus
}
#endif

#endif // AI_SDK_H
