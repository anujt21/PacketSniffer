#!/bin/bash

# Exit on error
set -e

# Print commands
# set -x

if [ ! -d "build" ]; then
  mkdir -p build
fi

# Generate build system and build the project
cd build
cmake ..
cmake --build .

# Create symbolic link to compile_commands.json in project root
# echo "Creating symbolic link to compile_commands.json in project root..."
# cd ..
# ln -sf build/compile_commands.json compile_commands.json
# cd build

# Print success message
echo ""
echo "Build completed successfully!"
echo "The executable can be found in the build directory."
