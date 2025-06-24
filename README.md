# AI SDK for C and C++

This repository provides a minimal SDK for building simple AI agents in C or C++
using the OpenAI API (or compatible APIs). The SDK is implemented in C with a
C++ wrapper and includes small example programs.

## Building

Requirements:

- GCC and G++
- libcurl development files

An optional helper script, `scripts/setup_platform.sh`, attempts to install
these dependencies automatically. It detects macOS, Windows or Linux
distributions and falls back to legacy packages on older systems.

Run `make` to build the static library (`libai_sdk.a`) and example programs:

```sh
make
```

This produces:

- `libai_sdk.a` – static library containing the SDK
- `example_c` – example C program
- `example_cpp` – example C++ program

Clean build artifacts with:

```sh
make clean
```

## Usage

The SDK supports up to 40 different AI systems. Provide each system's API key
and base URL via environment variables `AI_API_KEY_1` .. `AI_API_KEY_40` and
`AI_API_URL_1` .. `AI_API_URL_40`.

For convenience the library also recognises provider specific variables:

- `OPENAI_API_KEY` / `OPENAI_API_URL` (system index 0)
- `GEMINI_API_KEY` / `GEMINI_API_URL` (system index 1)
- `TOGETHER_API_KEY` / `TOGETHER_API_URL` (system index 2)
- `CLAUDE_API_KEY` / `CLAUDE_API_URL` (system index 3)

The first system defaults to OpenAI if no variables are supplied.

Set the first API key in `AI_API_KEY_1` (or `OPENAI_API_KEY`) and run one of the examples:

```sh
export AI_API_KEY_1=your-key-here
./example_c
# or
./example_cpp
```

To try the Gemini endpoint provide `GEMINI_API_KEY` (and optionally
`GEMINI_API_URL`) and pass system index `1`:

```sh
export GEMINI_API_KEY=your-gemini-key
./example_c    # will also print a Gemini response
```

Both examples send a simple prompt to the API and print the returned message
content.

Developers can link against `libai_sdk.a` and include `ai_sdk.h` or
`ai_sdk.hpp` in their projects to issue chat completion requests. Systems can be
updated at runtime using `ai_client_set_base_url()` and `ai_client_set_api_key()`
from C, or the `setBaseUrl()` and `setApiKey()` methods of the C++ wrapper.

The SDK also provides helpers to inspect the current configuration:
`ai_client_get_base_url()` and `ai_client_get_api_key()` (or `getBaseUrl()` and
`getApiKey()` in C++).

Failed API calls store a message accessible via `ai_client_last_error()` (or
`lastError()` in C++). Clear it with `ai_client_clear_error()`/`clearError()`.

### System management

`system_manager.h` offers utilities for working with multiple systems. Use
`ai_count_available_systems()` to count configured systems and
`ai_cycle_system()` to advance to the next one with a valid API key. The helper
`ai_stop_on_error()` prints a message and exits, useful for fatal errors.

### Built-in tools

`ai_tools.h` and `ai_tools.hpp` expose a set of 28 helper functions for
common tasks across text, code, images and PDF documents. These helpers build a
prompt and call `ai_client_send_prompt_system()` under the hood. Each tool now
prefaces the request with a short system message so the AI responds with more
detailed and helpful output.

Example using the C API to summarise text:

```c
char *summary = NULL;
ai_tool_summarize_text(client, "Some long text", 0, &summary);
printf("Summary: %s\n", summary);
free(summary);
```

The C++ wrapper offers similar methods via the `AIToolsCPP` class.
