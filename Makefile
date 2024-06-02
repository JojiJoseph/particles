# Define the compiler and compiler flags
CXX = g++
CXXFLAGS = -Wall -std=c++17

# Define directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin

# Define the target executable
TARGET = $(BIN_DIR)/particle_system

# Define the source files
SRCS = $(wildcard $(SRC_DIR)/*.cpp)

# Define the object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))

# Define SFML library paths and libraries
LIB_DIR = /usr/local/lib
INCLUDE_DIR = /usr/local/include
LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Rule to build the target
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CXX) -o $(TARGET) $(OBJS) -L$(LIB_DIR) $(LIBS)

# Rule to build the object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up build files
.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# Print out variables (useful for debugging)
.PHONY: print
print:
	@echo "SRCS: $(SRCS)"
	@echo "OBJS: $(OBJS)"
	@echo "TARGET: $(TARGET)"
