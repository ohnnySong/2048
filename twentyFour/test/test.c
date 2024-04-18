#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 4
int nonEmptyNumber(int * arr);
int nonEmptyNumber(int * arr){
    int cnt_non_zero = 0;
    for(int i  = 0;i < SIZE;i++){
        if(arr[i] != 0)
           cnt_non_zero++;
    }
    return cnt_non_zero;
}
void PushtoTop(int * arr);
void PushtoTop(int *arr) {
    int j = 0;
    int *Occupied_Series;
    int CntNonZero = nonEmptyNumber(arr); // 假设已经实现了 nonEmptyNumber 函数
    Occupied_Series = (int *)malloc(sizeof(int) * CntNonZero);
    
    for (int i = 0; i < SIZE; i++) {
        if (arr[i] != 0) {
            Occupied_Series[j++] = arr[i];
        }
    }

    for (int j = 0; j < CntNonZero; j++) {
        arr[j] = Occupied_Series[j];
    }

    for (int j = CntNonZero; j < SIZE; j++) {
        arr[j] = 0;
    }
    
    free(Occupied_Series); // 释放动态分配的内存
}
void CombineValue(int * arr,int index_1,int index_2);
void CombineValue(int * arr,int index_1,int index_2){
    arr[index_1] = 2 * arr[index_1] ;
    arr[index_2] = 0;
}

void move_up_column(int * arr){
     bool haveCombined = false;
     
     PushtoTop(arr);
      if(arr[2] == arr[3]&&arr[2]&&arr[3]) {
         CombineValue(arr, 2, 3);
         haveCombined = true;
         PushtoTop(arr);
      }
       else if(!haveCombined && arr[1] == arr[2]&&arr[1]&&arr[2]) {
         CombineValue(arr, 1, 2);
         haveCombined = true;
         PushtoTop(arr);
      }
       else if(!haveCombined && arr[0] == arr[1]&&arr[0]&&arr[1]){
         CombineValue(arr, 0, 1);
         haveCombined = true;
         PushtoTop(arr);
      }
}
void print_arr(int * arr,int size);
void print_arr(int * arr,int size){
    for(int i = 0;i < SIZE;i++){
        printf("%d ",arr[i]);
    }
}
int main(void){
    int sample_arr1 [4]= {0,2,2,2};
    int sample_arr2 [4]= {2,2,2,2};
    int sample_arr3 [4]= {2,2,1024,2};
     int sample_arr4 [4]= {2,2,0,0};
   move_up_column(sample_arr1);
   move_up_column(sample_arr2);
    move_up_column(sample_arr3);
     move_up_column(sample_arr4);
   print_arr(sample_arr1,SIZE);
   printf("\n");
   print_arr(sample_arr2,SIZE);
   printf("\n");
   print_arr(sample_arr3,SIZE);
   printf("\n");
   print_arr(sample_arr4,SIZE);
   printf("\n");
}