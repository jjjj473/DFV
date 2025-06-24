#ifndef AI_TOOLS_H
#define AI_TOOLS_H

#ifdef __cplusplus
extern "C" {
#endif

#include "ai_sdk.h"

int ai_tool_summarize_text(AIClient *c, const char *text, int system, char **response);
int ai_tool_translate_to_english(AIClient *c, const char *text, int system, char **response);
int ai_tool_expand_text(AIClient *c, const char *text, int system, char **response);
int ai_tool_classify_sentiment(AIClient *c, const char *text, int system, char **response);
int ai_tool_generate_outline(AIClient *c, const char *text, int system, char **response);
int ai_tool_generate_code(AIClient *c, const char *request, int system, char **response);
int ai_tool_explain_code(AIClient *c, const char *code, int system, char **response);
int ai_tool_refactor_code(AIClient *c, const char *code, int system, char **response);
int ai_tool_generate_image(AIClient *c, const char *description, int system, char **response);
int ai_tool_describe_image(AIClient *c, const char *description, int system, char **response);
int ai_tool_extract_text_from_pdf(AIClient *c, const char *pdf_text, int system, char **response);
int ai_tool_summarize_pdf(AIClient *c, const char *pdf_text, int system, char **response);
int ai_tool_answer_question_from_pdf(AIClient *c, const char *pdf_text, const char *question, int system, char **response);
int ai_tool_fix_grammar(AIClient *c, const char *text, int system, char **response);
int ai_tool_list_key_points(AIClient *c, const char *text, int system, char **response);
int ai_tool_summarize_code(AIClient *c, const char *code, int system, char **response);
int ai_tool_document_code(AIClient *c, const char *code, int system, char **response);
int ai_tool_optimize_code(AIClient *c, const char *code, int system, char **response);
int ai_tool_generate_unit_tests(AIClient *c, const char *code, int system, char **response);
int ai_tool_caption_image(AIClient *c, const char *description, int system, char **response);
int ai_tool_thumbnail_prompt(AIClient *c, const char *description, int system, char **response);
int ai_tool_extract_keywords(AIClient *c, const char *text, int system, char **response);
int ai_tool_translate_from_english(AIClient *c, const char *text, int system, char **response);
int ai_tool_detect_language(AIClient *c, const char *text, int system, char **response);
int ai_tool_continue_text(AIClient *c, const char *text, int system, char **response);
int ai_tool_generate_title(AIClient *c, const char *text, int system, char **response);
int ai_tool_generate_meta_description(AIClient *c, const char *text, int system, char **response);
int ai_tool_outline_pdf_sections(AIClient *c, const char *pdf_text, int system, char **response);

#ifdef __cplusplus
}
#endif

#endif // AI_TOOLS_H
