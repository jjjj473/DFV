# DFV Video Editor

DFV Video Editor is a simple GTK+3 application that demonstrates
basic video editing capabilities using the GStreamer Editing Services
(GES) library.

## Features

- Load video clips and preview them inside the application
- Basic trimming of clips with start and end points
- Apply simple effects such as fade in/out
- Export the edited timeline to a new video file

This project serves as a minimal example for building a GTK-based
video editor using existing multimedia SDKs.

## Building

You need the development packages for `gtk+-3.0`, `gstreamer-1.0`,
`gstreamer-video-1.0` and `ges-1.0` installed on your system.

Compile the editor with:

```sh
make
```

### Optional: Download pre-built effects

To try additional GStreamer effects without building them yourself, run:

```sh
./scripts/download_effects.sh
```

This script fetches binary plugin packages from the GStreamer project and
places them in an `external/` directory. The editor will load any effects
available in your system's plugin path at runtime.

## Running

```
./dfv_editor [video-file]
```

If no video file is supplied, a test clip is generated automatically.
