# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++14

# Target executable
TARGET = main

# Source files
SRCS = src/main.cpp src/sequential_implementation.cpp src/implicit_parallelization.cpp src/explicit_parallelization.cpp src/helpers.cpp

# Object files
OBJS = $(SRCS:.cpp=.o)

# Default target
all: $(TARGET)

# Link the object files to create the executable
$(TARGET): $(OBJS)
	@echo "Linking object files to create the executable..."
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files into object files
src/%.o: src/%.cpp
	@echo "Compiling $< into $@..."
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
clean:
	rm -f $(TARGET) $(OBJS)

.PHONY: all clean