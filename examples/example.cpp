#include "ai_sdk.hpp"
#include <iostream>
#include <cstdlib>

int main() {
    const char *api_key = std::getenv("OPENAI_API_KEY");
    if (!api_key) {
        std::cerr << "Please set OPENAI_API_KEY environment variable" << std::endl;
        return 1;
    }
    AIClientCPP client(api_key);
    std::string response = client.chat("Hello from C++");
    std::cout << "AI: " << response << std::endl;
    return 0;
}
