#ifndef _CLEAR_H
#define _CLEAR_H

#ifdef _WIN32 // Check if compiling on Windows
#include <windows.h>
#else // Assume compiling on macOS or Linux
#include <stdlib.h>
#endif

void clear_screen();

#endif

void clear_screen() {
#ifdef _WIN32
    system("cls"); // Windows: Clear console screen
#else
    system("clear"); // macOS/Linux: Clear console screen
#endif
}
