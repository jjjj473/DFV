# DFV Browser

DFV Browser is a lightweight web browser written in C with GTK3 and WebKitGTK. The code
incorporates several small x86_64 assembly routines to demonstrate how low-level
optimizations can speed up common operations. A simple settings file lets you choose the
homepage. The Tools menu exposes system utilities for viewing CPU and memory info,
launching a terminal, inspecting network configuration, checking disk usage and
displaying kernel details and memory statistics using Linux APIs.

The project no longer builds a full operating system image. Instead, it targets
any modern Linux distribution with GTK3 and WebKitGTK development packages.

## Requirements

- A C compiler (GCC or Clang)
- Development headers for GTK3 and WebKitGTK
- `make`

On Debian/Ubuntu systems you can install the dependencies with:

```bash
sudo apt-get install build-essential libgtk-3-dev libwebkit2gtk-4.1-dev
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
- `fast_memset.S` – optimized memory fill routine
- `fast_strcmp.S` – compares two strings quickly
- `fast_memmove.S` – handles overlapping copies efficiently
- `fast_sum_array.S` – sums 32‑bit integers using SIMD

## Running

Execute the browser with an optional URL:

```bash
./dfv_browser https://duckduckgo.com
```

If no URL is provided, it opens `https://duckduckgo.com` by default. At start-up
it runs the assembly routines and prints their results to the terminal.  The
homepage can also point at the DuckDuckGo API to show search results directly.

The browser reads `~/.dfv_browser.conf` for user settings. To change the
homepage, create a file containing a line like:

```ini
homepage=https://your-site.example
```

For example, to load DuckDuckGo's Instant Answer API search for "dfv" on start
up, you could set:

```ini
homepage=https://duckduckgo.com/?q=dfv&ia=web
```

The Tools menu offers quick access to system information, network details,
disk usage statistics and a terminal launcher.  Additional options show the
running kernel version and memory statistics using Linux system calls.

The main window also provides a sidebar built with `GtkStackSidebar`.  It lets
you switch between the web view and additional pages for Downloads, History,
Settings and Developer Tools. Selecting the Dev Tools page automatically opens
the WebKit inspector so you can debug pages just like in other browsers.

Hardware acceleration is handled internally by WebKitGTK. If the underlying
system provides GPU support, WebKitGTK will use it automatically to render web
content.
