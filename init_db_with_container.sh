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

# Run the container.
$CONTAINER_CMD run -v $(pwd)/logs:/app/logs:z -it db_init