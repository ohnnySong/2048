
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define SIZE 4
typedef int** Board;
int board[SIZE][SIZE];
void print_board(Board board) {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%-6d", board[i][j]);
        }
        printf("\n\n");
    }
}

void move_up_column(int * arr);
void init_zero(int * arr){
  for(int i = 0; i < SIZE;i++){
    arr[i] = 0;
  }
}
int **create_board(int arr[][SIZE], int rows, int cols) {
    int **board = (int **)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        board[i] = (int *)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            board[i][j] = arr[i][j];
        }
    }
    return board;
}
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
     //bool haveCombined = false;
     
     PushtoTop(arr);
      if(arr[2] == arr[3]&&arr[2]&&arr[3]) {
         CombineValue(arr, 2, 3);
         
        // haveCombined = true;
         PushtoTop(arr);
      }
     if(/*!haveCombined &&*/ arr[1] == arr[2]&&arr[1]&&arr[2]) {
         CombineValue(arr, 1, 2);
        
        // haveCombined = true;
         PushtoTop(arr);
      }
      if(/*!haveCombined &&*/ arr[0] == arr[1]&&arr[0]&&arr[1]){
         CombineValue(arr, 0, 1);
         //haveCombined = true;
         PushtoTop(arr);
      }
}
 //return a series of non-empty block in the board
