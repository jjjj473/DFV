#include "ai_sdk.h"
#include <curl/curl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char *my_strdup(const char *s) {
    size_t len = strlen(s) + 1;
    char *d = malloc(len);
    if (d) memcpy(d, s, len);
    return d;
}

struct AIClient {
    char *api_keys[AI_MAX_SYSTEMS];
    char *base_urls[AI_MAX_SYSTEMS];
    int current;
};

AIClient *ai_client_create(const char *api_key, const char *base_url) {
    AIClient *c = (AIClient*)malloc(sizeof(AIClient));
    if (!c) return NULL;
    for (int i = 0; i < AI_MAX_SYSTEMS; ++i) {
        char key_var[32];
        char url_var[32];
        snprintf(key_var, sizeof(key_var), "AI_API_KEY_%d", i + 1);
        snprintf(url_var, sizeof(url_var), "AI_API_URL_%d", i + 1);
        const char *key = getenv(key_var);
        const char *url = getenv(url_var);
        if (i == 0) {
            if (!key) key = api_key;
            if (!url) url = base_url ? base_url : "https://api.openai.com/v1";
        }
        c->api_keys[i] = my_strdup(key ? key : "");
        c->base_urls[i] = my_strdup(url ? url : "");
    }
    c->current = 0;
    return c;
}

void ai_client_destroy(AIClient *c) {
    if (!c) return;
    for (int i = 0; i < AI_MAX_SYSTEMS; ++i) {
        free(c->api_keys[i]);
        free(c->base_urls[i]);
    }
    free(c);
}

struct buffer {
    char *data;
    size_t size;
};

static size_t write_cb(void *ptr, size_t size, size_t nmemb, void *userdata) {
    struct buffer *buf = (struct buffer*)userdata;
    size_t total = size * nmemb;
    char *new_data = (char*)realloc(buf->data, buf->size + total + 1);
    if (!new_data) return 0;
    buf->data = new_data;
    memcpy(buf->data + buf->size, ptr, total);
    buf->size += total;
    buf->data[buf->size] = '\0';
    return total;
}

static char* build_url(const AIClient *c, int idx) {
    const char *base = c->base_urls[idx];
    if (!base || !*base) base = "https://api.openai.com/v1";
    const char *path = "/chat/completions";
    size_t len = strlen(base) + strlen(path) + 1;
    char *url = (char*)malloc(len);
    if (url) sprintf(url, "%s%s", base, path);
    return url;
}

static char* escape_json(const char *in) {
    size_t len = strlen(in);
    char *out = (char*)malloc(len * 2 + 1); // rough
    char *p = out;
    for (; *in; ++in) {
        if (*in == '"' || *in == '\\') *p++ = '\\';
        *p++ = *in;
    }
    *p = '\0';
    return out;
}

static char* build_post_data(const char *prompt) {
    const char *fmt = "{\"model\":\"gpt-3.5-turbo\",\"messages\":[{\"role\":\"user\",\"content\":\"%s\"}]}";
    char *escaped = escape_json(prompt);
    size_t len = strlen(fmt) + strlen(escaped) + 1;
    char *json = (char*)malloc(len);
    sprintf(json, fmt, escaped);
    free(escaped);
    return json;
}

int ai_client_send_prompt_system(AIClient *client, int idx, const char *prompt, char **response) {
    if (!client || !prompt || !response) return 1;
    if (idx < 0 || idx >= AI_MAX_SYSTEMS) return 1;

    CURL *curl = curl_easy_init();
    if (!curl) return 1;

    struct buffer buf = {0};

    struct curl_slist *headers = NULL;
    char auth[256];
    snprintf(auth, sizeof(auth), "Authorization: Bearer %s", client->api_keys[idx]);
    headers = curl_slist_append(headers, auth);
    headers = curl_slist_append(headers, "Content-Type: application/json");

    char *url = build_url(client, idx);
    char *post = build_post_data(prompt);

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_cb);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buf);

    CURLcode res = curl_easy_perform(curl);

    free(url);
    free(post);
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        free(buf.data);
        return 1;
    }

    char *start = strstr(buf.data, "\"content\":\"");
    if (!start) {
        *response = buf.data;
        return 0;
    }
    start += strlen("\"content\":\"");
    char *end = strchr(start, '"');
    if (!end) {
        *response = buf.data;
        return 0;
    }
    size_t len = end - start;
    char *content = (char*)malloc(len + 1);
    strncpy(content, start, len);
    content[len] = '\0';
    free(buf.data);
    *response = content;
    return 0;
}

void ai_client_set_system(AIClient *c, int index) {
    if (!c) return;
    if (index >= 0 && index < AI_MAX_SYSTEMS)
        c->current = index;
}

int ai_client_send_prompt(AIClient *client, const char *prompt, char **response) {
    if (!client) return 1;
    return ai_client_send_prompt_system(client, client->current, prompt, response);
}

void ai_client_set_base_url(AIClient *client, int index, const char *base_url) {
    if (!client || index < 0 || index >= AI_MAX_SYSTEMS) return;
    free(client->base_urls[index]);
    client->base_urls[index] = my_strdup(base_url ? base_url : "");
}

void ai_client_set_api_key(AIClient *client, int index, const char *api_key) {
    if (!client || index < 0 || index >= AI_MAX_SYSTEMS) return;
    free(client->api_keys[index]);
    client->api_keys[index] = my_strdup(api_key ? api_key : "");
}
