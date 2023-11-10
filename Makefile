# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

# Directories
SRC_DIR = src
BUILD_DIR = build

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

# Executable
TARGET = mini_banco_pcd

# Ensure build directory exists
ifeq ($(OS),Windows_NT)
    dir_guard = @if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
else
    dir_guard = @mkdir -p $(BUILD_DIR)
endif

# Phony targets
.PHONY: all clean

# Build rule
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(dir_guard)
	$(CC) $(CFLAGS) -c $< -o $@

# Main target
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Default target
all: $(TARGET)
	@echo Build complete for $(TARGET)

# Clean rule
clean:
	rmdir /s /q $(BUILD_DIR)
