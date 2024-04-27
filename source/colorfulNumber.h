
#include <stdio.h>
#ifndef _COLORFUL_NUMBER_H
#define _COLORFUL_NUMBER_H

#ifdef _WIN32 // Check if compiling on Windows
#include <windows.h>

#define BLACK   0
#define RED     FOREGROUND_RED
#define GREEN   FOREGROUND_GREEN
#define YELLOW  (FOREGROUND_RED | FOREGROUND_GREEN)
#define BLUE    FOREGROUND_BLUE
#define MAGENTA (FOREGROUND_RED | FOREGROUND_BLUE)
#define CYAN    (FOREGROUND_GREEN | FOREGROUND_BLUE)
#define WHITE   (FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)

#define RESET   WHITE
#else // Assume compiling on macOS or Linux
#define BLACK   "\e[0;30m"
#define RED     "\e[0;31m"
#define GREEN   "\e[0;32m"
#define YELLOW  "\e[0;33m"
#define BLUE    "\e[0;34m"
#define MAGENTA "\e[0;35m"
#define CYAN    "\e[0;36m"
#define WHITE   "\e[0;37m"

#define RESET   "\e[0m"
#endif

void print_number(int Num);

#endif
void print_number(int Num) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif

    printf(WHITE "| "); // Print the pipe character in white color

    switch(Num) {
        case 0:
            printf(WHITE "%-4d ", Num);

            break;
        case 2:
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, RED);
#else
            printf(RED);
#endif
            printf("%-4d ", Num);
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, RESET);
#else       
            printf(WHITE);
#endif
            break;
        case 4:
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, GREEN);
#else
            printf(GREEN);
#endif
            printf("%-4d ", Num);
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, RESET);
#else       
            printf(WHITE);
#endif
            break;
        case 8:
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, YELLOW);
#else
            printf(YELLOW);
#endif
            printf("%-4d ", Num);
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, RESET);
#else       
            printf(WHITE);
#endif
            break;
        case 16:
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, BLUE);
#else
            printf(BLUE);
#endif
            printf("%-4d ", Num);
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, RESET);
#else       
            printf(WHITE);
#endif
            break;
        case 32:
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, MAGENTA);
#else
            printf(MAGENTA);
#endif
            printf("%-4d ", Num);
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, RESET);
#else       
            printf(WHITE);
#endif
            break;
        case 64:
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, CYAN);
#else
            printf(CYAN);
#endif
            printf("%-4d ", Num);
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, RESET);
#else       
            printf(WHITE);
#endif
            break;
        case 128:
            printf(WHITE "%-4d ", Num);
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, RESET);
#else       
            printf(WHITE);
#endif
            break;
        case 256:
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, RED);
#else
            printf(RED);
#endif
            printf("%-4d ", Num);
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, RESET);
#else       
            printf(WHITE);
#endif
            break;
        case 512:
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, GREEN);
#else
            printf(GREEN);
#endif
            printf("%-4d ", Num);
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, RESET);
#else       
            printf(WHITE);
#endif
            break;
        case 1024:
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, YELLOW);
#else
            printf(YELLOW);
#endif
            printf("%-4d ", Num);
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, RESET);
#else       
            printf(WHITE);
#endif
            break;
        case 2048:
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, BLUE);
#else
            printf(BLUE);
#endif
            printf("%-4d ", Num);
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, RESET);
#else       
            printf(WHITE);
#endif
            break;
        default:
#ifdef _WIN32
            SetConsoleTextAttribute(hConsole, RESET);
#else
            printf(RESET);
#endif
            printf("%-4d ", Num); // If the number is not in the specified range, reset to default color
            break;
    }
#ifdef _WIN32
    SetConsoleTextAttribute(hConsole, RESET); // Reset console color to default
#endif
}