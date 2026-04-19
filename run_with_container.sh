#!/bin/bash

# Check for podman or docker
if command -v podman &> /dev/null; then
    CONTAINER_CMD="podman"
elif command -v docker &> /dev/null; then
    CONTAINER_CMD="docker"
else
    echo "Error: Neither podman nor docker is installed."
    exit 1
fi

echo "Using: $CONTAINER_CMD"

# Run the container.
$CONTAINER_CMD run build_env