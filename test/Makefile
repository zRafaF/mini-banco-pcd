# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -I../include -I$(UNITY_DIR)/src 

# Directories
SRC_DIR = ../src
BUILD_DIR = build
TEST_DIR = .
UNITY_DIR = Unity-master

# Source and object files
SRCS = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c))
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))
TEST_SRCS = $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o, $(TEST_SRCS))

# Executables
TARGET = mini_banco_pcd_test

# Ensure build directory exists
ifeq ($(OS),Windows_NT)
    dir_guard = @if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
else
    dir_guard = @mkdir -p $(BUILD_DIR)
endif

# Phony targets
.PHONY: all clean run

# Main target
all:
	$(CC) $(CFLAGS) $(SRCS) $(TEST_SRCS) $(UNITY_DIR)/src/unity.c  -o $(TARGET)
	@echo Build complete for $(TARGET)


run: $(TARGET)
ifeq ($(OS),Windows_NT)
	@if exist $(TARGET).exe .\\$(TARGET).exe
else
	./$(TARGET)
endif

clean:
	@echo Cleaning $(TARGET)
ifeq ($(OS),Windows_NT)
	@if exist $(BUILD_DIR) rmdir /s /q $(BUILD_DIR) 2>nul
	@if exist $(TARGET).exe del /f $(TARGET).exe 2>nul
else
	@if [ -d "$(BUILD_DIR)" ]; then rm -rf $(BUILD_DIR); fi
	@if [ -e "$(TARGET)" ]; then rm -f $(TARGET); fi
endif

