#ifndef AI_SDK_HPP
#define AI_SDK_HPP

#include <string>
#include "ai_sdk.h"

class AIClientCPP {
public:
    AIClientCPP(const std::string &api_key, const std::string &base_url = "https://api.openai.com/v1");
    ~AIClientCPP();
    std::string chat(const std::string &prompt);
private:
    AIClient *client_;
};

#endif // AI_SDK_HPP
