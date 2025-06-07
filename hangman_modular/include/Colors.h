#pragma once
#ifdef _WIN32
  #include <windows.h>
#endif

#define RED    "\x1b[31m"
#define GREEN  "\x1b[32m"
#define ORANGE "\x1b[38;5;214m"
#define RESET  "\x1b[0m"

void enableAnsiColors();