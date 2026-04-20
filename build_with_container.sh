#!/bin/bash

# Check for docker or podman
if command -v docker &> /dev/null; then
    CONTAINER_CMD="docker"
elif command -v podman &> /dev/null; then
    CONTAINER_CMD="podman"
else
    echo "Error: Neither podman nor docker is installed."
    exit 1
fi

echo "Using: $CONTAINER_CMD"

# Build the container image
$CONTAINER_CMD build -t build_env . --progress=plain