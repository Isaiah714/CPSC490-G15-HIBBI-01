#!/usr/bin/env bash
set -e

echo "Detecting Linux distribution..."

if [ -f /etc/os-release ]; then
    . /etc/os-release
    OS=$ID
fi

case "$OS" in
    ubuntu|debian)
        echo "Detected Ubuntu/Debian. Installing dependencies via apt..."
        sudo apt update
        sudo apt install -y \
            cmake \
            build-essential \
            libsdl3-dev \
            libassimp-dev \
            libglm-dev \
            libopengl-dev \
            libgl1-mesa-dev
        ;;
    arch)
        echo "Detected Arch Linux. Installing dependencies via pacman..."
        sudo pacman -Syu --needed \
            cmake \
            base-devel \
            sdl3 \
            assimp \
            glm \
            mesa
        ;;
    *)
        echo "Unsupported Linux distribution: $OS"
        exit 1
        ;;
esac

echo "dependencies installed"