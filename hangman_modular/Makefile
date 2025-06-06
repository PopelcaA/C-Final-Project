# Simple Makefile for the modular Hangman project
CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2

# folders
INCLUDES := -Iinclude
SRCDIR   := src
OBJDIR   := build
BINDIR   := bin

# source files
SRC := $(wildcard $(SRCDIR)/*.cpp)
OBJ := $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))

# executables
ADMIN_EXE := $(BINDIR)/hangman_admin
GAME_EXE  := $(BINDIR)/hangman_game

.PHONY: all clean dirs

all: dirs $(ADMIN_EXE) $(GAME_EXE)

# pattern rule
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

$(ADMIN_EXE): $(OBJ) main_admin.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

$(GAME_EXE): $(OBJ) main_game.o
	$(CXX) $(CXXFLAGS) $(INCLUDES) $^ -o $@

main_admin.o: main_admin.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

main_game.o: main_game.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

dirs:
	@mkdir -p $(OBJDIR) $(BINDIR)

clean:
	rm -rf $(OBJDIR) $(BINDIR) *.o main_admin.o main_game.o
