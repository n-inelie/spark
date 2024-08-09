CXX_C := clang++
CXX_FLAGS := -Wall -Wextra -Werror -Wpedantic -std=c++17 -Iinclude
DEBUG_FLAGS := -glldb
RELEASE_FLAGS := -O3
LINK_FLAGS := -lm -lglfw -lGL -fuse-ld=mold
TARGET := spark

OBJ_DIR := build

$(shell mkdir -p $(OBJ_DIR))

SOURCES := $(wildcard src/*.cxx)
OBJECTS := $(SOURCES:src/%.cxx=$(OBJ_DIR)/%.o)

$(TARGET): $(OBJECTS)
	$(CXX_C) $(CXX_FLAGS) $(LINK_FLAGS) $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: src/%.cxx
	$(CXX_C) $(CXX_FLAGS) -c $< -o $@

.PHONY: clean debug release

clean:
	rm -rf $(TARGET) $(OBJ_DIR)

debug: CXX_FLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

release: CXX_FLAGS += $(RELEASE_FLAGS)
release: $(TARGET)

