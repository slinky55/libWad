# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17

# Source and object files
SRC = Wad.cpp
HEADER = Wad.h
OBJ = Wad.o

# Library name and output
LIB_NAME = Wad
LIB_OUTPUT = lib$(LIB_NAME).a

# Targets
all: clean $(LIB_OUTPUT)

$(LIB_OUTPUT): $(OBJ)
	ar rcs $@ $^

$(OBJ): $(SRC) $(HEADER)
	$(CXX) $(CXXFLAGS) -c $(SRC) -o $(OBJ)

clean:
	rm -f $(LIB_OUTPUT) $(OBJ)

.PHONY: all clean
