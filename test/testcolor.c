#include <stdio.h>
void red () {
  printf("\033[1;31m");
}

void yellow (){
  printf("\033[1;33m");
}
void color(){
    printf("\e[0;32m");
}

int main () {
  red();
  printf("Hello ");
  yellow();
  printf("world ");
  color();
  printf("color\n");

  
  return 0;
}