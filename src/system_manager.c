#include "system_manager.h"

int ai_count_available_systems(const AIClient *client) {
    if (!client) return 0;
    int count = 0;
    for (int i = 0; i < AI_MAX_SYSTEMS; ++i) {
        const char *key = ai_client_get_api_key(client, i);
        if (key && *key)
            ++count;
    }
    return count;
}

int ai_next_available_system(const AIClient *client, int current) {
    if (!client) return current;
    for (int i = 1; i <= AI_MAX_SYSTEMS; ++i) {
        int idx = (current + i) % AI_MAX_SYSTEMS;
        const char *key = ai_client_get_api_key(client, idx);
        if (key && *key)
            return idx;
    }
    return current;
}

void ai_cycle_system(AIClient *client) {
    if (!client) return;
    int current = ai_client_get_system(client);
    int next = ai_next_available_system(client, current);
    ai_client_set_system(client, next);
}
