# OS Lab Docker Setup

## Problem Analysis

The issue you encountered is that your Docker container is using the Ubuntu ports repository (`ports.ubuntu.com`) which is designed for ARM64 architecture and has connectivity issues. This is why `apt update` fails and you can't install `gcc-riscv64-linux-gnu`.

## Solution

I've created a proper Docker setup that uses the main Ubuntu repositories instead of the ports repository.

### Files Created:

1. **Dockerfile** - Uses Ubuntu 24.04 with proper repository configuration
2. **docker-compose.yml** - Easy container management
3. **run-container.sh** - Convenience script to build and run
4. **.dockerignore** - Excludes unnecessary files from build context

### Key Fixes:

1. **Repository Issue**: The Dockerfile uses `ubuntu:24.04` which automatically uses the correct repositories for your architecture
2. **Pre-installed Tools**: The Dockerfile already includes `gcc-riscv64-linux-gnu` and other essential tools
3. **Proper Environment**: Sets up a clean Ubuntu environment for your OS lab

## Usage Instructions

### Option 1: Using Docker Compose (Recommended)
```bash
# Build the container
docker compose build

# Run the container
docker compose up -d

# Attach to the container
docker compose exec os-lab bash

# Stop the container
docker compose down
```

### Option 2: Using Docker directly
```bash
# Build the image
docker build -t os-lab-ubuntu .

# Run the container
docker run -it --name os-lab-container -v $(pwd):/workspace os-lab-ubuntu

# Or run in background
docker run -d --name os-lab-container -v $(pwd):/workspace os-lab-ubuntu
docker exec -it os-lab-container bash
```

### Option 3: If Docker is not available
If Docker is not installed on your system, you can:

1. **Install Docker** following the official guide for your OS
2. **Use the provided Dockerfile** to create a container with proper repository configuration
3. **Run the container** and verify that `gcc-riscv64-linux-gnu` is available

## Verification

Once inside the container, verify the installation:
```bash
# Check if gcc-riscv64-linux-gnu is installed
gcc-riscv64-linux-gnu --version

# Check available packages
apt list --installed | grep riscv

# Update package lists (should work now)
apt update
```

## Why This Fixes Your Problem

1. **Correct Architecture**: Uses the main Ubuntu repositories instead of ports
2. **Pre-configured**: All necessary tools are installed during build
3. **Clean Environment**: Fresh Ubuntu installation without repository conflicts
4. **Volume Mounting**: Your source code is available inside the container

## Troubleshooting

If you still encounter issues:

1. **Check Docker installation**: `docker --version`
2. **Check Docker Compose**: `docker compose version`
3. **Rebuild without cache**: `docker compose build --no-cache`
4. **Check container logs**: `docker compose logs os-lab`

The container should now have all the tools you need for your OS lab, including `gcc-riscv64-linux-gnu` for RISC-V development.