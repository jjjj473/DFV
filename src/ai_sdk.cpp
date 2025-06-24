#include "ai_sdk.hpp"
#include <cstdlib>

AIClientCPP::AIClientCPP(const std::string &api_key, const std::string &base_url)
{
    client_ = ai_client_create(api_key.c_str(), base_url.c_str());
}

AIClientCPP::~AIClientCPP()
{
    ai_client_destroy(client_);
}

void AIClientCPP::setSystem(int index)
{
    ai_client_set_system(client_, index);
}

void AIClientCPP::setBaseUrl(int index, const std::string &base_url)
{
    ai_client_set_base_url(client_, index, base_url.c_str());
}

void AIClientCPP::setApiKey(int index, const std::string &api_key)
{
    ai_client_set_api_key(client_, index, api_key.c_str());
}

std::string AIClientCPP::chat(const std::string &prompt, int system_index)
{
    char *resp = NULL;
    if (ai_client_send_prompt_system(client_, system_index, prompt.c_str(), &resp) == 0 && resp) {
        std::string result(resp);
        free(resp);
        return result;
    }
    return {};
}
