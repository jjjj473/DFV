#include "ai_sdk.hpp"
#include "system_manager.h"
#include "ai_tools.hpp"
#include <iostream>
#include <cstdlib>

int main() {
    const char *api_key = std::getenv("AI_API_KEY_1");
    if (!api_key) api_key = std::getenv("OPENAI_API_KEY");
    if (!api_key) {
        ai_stop_on_error("Please set AI_API_KEY_1 or OPENAI_API_KEY environment variable");
    }
    AIClientCPP client(api_key);
    if (const char* url = std::getenv("AI_API_URL_1")) {
        client.setBaseUrl(0, url);
    } else if (const char* url2 = std::getenv("OPENAI_API_URL")) {
        client.setBaseUrl(0, url2);
    }
    std::cout << "System 0 URL: " << client.getBaseUrl(0) << std::endl;
    std::cout << "Configured systems: " << ai_count_available_systems(client.getClient()) << std::endl;
    std::string response = client.chat("Hello from C++", 0);
    if (!response.empty()) {
        std::cout << "AI: " << response << std::endl;
    } else {
        std::cerr << "API call failed: " << client.lastError() << std::endl;
    }

    char *summary = NULL;
    ai_tool_summarize_text(client.getClient(), "This is a long piece of text that needs summarising.", 0, &summary);
    if (summary) {
        std::cout << "Summary: " << summary << std::endl;
        free(summary);
    }
    AIToolsCPP tools(client.getClient());
    std::string fixed = tools.fixGrammar("This sentence are bad.");
    std::cout << "Fixed: " << fixed << std::endl;

    if (const char* gkey = std::getenv("GEMINI_API_KEY")) {
        if (const char* gurl = std::getenv("GEMINI_API_URL"))
            client.setBaseUrl(1, gurl);
        client.setApiKey(1, gkey);
        std::string gresp = client.chat("Hello Gemini", 1);
        if (!gresp.empty())
            std::cout << "Gemini: " << gresp << std::endl;
        else
            std::cerr << "Gemini call failed: " << client.lastError() << std::endl;
    }
    return 0;
}
