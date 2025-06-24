#!/bin/sh
# Download pre-built GStreamer packages with useful video effects.
set -e
URL_BASE="https://gstreamer.freedesktop.org/data/pkg/linux/x86_64"
VERSION="1.22.6"
mkdir -p external
cd external
for pkg in gstreamer gst-plugins-base gst-plugins-good gst-plugins-bad gst-plugins-ugly; do
    file="${pkg}-${VERSION}.tar.xz"
    if [ ! -f "$file" ]; then
        wget -c "$URL_BASE/$file"
    fi
done

