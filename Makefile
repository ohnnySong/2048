# Simple Makefile for building and running a 2048 game

# Declare variables
CC=gcc
SRC_DIR=source
OUT_DIR=tmp
EXECUTABLE=2048game

# Phony targets for not actual files
.PHONY: build run

# Build target
build:
	@echo "Building the game..."
	@cd $(SRC_DIR) && $(CC) -o ../$(OUT_DIR)/$(EXECUTABLE) 2048game.c && cd ..

# Run target
run:
	@echo "Running the game..."
	@chmod +x $(OUT_DIR)/$(EXECUTABLE)
	@./$(OUT_DIR)/$(EXECUTABLE)
