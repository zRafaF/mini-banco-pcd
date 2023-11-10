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
	$(clean)
	$(dir_guard)
	$(CC) $(CFLAGS) -c $< -o $@

# Main target with clean and all as dependencies
$(TARGET): clean all

# Default target
all: 
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)
	@echo Build complete for $(TARGET)


# Clean rule
clean:
	@echo Cleaning $(TARGET)
ifeq ($(OS),Windows_NT)
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR)
	@if exist $(TARGET).exe del /f $(TARGET).exe

else
	@rm -rf $(BUILD_DIR)
	@rm $(TARGET)
endif

