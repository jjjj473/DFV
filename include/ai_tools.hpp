#ifndef AI_TOOLS_HPP
#define AI_TOOLS_HPP

#include <string>
#include "ai_tools.h"

class AIToolsCPP {
public:
    explicit AIToolsCPP(AIClient *client) : client_(client) {}

    std::string summarizeText(const std::string &text, int system = 0);
    std::string translateToEnglish(const std::string &text, int system = 0);
    std::string expandText(const std::string &text, int system = 0);
    std::string classifySentiment(const std::string &text, int system = 0);
    std::string generateOutline(const std::string &text, int system = 0);
    std::string generateCode(const std::string &request, int system = 0);
    std::string explainCode(const std::string &code, int system = 0);
    std::string refactorCode(const std::string &code, int system = 0);
    std::string generateImage(const std::string &description, int system = 0);
    std::string describeImage(const std::string &description, int system = 0);
    std::string extractTextFromPdf(const std::string &text, int system = 0);
    std::string summarizePdf(const std::string &text, int system = 0);
    std::string answerQuestionFromPdf(const std::string &text, const std::string &question, int system = 0);

private:
    AIClient *client_;
};

#endif // AI_TOOLS_HPP
