# Use Ubuntu as base image with Qt support
FROM ubuntu:22.04

# Avoid prompts from apt
ENV DEBIAN_FRONTEND=noninteractive

# Install Qt6, development tools, and X11 libraries
RUN apt-get update && apt-get install -y \
    qt6-base-dev \
    qt6-tools-dev \
    qt6-tools-dev-tools \
    build-essential \
    cmake \
    make \
    g++ \
    xvfb \
    x11vnc \
    fluxbox \
    wget \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy source code
COPY . .

# Create CMakeLists.txt for your Qt project
RUN cat > CMakeLists.txt << 'EOF'
cmake_minimum_required(VERSION 3.16)
project(TicTacToe)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets)

qt6_standard_project_setup()

# Find all source files
file(GLOB SOURCES "*.cpp")
file(GLOB HEADERS "*.h")
file(GLOB UI_FILES "*.ui")

# Process UI files
qt6_add_executable(TicTacToe ${SOURCES} ${HEADERS})
qt6_add_resources(TicTacToe "resources" FILES ${UI_FILES})

target_link_libraries(TicTacToe Qt6::Core Qt6::Widgets)
EOF

# Build the application
RUN mkdir build && cd build && \
    cmake .. && \
    make

# Create a simple startup script
RUN cat > start.sh << 'EOF'
#!/bin/bash
export DISPLAY=:99
Xvfb :99 -screen 0 1024x768x16 &
sleep 2
fluxbox &
cd /app/build
./TicTacToe
EOF

RUN chmod +x start.sh

# Expose port for VNC (optional, for remote access)
EXPOSE 5900

# Start the application
CMD ["./start.sh"]
