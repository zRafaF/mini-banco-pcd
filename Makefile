# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
CFLAGS_TEST = -Wall -Wextra -Iinclude -I$(UNITY_DIR)/src 

# Directories
SRC_DIR = src
BUILD_DIR = build
TEST_DIR = test
UNITY_DIR = $(TEST_DIR)/Unity-master

# Source and object files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS))

TEST_SRCS = $(filter-out $(SRC_DIR)/main.c, $(wildcard $(SRC_DIR)/*.c)) $(wildcard $(TEST_DIR)/*.c)
TEST_OBJS = $(patsubst $(SRC_DIR)/%.c, $(BUILD_DIR)/%.o, $(SRCS)) $(patsubst $(TEST_DIR)/%.c, $(BUILD_DIR)/%.o)


# Executable
TARGET = mini_banco_pcd
TARGET_TEST = mini_banco_pcd_test

# Ensure build directory exists
ifeq ($(OS),Windows_NT)
    dir_guard = @if not exist $(BUILD_DIR) mkdir $(BUILD_DIR)
else
    dir_guard = @mkdir -p $(BUILD_DIR)
endif

# Phony targets
.PHONY: all clean run test

# Build rule
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	$(clean)
	$(dir_guard)
	$(CC) $(CFLAGS) -c $< -o $@

# Main target with clean and all as dependencies
$(TARGET): clean all

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)
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

test:
	$(CC) $(CFLAGS_TEST) $(TEST_SRCS) $(UNITY_DIR)/src/unity.c  -o $(TARGET_TEST)
	@echo Build complete for $(TARGET_TEST)
	@echo running Test...
ifeq ($(OS),Windows_NT)
	@if exist $(TARGET_TEST).exe .\\$(TARGET_TEST).exe
else
	./$(TARGET_TEST)
endif