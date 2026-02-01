# ===== Project settings =====
TARGET   := game
CXX      := g++
CXXFLAGS := -Wall -Wextra -Wpedantic -std=c++17 -Iinclude
LDFLAGS  :=

# ===== Directory layout =====
SRC_DIR   := src
BUILD_DIR := build

# ===== Source / object files =====
SRCS := $(wildcard $(SRC_DIR)/*.cpp)
OBJS := $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
DEPS := $(OBJS:.o=.d)

# ===== Default target =====
all: $(TARGET)

# ===== Link =====
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# ===== Compile =====
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# ===== Dependency handling =====
-include $(DEPS)

# ===== Cleanup =====
clean:
	rm -rf $(BUILD_DIR) $(TARGET)

.PHONY: all clean

