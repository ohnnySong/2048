# Use Ubuntu 24.04 LTS (Noble) as base image
FROM ubuntu:24.04

# Set environment variables to avoid interactive prompts
ENV DEBIAN_FRONTEND=noninteractive
ENV TZ=UTC

# Update package lists and install essential tools
RUN apt-get update && \
    apt-get install -y \
    software-properties-common \
    apt-transport-https \
    ca-certificates \
    gnupg \
    lsb-release \
    curl \
    wget \
    vim \
    nano \
    git \
    build-essential \
    gcc-riscv64-linux-gnu \
    gdb-multiarch \
    qemu-user-static \
    && apt-get clean \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /workspace

# Copy your source code
COPY . /workspace/

# Set proper permissions
RUN chmod -R 755 /workspace

# Default command
CMD ["/bin/bash"]