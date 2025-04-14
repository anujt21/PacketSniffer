#!/bin/bash

# Exit on error
set -e

# Check for debug flag
if [ "$1" == "-d" ]; then
  BUILD_DIR="dbuild"
  BUILD_TYPE="Debug"
else
  BUILD_DIR="build"
  BUILD_TYPE="Release"
fi

# Create build directory if it doesn't exist
if [ ! -d "$BUILD_DIR" ]; then
  mkdir -p "$BUILD_DIR"
fi

# Generate build system and build the project
cd "$BUILD_DIR"
cmake -DCMAKE_BUILD_TYPE="$BUILD_TYPE" ..
cmake --build .

# Optional: Create symbolic link to compile_commands.json in project root
# echo "Creating symbolic link to compile_commands.json in project root..."
# cd ..
# ln -sf "$BUILD_DIR/compile_commands.json" compile_commands.json
# cd "$BUILD_DIR"

# Print success message
echo ""
echo "Build completed successfully!"
echo "Build type: $BUILD_TYPE"
echo "The executable can be found in the $BUILD_DIR directory."
