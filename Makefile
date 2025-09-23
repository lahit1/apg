# Compilers
CXX := g++
CC := gcc

# Standard flags
CXXSTD := -std=c++17
CSTD := -std=c11

# Directories
BUILD := build
BIN := bin
SRC_DIRS := src glad/src
INCLUDE_DIRS := include glad/include stb

# Flags
COMPILE_FLAGS := -O0 -g -pipe -march=native
WARNING_FLAGS := -Wall -Wextra -Wpedantic
LINK_FLAGS := -lglfw -ldl

# Find all source files
CPP_SRCS := $(shell find $(SRC_DIRS) -name "*.cpp" -o -name "*.cxx" -o -name "*.cc" 2>/dev/null)
C_SRCS := $(shell find $(SRC_DIRS) -name "*.c" 2>/dev/null)
SRCS := $(CPP_SRCS) $(C_SRCS)

# Generate object file paths
CPP_OBJS := $(CPP_SRCS:%=$(BUILD)/%.o)
C_OBJS := $(C_SRCS:%=$(BUILD)/%.o)
OBJS := $(CPP_OBJS) $(C_OBJS)

# Include paths
INCLUDES := $(addprefix -I,$(INCLUDE_DIRS))

# Target
TARGET := $(BIN)/program

# Default target
all: $(TARGET)

# Link target
$(TARGET): $(OBJS) | $(BIN)
	@echo "Linking $@..."
	$(CXX) $(OBJS) -o $@ $(LINK_FLAGS)
	@echo "Copying resources..."
	@if [ -d "res/" ]; then cp -r res/ $(BIN)/; fi
	@echo "Build successful: $@"
	@echo "To run: ./$@"

# Compile C++ files
$(BUILD)/%.cpp.o: %.cpp | $(BUILD)
	@echo "Compiling: $<"
	@mkdir -p $(dir $@)
	$(CXX) $(COMPILE_FLAGS) $(WARNING_FLAGS) $(CXXSTD) $(INCLUDES) -c $< -o $@

$(BUILD)/%.cxx.o: %.cxx | $(BUILD)
	@echo "Compiling: $<"
	@mkdir -p $(dir $@)
	$(CXX) $(COMPILE_FLAGS) $(WARNING_FLAGS) $(CXXSTD) $(INCLUDES) -c $< -o $@

$(BUILD)/%.cc.o: %.cc | $(BUILD)
	@echo "Compiling: $<"
	@mkdir -p $(dir $@)
	$(CXX) $(COMPILE_FLAGS) $(WARNING_FLAGS) $(CXXSTD) $(INCLUDES) -c $< -o $@

# Compile C files
$(BUILD)/%.c.o: %.c | $(BUILD)
	@echo "Compiling: $<"
	@mkdir -p $(dir $@)
	$(CC) $(COMPILE_FLAGS) $(WARNING_FLAGS) $(CSTD) $(INCLUDES) -c $< -o $@

# Create directories
$(BUILD):
	@mkdir -p $(BUILD)

$(BIN):
	@mkdir -p $(BIN)

# Clean build
clean:
	@echo "Cleaning..."
	rm -rf $(BUILD) $(BIN)

# Run the program
run: $(TARGET)
	./$(TARGET)

# Debug build with more warnings
debug: COMPILE_FLAGS += -DDEBUG -O0 -ggdb3
debug: all

# Release build
release: COMPILE_FLAGS := -O3 -DNDEBUG -flto
release: all

# Show variables (for debugging)
print:
	@echo "C++ Sources: $(CPP_SRCS)"
	@echo "C Sources: $(C_SRCS)"
	@echo "Objects: $(OBJS)"
	@echo "Includes: $(INCLUDES)"

# Phony targets
.PHONY: all clean run debug release print

# Prevent make from deleting intermediate files
.SECONDARY:



.PHONY: install
install:
	mkdir -p assimp-build
	cd assimp-build
	cmake ../assimp
	cd ..
