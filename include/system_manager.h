#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ai_sdk.h"

int ai_count_available_systems(const AIClient *client);
int ai_next_available_system(const AIClient *client, int current);
void ai_cycle_system(AIClient *client);

#ifdef __cplusplus
}
#endif

#endif // SYSTEM_MANAGER_H
