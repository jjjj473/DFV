#include "ai_sdk.hpp"
#include <iostream>
#include <cstdlib>

int main() {
    const char *api_key = std::getenv("AI_API_KEY_1");
    if (!api_key) {
        std::cerr << "Please set AI_API_KEY_1 environment variable" << std::endl;
        return 1;
    }
    AIClientCPP client(api_key);
    std::string response = client.chat("Hello from C++", 0);
    std::cout << "AI: " << response << std::endl;
    return 0;
}
