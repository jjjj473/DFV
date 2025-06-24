#include <stdio.h>
#include <stdlib.h>
#include "ai_sdk.h"

void ai_stop_on_error(const char *msg) {
    if (!msg) msg = "Unknown error";
    fprintf(stderr, "%s\n", msg);
    exit(1);
}
