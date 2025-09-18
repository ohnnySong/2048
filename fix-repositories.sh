#!/bin/bash

# Script to fix repository issues in existing Ubuntu container
# Run this inside your existing container

echo "Fixing Ubuntu repository configuration..."

# Backup original sources.list
cp /etc/apt/sources.list /etc/apt/sources.list.backup

# Create new sources.list with main Ubuntu repositories
cat > /etc/apt/sources.list << 'EOF'
# Ubuntu 24.04 LTS (Noble) - Main repositories
deb http://archive.ubuntu.com/ubuntu/ noble main restricted universe multiverse
deb http://archive.ubuntu.com/ubuntu/ noble-updates main restricted universe multiverse
deb http://archive.ubuntu.com/ubuntu/ noble-backports main restricted universe multiverse
deb http://security.ubuntu.com/ubuntu/ noble-security main restricted universe multiverse
EOF

echo "Updated sources.list with main Ubuntu repositories"

# Update package lists
echo "Updating package lists..."
apt update

# Install gcc-riscv64-linux-gnu
echo "Installing gcc-riscv64-linux-gnu..."
apt install -y gcc-riscv64-linux-gnu

# Install other useful tools for OS lab
echo "Installing additional tools..."
apt install -y build-essential gdb-multiarch qemu-user-static

echo "Repository fix completed!"
echo "You can now use gcc-riscv64-linux-gnu for your OS lab."