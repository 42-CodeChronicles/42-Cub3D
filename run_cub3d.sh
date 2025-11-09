#!/bin/bash

# Script to run cub3D with virtual display in dev container

# Check if Xvfb is running
if ! pgrep -x "Xvfb" > /dev/null; then
    echo "Starting Xvfb virtual display..."
    Xvfb :99 -screen 0 1280x720x24 > /dev/null 2>&1 &
    sleep 1
fi

# Set display and run cub3D
export DISPLAY=:99
./cub3D "$@"
