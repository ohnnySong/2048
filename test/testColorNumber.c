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

void print_number(int Num);
void print_number(int Num){
   switch(Num){
    case 0:
    
    case 2: 
       red();
       printf("%d",Num);
       reset();
       break;       
    case 4:
        yellow();
       printf("%d",Num);
       reset();
       break;       
    case 8:
      green();
       printf("%d",Num);
       reset();
       break;       
    case 16:
     red();
       printf("%d",Num);
       reset();
       break;       
    case 32:
     yellow();
       printf("%d",Num);
       reset();
       break;       
    case 64:
     green();
       printf("%d",Num);
       reset();
       break;       
    case 128:
     red();
       printf("%d",Num);
       reset();
       break;       
    case 256:
     yellow();
       printf("%d",Num);
       reset();
       break;       
    case 512:
     green();
       printf("%d",Num);
       reset();
       break;       
    case 1024:
     cayn();
       printf("%d",Num);
       reset();
       break;       
    case 2048:
     cayn();
       printf("%d",Num);
       reset();
       break;       
   }
}

int main(void){
    print_number(2);
    return 0;
}