#include "ai_tools.hpp"
#include <cstdlib>

std::string AIToolsCPP::summarizeText(const std::string &text, int system) {
    char *resp = NULL;
    ai_tool_summarize_text(client_, text.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::translateToEnglish(const std::string &text, int system) {
    char *resp = NULL;
    ai_tool_translate_to_english(client_, text.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::expandText(const std::string &text, int system) {
    char *resp = NULL;
    ai_tool_expand_text(client_, text.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::classifySentiment(const std::string &text, int system) {
    char *resp = NULL;
    ai_tool_classify_sentiment(client_, text.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::generateOutline(const std::string &text, int system) {
    char *resp = NULL;
    ai_tool_generate_outline(client_, text.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::generateCode(const std::string &request, int system) {
    char *resp = NULL;
    ai_tool_generate_code(client_, request.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::explainCode(const std::string &code, int system) {
    char *resp = NULL;
    ai_tool_explain_code(client_, code.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::refactorCode(const std::string &code, int system) {
    char *resp = NULL;
    ai_tool_refactor_code(client_, code.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::generateImage(const std::string &desc, int system) {
    char *resp = NULL;
    ai_tool_generate_image(client_, desc.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::describeImage(const std::string &desc, int system) {
    char *resp = NULL;
    ai_tool_describe_image(client_, desc.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::extractTextFromPdf(const std::string &txt, int system) {
    char *resp = NULL;
    ai_tool_extract_text_from_pdf(client_, txt.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::summarizePdf(const std::string &txt, int system) {
    char *resp = NULL;
    ai_tool_summarize_pdf(client_, txt.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::answerQuestionFromPdf(const std::string &txt, const std::string &q, int system) {
    char *resp = NULL;
    ai_tool_answer_question_from_pdf(client_, txt.c_str(), q.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::fixGrammar(const std::string &text, int system) {
    char *resp = NULL;
    ai_tool_fix_grammar(client_, text.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::listKeyPoints(const std::string &text, int system) {
    char *resp = NULL;
    ai_tool_list_key_points(client_, text.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::summarizeCode(const std::string &code, int system) {
    char *resp = NULL;
    ai_tool_summarize_code(client_, code.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::documentCode(const std::string &code, int system) {
    char *resp = NULL;
    ai_tool_document_code(client_, code.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::optimizeCode(const std::string &code, int system) {
    char *resp = NULL;
    ai_tool_optimize_code(client_, code.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::generateUnitTests(const std::string &code, int system) {
    char *resp = NULL;
    ai_tool_generate_unit_tests(client_, code.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::captionImage(const std::string &desc, int system) {
    char *resp = NULL;
    ai_tool_caption_image(client_, desc.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::thumbnailPrompt(const std::string &desc, int system) {
    char *resp = NULL;
    ai_tool_thumbnail_prompt(client_, desc.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::extractKeywords(const std::string &text, int system) {
    char *resp = NULL;
    ai_tool_extract_keywords(client_, text.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::translateFromEnglish(const std::string &text, int system) {
    char *resp = NULL;
    ai_tool_translate_from_english(client_, text.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::detectLanguage(const std::string &text, int system) {
    char *resp = NULL;
    ai_tool_detect_language(client_, text.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::continueText(const std::string &text, int system) {
    char *resp = NULL;
    ai_tool_continue_text(client_, text.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::generateTitle(const std::string &text, int system) {
    char *resp = NULL;
    ai_tool_generate_title(client_, text.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::generateMetaDescription(const std::string &text, int system) {
    char *resp = NULL;
    ai_tool_generate_meta_description(client_, text.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}

std::string AIToolsCPP::outlinePdfSections(const std::string &text, int system) {
    char *resp = NULL;
    ai_tool_outline_pdf_sections(client_, text.c_str(), system, &resp);
    std::string out = resp ? resp : "";
    free(resp);
    return out;
}
