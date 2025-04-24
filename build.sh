#!/bin/bash

# Colors for output
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Function to print colored messages
print_message() {
    echo -e "${GREEN}$1${NC}"
}

print_error() {
    echo -e "${RED}$1${NC}"
}

# Check if build directory exists, if not create it
if [ ! -d "build" ]; then
    print_message "Creating build directory..."
    mkdir build
fi

# Enter build directory
cd build

# Check if CMake has been run before
if [ ! -f "Makefile" ]; then
    print_message "Running CMake..."
    cmake ..
    if [ $? -ne 0 ]; then
        print_error "CMake failed!"
        exit 1
    fi
fi

# Build the project
print_message "Building the project..."
cmake --build .
if [ $? -ne 0 ]; then
    print_error "Build failed!"
    exit 1
fi

# Check if the executable exists
if [ -f "bin/Battleship" ]; then
    print_message "Build successful! Running the game..."
    ./bin/Battleship
else
    print_error "Executable not found!"
    exit 1
fi 