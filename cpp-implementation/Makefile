# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14

# Target executable
TARGET = main

# Source files
SRCS = src/main.cpp src/sequential_implementation.cpp src/implicit_parallelization.cpp src/explicit_parallelization.cpp src/helpers.cpp

# Output directory for object files
OUTPUT_DIR = output_files

# Object files
OBJS = $(SRCS:src/%.cpp=$(OUTPUT_DIR)/%.o)

# Default target
all: $(TARGET)

# Ensure the output directory exists
$(OUTPUT_DIR):
	mkdir -p $(OUTPUT_DIR)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
$(OUTPUT_DIR)/%.o: src/%.cpp | $(OUTPUT_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)
	rm -rf $(OUTPUT_DIR)

.PHONY: all clean
