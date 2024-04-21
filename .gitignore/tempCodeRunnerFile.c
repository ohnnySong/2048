#include <stdio.h>
void change(int * arr,int size){
  for(int i = 0;i < size;i++)
     arr[i] = 0;
}
int main(void){
  int arr[4] = {1,2,2,2};
  change(arr,4);
  for(int i = 0;i < 4;i++)
   printf("%d ",arr[i]);
   return 0;
}