# AI SDK for C and C++

This repository provides a minimal SDK for building simple AI agents in C or C++
using the OpenAI API (or compatible APIs). The SDK is implemented in C with a
C++ wrapper and includes small example programs.

## Building

Requirements:

- GCC and G++
- libcurl development files

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

Set your API key in the environment variable `OPENAI_API_KEY` and run one of the
examples:

```sh
export OPENAI_API_KEY=your-key-here
./example_c
# or
./example_cpp
```

Both examples send a simple prompt to the API and print the returned message
content.

Developers can link against `libai_sdk.a` and include `ai_sdk.h` or
`ai_sdk.hpp` in their projects to issue chat completion requests.
