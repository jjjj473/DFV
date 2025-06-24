# DFV Browser

DFV Browser is a lightweight web browser written in C with GTK3 and WebKitGTK. The code
incorporates several small x86_64 assembly routines to demonstrate how low-level
optimizations can speed up common operations. A simple settings file lets you choose the
homepage, while the Tools menu exposes system utilities like viewing CPU and memory info
or launching a terminal.

The project no longer builds a full operating system image. Instead, it targets
any modern Linux distribution with GTK3 and WebKitGTK development packages.

## Requirements

- A C compiler (GCC or Clang)
- Development headers for GTK3 and WebKitGTK
- `make`

On Debian/Ubuntu systems you can install the dependencies with:

```bash
sudo apt-get install build-essential libgtk-3-dev libwebkit2gtk-4.0-dev
```

## Building

Simply run:

```bash
make
```

This creates the `dfv_browser` executable and assembles the following optimized
modules with SSE2 instructions for better performance on modern AMD and Intel
processors:

- `fast_memcpy.S` – unrolled SSE copy with prefetch
- `fast_strlen.S` – vectorized string length routine
- `fast_add.S` – 64‑bit addition example
- `fast_uppercase.S` – converts strings to uppercase

## Running

Execute the browser with an optional URL:

```bash
./dfv_browser https://example.com
```

If no URL is provided, it opens `https://example.com` by default. At start-up
it runs the assembly routines and prints their results to the terminal.

The browser reads `~/.dfv_browser.conf` for user settings. To change the
homepage, create a file containing a line like:

```ini
homepage=https://your-site.example
```

The Tools menu offers quick access to system information and a terminal
launcher.

Hardware acceleration is handled internally by WebKitGTK. If the underlying
system provides GPU support, WebKitGTK will use it automatically to render web
content.
