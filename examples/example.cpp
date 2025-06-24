#include "ai_sdk.hpp"
#include <iostream>
#include <cstdlib>

int main() {
    const char *api_key = std::getenv("AI_API_KEY_1");
    if (!api_key) api_key = std::getenv("OPENAI_API_KEY");
    if (!api_key) {
        std::cerr << "Please set AI_API_KEY_1 or OPENAI_API_KEY environment variable" << std::endl;
        return 1;
    }
    AIClientCPP client(api_key);
    if (const char* url = std::getenv("AI_API_URL_1")) {
        client.setBaseUrl(0, url);
    } else if (const char* url2 = std::getenv("OPENAI_API_URL")) {
        client.setBaseUrl(0, url2);
    }
    std::string response = client.chat("Hello from C++", 0);
    std::cout << "AI: " << response << std::endl;

    if (const char* gkey = std::getenv("GEMINI_API_KEY")) {
        if (const char* gurl = std::getenv("GEMINI_API_URL"))
            client.setBaseUrl(1, gurl);
        client.setApiKey(1, gkey);
        std::string gresp = client.chat("Hello Gemini", 1);
        std::cout << "Gemini: " << gresp << std::endl;
    }
    return 0;
}
