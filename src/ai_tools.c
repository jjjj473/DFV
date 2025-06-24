#include "ai_tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int send_prompt(AIClient *c, int sys, char **resp, const char *fmt, const char *a, const char *b) {
    size_t len = strlen(fmt) + strlen(a) + (b ? strlen(b) : 0) + 1;
    char *prompt = (char*)malloc(len);
    if (!prompt) return 1;
    if (b)
        sprintf(prompt, fmt, a, b);
    else
        sprintf(prompt, fmt, a);
    int r = ai_client_send_prompt_system(c, sys, prompt, resp);
    free(prompt);
    return r;
}

int ai_tool_summarize_text(AIClient *c, const char *text, int system, char **response) {
    const char *fmt = "Summarize the following text:\n%s";
    return send_prompt(c, system, response, fmt, text, NULL);
}

int ai_tool_translate_to_english(AIClient *c, const char *text, int system, char **response) {
    const char *fmt = "Translate the following text to English:\n%s";
    return send_prompt(c, system, response, fmt, text, NULL);
}

int ai_tool_expand_text(AIClient *c, const char *text, int system, char **response) {
    const char *fmt = "Expand on the following text:\n%s";
    return send_prompt(c, system, response, fmt, text, NULL);
}

int ai_tool_classify_sentiment(AIClient *c, const char *text, int system, char **response) {
    const char *fmt = "Classify the sentiment of the following text as positive, negative, or neutral:\n%s";
    return send_prompt(c, system, response, fmt, text, NULL);
}

int ai_tool_generate_outline(AIClient *c, const char *text, int system, char **response) {
    const char *fmt = "Create an outline for a document based on the following topic or text:\n%s";
    return send_prompt(c, system, response, fmt, text, NULL);
}

int ai_tool_generate_code(AIClient *c, const char *request, int system, char **response) {
    const char *fmt = "Write code for the following request:\n%s";
    return send_prompt(c, system, response, fmt, request, NULL);
}

int ai_tool_explain_code(AIClient *c, const char *code, int system, char **response) {
    const char *fmt = "Explain what the following code does:\n%s";
    return send_prompt(c, system, response, fmt, code, NULL);
}

int ai_tool_refactor_code(AIClient *c, const char *code, int system, char **response) {
    const char *fmt = "Refactor the following code to improve readability:\n%s";
    return send_prompt(c, system, response, fmt, code, NULL);
}

int ai_tool_generate_image(AIClient *c, const char *description, int system, char **response) {
    const char *fmt = "Provide a prompt to generate an image with the following description:\n%s";
    return send_prompt(c, system, response, fmt, description, NULL);
}

int ai_tool_describe_image(AIClient *c, const char *description, int system, char **response) {
    const char *fmt = "Describe the contents of the image: %s";
    return send_prompt(c, system, response, fmt, description, NULL);
}

int ai_tool_extract_text_from_pdf(AIClient *c, const char *pdf_text, int system, char **response) {
    const char *fmt = "Extract important text from the following PDF content:\n%s";
    return send_prompt(c, system, response, fmt, pdf_text, NULL);
}

int ai_tool_summarize_pdf(AIClient *c, const char *pdf_text, int system, char **response) {
    const char *fmt = "Summarize the following PDF content:\n%s";
    return send_prompt(c, system, response, fmt, pdf_text, NULL);
}

int ai_tool_answer_question_from_pdf(AIClient *c, const char *pdf_text, const char *question, int system, char **response) {
    const char *fmt = "Given the following PDF content:\n%s\nAnswer the question: %s";
    return send_prompt(c, system, response, fmt, pdf_text, question);
}

int ai_tool_fix_grammar(AIClient *c, const char *text, int system, char **response) {
    const char *fmt = "Correct any grammar mistakes in the following text:\n%s";
    return send_prompt(c, system, response, fmt, text, NULL);
}

int ai_tool_list_key_points(AIClient *c, const char *text, int system, char **response) {
    const char *fmt = "List the key points from the following text:\n%s";
    return send_prompt(c, system, response, fmt, text, NULL);
}

int ai_tool_summarize_code(AIClient *c, const char *code, int system, char **response) {
    const char *fmt = "Summarize what the following code does:\n%s";
    return send_prompt(c, system, response, fmt, code, NULL);
}

int ai_tool_document_code(AIClient *c, const char *code, int system, char **response) {
    const char *fmt = "Add documentation comments to the following code:\n%s";
    return send_prompt(c, system, response, fmt, code, NULL);
}

int ai_tool_optimize_code(AIClient *c, const char *code, int system, char **response) {
    const char *fmt = "Optimize the following code for performance:\n%s";
    return send_prompt(c, system, response, fmt, code, NULL);
}

int ai_tool_generate_unit_tests(AIClient *c, const char *code, int system, char **response) {
    const char *fmt = "Generate unit tests for the following code:\n%s";
    return send_prompt(c, system, response, fmt, code, NULL);
}

int ai_tool_caption_image(AIClient *c, const char *description, int system, char **response) {
    const char *fmt = "Create a caption for this image description:\n%s";
    return send_prompt(c, system, response, fmt, description, NULL);
}

int ai_tool_thumbnail_prompt(AIClient *c, const char *description, int system, char **response) {
    const char *fmt = "Provide instructions to create a thumbnail image for:\n%s";
    return send_prompt(c, system, response, fmt, description, NULL);
}

int ai_tool_extract_keywords(AIClient *c, const char *text, int system, char **response) {
    const char *fmt = "Extract important keywords from the following text:\n%s";
    return send_prompt(c, system, response, fmt, text, NULL);
}

int ai_tool_translate_from_english(AIClient *c, const char *text, int system, char **response) {
    const char *fmt = "Translate the following English text to another language:\n%s";
    return send_prompt(c, system, response, fmt, text, NULL);
}

int ai_tool_detect_language(AIClient *c, const char *text, int system, char **response) {
    const char *fmt = "Detect the language of the following text:\n%s";
    return send_prompt(c, system, response, fmt, text, NULL);
}

int ai_tool_continue_text(AIClient *c, const char *text, int system, char **response) {
    const char *fmt = "Continue writing from the following text:\n%s";
    return send_prompt(c, system, response, fmt, text, NULL);
}

int ai_tool_generate_title(AIClient *c, const char *text, int system, char **response) {
    const char *fmt = "Generate a short title for the following text:\n%s";
    return send_prompt(c, system, response, fmt, text, NULL);
}

int ai_tool_generate_meta_description(AIClient *c, const char *text, int system, char **response) {
    const char *fmt = "Write a meta description for the following text:\n%s";
    return send_prompt(c, system, response, fmt, text, NULL);
}

int ai_tool_outline_pdf_sections(AIClient *c, const char *pdf_text, int system, char **response) {
    const char *fmt = "Provide an outline of the main sections in this PDF content:\n%s";
    return send_prompt(c, system, response, fmt, pdf_text, NULL);
}
