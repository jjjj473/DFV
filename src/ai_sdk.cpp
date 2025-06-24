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

std::string AIClientCPP::chat(const std::string &prompt)
{
    char *resp = NULL;
    if (ai_client_send_prompt(client_, prompt.c_str(), &resp) == 0 && resp) {
        std::string result(resp);
        free(resp);
        return result;
    }
    return {};
}
