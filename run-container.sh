#!/bin/bash

# Script to build and run the OS lab Ubuntu container

echo "Building Docker container for OS lab..."
docker-compose build

echo "Starting container..."
docker-compose up -d

echo "Container is running! You can now:"
echo "1. Attach to the container: docker-compose exec os-lab bash"
echo "2. Or run commands directly: docker-compose exec os-lab <command>"
echo ""
echo "To stop the container: docker-compose down"
echo "To rebuild: docker-compose build --no-cache"