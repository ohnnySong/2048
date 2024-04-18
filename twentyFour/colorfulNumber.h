#include <stdio.h>
#ifndef _colorful_Number_h
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

#define RESET "\e[0m"
#define CRESET "\e[0m"
#define COLOR_RESET "\e[0m"
#endif
void red();
void red () {
  printf("\033[1;31m");
}
void green();
void green () {
  printf("\033[1;32m");
}
void yellow();
void yellow(){
  printf("\033[1;33m");
}
void blue();
void blue(){
     printf("\033[1;34m");
}
void mag();
void mag(){
     printf("\033[1;35m");
}
void cayn();
void cayn(){
     printf("\033[1;36m");
}
void reset () {
  printf("\033[0m");
}
void white(){
    printf("\033[1;37m");
}

void print_number(int Num);
void print_number(int Num) {
    white(); // 设置颜色为白色
    printf("| ");
    reset(); // 恢复默认颜色

    switch(Num) {
        case 0:
            white();
            break;
        case 2:
            red();
            break;
        case 4:
            green();
            break;
        case 8:
            yellow();
            break;
        case 16:
            blue();
            break;
        case 32:
            mag();
            break;
        case 64:
            cayn();
            break;
        case 128:
            white();
            break;
        case 256:
            red();
            break;
        case 512:
            green();
            break;
        case 1024:
            yellow();
            break;
        case 2048:
            blue();
            break;
        default:
            reset(); // 如果数字不在所列出的范围内，则重置为默认颜色
            break;
    }
    printf("%-4d ", Num);
    reset(); // 恢复默认颜色
}
