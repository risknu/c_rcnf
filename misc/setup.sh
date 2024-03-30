#!/bin/bash

# This script creates shared directories in the root of the project

# Function to create directories if they don't exist
create_directories() {
    for dir in "$@"; do
        if [ ! -d "$dir" ]; then
            mkdir -p "$dir" && echo "Created directory: $dir"
        else
            echo "Directory already exists: $dir"
        fi
    done
}

main() {
    directories=(
        "shared"
        "shared/dll"
    )

    create_directories "${directories[@]}"
}

main
