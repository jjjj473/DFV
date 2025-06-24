#ifndef AI_SDK_HPP
#define AI_SDK_HPP

#include <string>
#include "ai_sdk.h"

class AIClientCPP {
public:
    AIClientCPP(const std::string &api_key, const std::string &base_url = "https://api.openai.com/v1");
    ~AIClientCPP();

    void setSystem(int index);
    void setBaseUrl(int index, const std::string &base_url);
    void setApiKey(int index, const std::string &api_key);
    std::string getBaseUrl(int index) const;
    std::string getApiKey(int index) const;
    std::string lastError() const;
    void clearError();
    std::string chat(const std::string &prompt, int system_index = 0);
    AIClient* getClient() const { return client_; }

private:
    AIClient *client_;
};

#endif // AI_SDK_HPP
