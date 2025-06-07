# Compiler and flags
CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2

# include path
INCLUDES := -Iinclude

# folders
SRCDIR   := src
OBJDIR   := build
BINDIR   := bin

# all .cpp files under src/
SRC      := $(wildcard $(SRCDIR)/*.cpp)

# object files in build/
OBJ      := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))

# entry‐point objects
MAIN_ADMIN_OBJ := main_admin.o
MAIN_GAME_OBJ  := main_game.o

# final executables
ADMIN_EXE := $(BINDIR)/hangman_admin
GAME_EXE  := $(BINDIR)/hangman_game

.PHONY: all clean dirs

all: dirs $(ADMIN_EXE) $(GAME_EXE)

# compile src/*.cpp → build/*.o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# compile main_admin.cpp → main_admin.o
$(MAIN_ADMIN_OBJ): main_admin.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# compile main_game.cpp → main_game.o
$(MAIN_GAME_OBJ): main_game.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# link admin executable
$(ADMIN_EXE): $(OBJ) $(MAIN_ADMIN_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# link game executable
$(GAME_EXE): $(OBJ) $(MAIN_GAME_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

# ensure build/ and bin/ exist
dirs:
	@mkdir -p $(OBJDIR) $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR) *.o main_admin.o main_game.o
