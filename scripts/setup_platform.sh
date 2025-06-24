#!/usr/bin/env bash
# Detect the host platform and install build dependencies for the AI SDK.
# Supports macOS, Windows (via Chocolatey) and common Linux distros.
# Older versions of each platform trigger installation of legacy packages.

set -e

install_macos() {
    ver=$(sw_vers -productVersion | cut -d. -f1)
    if ! command -v brew >/dev/null; then
        echo "Homebrew not found. Please install Homebrew first." >&2
        return 1
    fi
    brew update
    if [ "$ver" -lt 11 ]; then
        echo "Installing legacy compilers on macOS $ver"
        brew install gcc@9 curl
    else
        echo "Installing packages on macOS $ver"
        brew install gcc curl
    fi
}

install_linux() {
    if [ -f /etc/os-release ]; then
        . /etc/os-release
    else
        echo "Cannot detect Linux distribution" >&2
        return 1
    fi
    case "$ID" in
        ubuntu|debian)
            sudo apt-get update
            if [ "${VERSION_ID%%.*}" -lt 20 ]; then
                echo "Installing legacy packages for $ID $VERSION_ID"
                sudo apt-get install -y gcc-9 g++-9 libcurl4-openssl-dev
            else
                sudo apt-get install -y gcc g++ libcurl4-openssl-dev
            fi
            ;;
        fedora|centos|rhel)
            sudo yum -y install gcc gcc-c++ libcurl-devel
            ;;
        *)
            echo "Unsupported Linux distribution: $ID" >&2
            return 1
            ;;
    esac
}

install_windows() {
    if ! command -v choco >/dev/null; then
        echo "Chocolatey not found. Install it from https://chocolatey.org/" >&2
        return 1
    fi
    ver=$(cmd.exe /c ver 2>/dev/null | tr -d '\r' | grep -o '[0-9]\+' | head -1)
    if [ "$ver" -lt 10 ]; then
        echo "Installing legacy packages on Windows $ver via Chocolatey"
        choco install -y mingw curl --version 7.70.0
    else
        echo "Installing packages on Windows $ver via Chocolatey"
        choco install -y mingw curl
    fi
}

case "$(uname -s)" in
    Darwin)
        install_macos ;;
    Linux)
        install_linux ;;
    CYGWIN*|MINGW*|MSYS*)
        install_windows ;;
    *)
        echo "Unsupported platform: $(uname -s)" >&2
        exit 1
        ;;
esac