void init_zero(int *arr);
void move_up(Board board) {
    int haveCombined[SIZE];
    init_zero(haveCombined);

    // 复制board的每一列到column_1到column_4
    int column_1[SIZE], column_2[SIZE], column_3[SIZE], column_4[SIZE];
    for (int i = 0; i < SIZE; i++) {
        column_1[i] = board[i][0];
        column_2[i] = board[i][1];
        column_3[i] = board[i][2];
        column_4[i] = board[i][3];
    }

    // 调用move_up_column处理每一列
    move_up_column(column_1);
    move_up_column(column_2);
    move_up_column(column_3);
    move_up_column(column_4);

    // 将处理后的列复制回board
    for (int i = 0; i < SIZE; i++) {
        board[i][0] = column_1[i];
        board[i][1] = column_2[i];
        board[i][2] = column_3[i];
        board[i][3] = column_4[i];
    }
}
void PushtoBottom(int * arr);
void PushtoBottom(int * arr){
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
void move_down_column(int * arr);
void move_down_column(int * arr){
 bool haveCombined = false;
     PushtoTop(arr);
      if(arr[2] == arr[3]&&arr[2]&&arr[3]) {
         CombineValue(arr, 2, 3);
         haveCombined = true;
         PushtoBottom(arr);
      }
       else if(!haveCombined && arr[1] == arr[2]&&arr[1]&&arr[2]) {
         CombineValue(arr, 1, 2);
         haveCombined = true;
         PushtoBottom(arr);
      }
       else if(!haveCombined && arr[0] == arr[1]&&arr[0]&&arr[1]){
         CombineValue(arr, 0, 1);
         haveCombined = true;
         PushtoBottom(arr);
      }

}
void move_down(Board board) {
    int haveCombined[SIZE];
    init_zero(haveCombined);

    // 复制board的每一列到column_1到column_4
    int column_1[SIZE], column_2[SIZE], column_3[SIZE], column_4[SIZE];
    for (int i = SIZE - 1; i >= 0; i--) {
        column_1[i] = board[SIZE - 1 - i][0];
        column_2[i] = board[SIZE - 1 - i][1];
        column_3[i] = board[SIZE - 1 - i][2];
        column_4[i] = board[SIZE - 1 - i][3];
    }

    // 调用move_up_column处理每一列
    move_down_column(column_1);
    move_down_column(column_2);
    move_down_column(column_3);
    move_down_column(column_4);

    // 将处理后的列复制回board
    for (int i = 0; i < SIZE; i++) {
        board[SIZE - 1 - i][0] = column_1[i];
        board[SIZE - 1 - i][1] = column_2[i];
        board[SIZE - 1 - i][2] = column_3[i];
        board[SIZE - 1 - i][3] = column_4[i];
    }
}
void PushtoLeft(int *arr);
void PushtoLeft(int *arr) {
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
void move_left_row(int * arr);
void move_left_row(int * arr){
    bool haveCombined = false;
     PushtoLeft(arr);
      if(arr[2] == arr[3]&&arr[2]&&arr[3]) {
         CombineValue(arr, 2, 3);
         haveCombined = true;
         PushtoBottom(arr);
      }
       else if(!haveCombined && arr[1] == arr[2]&&arr[1]&&arr[2]) {
         CombineValue(arr, 1, 2);
         haveCombined = true;
         PushtoBottom(arr);
      }
       else if(!haveCombined && arr[0] == arr[1]&&arr[0]&&arr[1]){
         CombineValue(arr, 0, 1);
         haveCombined = true;
         PushtoBottom(arr);
      }

}
void move_left(Board board);
void move_left(Board board){
   
    // 复制board的每一列到row_1到row_4
    int row_1[SIZE], row_2[SIZE], row_3[SIZE], row_4[SIZE];
    for (int i = 0; i < SIZE; i++) {
        row_1[i] = board[0][i];
        row_2[i] = board[1][i];
        row_3[i] = board[2][i];
        row_4[i] = board[3][i];
    }

    // 调用move_up_column处理每一列
    move_left_row(row_1);
    move_left_row(row_2);
    move_left_row(row_3);
    move_left_row(row_4);

    // 将处理后的列复制回board
    for (int i = 0; i < SIZE; i++) {
        board[0][i] = row_1[i];
        board[1][i] = row_2[i];
        board[2][i] = row_3[i];
        board[3][i] = row_4[i];
    }
}
void PushtoRight(int * arr);
void PushtoRight(int * arr){
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
void move_right_row(int * arr);
void move_right_row(int * arr){
  bool haveCombined = false;
     PushtoRight(arr);
      if(arr[2] == arr[3]&&arr[2]&&arr[3]) {
         CombineValue(arr, 2, 3);
         haveCombined = true;
         PushtoRight(arr);
      }
       else if(!haveCombined && arr[1] == arr[2]&&arr[1]&&arr[2]) {
         CombineValue(arr, 1, 2);
         haveCombined = true;
         PushtoRight(arr);
      }
       else if(!haveCombined && arr[0] == arr[1]&&arr[0]&&arr[1]){
         CombineValue(arr, 0, 1);
         haveCombined = true;
          PushtoRight(arr);
      }


}
void move_right(Board board);
void move_right(Board board){
   
    // 复制board的每一列到row_1到row_4
    int row_1[SIZE], row_2[SIZE], row_3[SIZE], row_4[SIZE];
    for (int i = 0; i < SIZE; i++) {
        row_1[i] = board[0][SIZE - i - 1];
        row_2[i] = board[1][SIZE - i - 1];
        row_3[i] = board[2][SIZE - i - 1];
        row_4[i] = board[3][SIZE - i - 1];
    }

    // 调用move_up_row处理每一列
    move_right_row(row_1);
    move_right_row(row_2);
    move_right_row(row_3);
    move_right_row(row_4);

    // 将处理后的列复制回board
    for (int i = 0; i < SIZE; i++) {
        board[0][SIZE - i - 1] = row_1[i];
        board[1][SIZE - i - 1] = row_2[i];
        board[2][SIZE - i - 1] = row_3[i];
        board[3][SIZE - i - 1] = row_4[i];
    }
}
int main(void){

   int board_1 [SIZE][SIZE] = {{2,2,0,4},{2,0,0,0},{4,2,2,0},{4,0,2,4}};
    int **board_2 = create_board(board_1, SIZE, SIZE);
    print_board(board_2);
    move_up(board_2);
    print_board(board_2);
}
