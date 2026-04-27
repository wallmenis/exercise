#!/bin/bash

mkdir -p logs
mkdir -p conf

if [ ! -f conf/conf.json ]; then
    echo "Creating default configuration file..."
    cat > conf/conf.json <<EOL
{ 
  "username" : "",
  "password" : "",
  "db_connection_string" : ""
}
EOL
    echo "Default configuration file created at conf/conf.json. Please update it with your database credentials."
else
    echo "Configuration file already exists at conf/conf.json. Please ensure it is updated with your database credentials."
fi

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
$CONTAINER_CMD build . --progress=plain --target build_env -t build_env
$CONTAINER_CMD build . --progress=plain --target db_init -t db_init
$CONTAINER_CMD build . --progress=plain --target main_app -t main_app
$CONTAINER_CMD build . --progress=plain --target test_image -t test_image