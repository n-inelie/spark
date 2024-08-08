CXX_C := clang++
CXX_FLAGS := -Wall -Wextra -Werror -Wpedantic -std=c++17 -Iinclude
DEBUG_FLAGS := -glldb
TARGET := spark

OBJ_DIR := build

$(shell mkdir -p $(OBJ_DIR))

SOURCES := $(wildcard src/*.cxx)
OBJECTS := $(SOURCES:src/%.cxx=$(OBJ_DIR)/%.o)

$(TARGET): $(OBJECTS)
	$(CXX_C) $(CXX_FLAGS) -lm -lglfw -lGL -fuse-ld=mold $(OBJECTS) -o $@

$(OBJ_DIR)/%.o: src/%.cxx
	$(CXX_C) $(CXX_FLAGS) -c $< -o $@

.PHONY: clean debug

clean:
	rm -rf $(TARGET) $(OBJ_DIR)

debug: CXX_FLAGS += $(DEBUG_FLAGS)
debug: $(TARGET)

