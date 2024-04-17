#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "colorfulNumber.h"
/*---------------------------MACRO---------------------------*/
#define SIZE 4
typedef int** Board;
typedef struct Coordinate{
    int x;
    int y;
}Coordinate;
typedef struct Block{
   Coordinate position;
   int keyValue;

}Block;
typedef Block* OccupiedSeries;
bool game_over = false;
int board[SIZE][SIZE];
int BestScore = 0;
int Score = 0;
bool init_show_mode = true;
char Mode ;
/*---------------------------MACRO---------------------------*/
/*---------------------------FUNCTION---------------------------*/
void calculateScore(int valueCombined);
void move_up_column(int * arr);
bool isEmptyBound(Board board,char Direction); 
int nonEmptyNumber(int * arr);
void PushtoTop(int * arr);
void CombineValue(int * arr,int index_1,int index_2);
void move_down_column(int * arr);
OccupiedSeries getNumberBlock(Board board); //return a series of non-empty block in the board
void init_zero(int *arr);
void PushtoLeft(int *arr);
void move_left_row(int * arr);
void move_left();
void PushtoRight(int * arr);
void move_right_row(int * arr);
int min_board();
void spawn_block_easy();
void reset_game();
void move_right();
void reset_entrance();
void quit_game();
void spawn_block_hard();
void spawn_block(char Mode);
/*---------------------------FUNCTION---------------------------*/

void PushtoBottom(int * arr);


 //check if the bound is empty(four sides);

void init_zero(int * arr){
  for(int i = 0; i < SIZE;i++){
    arr[i] = 0;
  }
}

int nonEmptyNumber(int * arr){
    int cnt_non_zero = 0;
    for(int i  = 0;i < SIZE;i++){
        if(arr[i] != 0)
           cnt_non_zero++;
    }
    return cnt_non_zero;
}

void PushtoTop(int *arr) {
    int j = 0;
    int *Occupied_Series;
    int CntNonZero = nonEmptyNumber(arr); 
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
    
    free(Occupied_Series); 
}

void CombineValue(int * arr,int index_1,int index_2){
    arr[index_1] = 2 * arr[index_1] ;
    arr[index_2] = 0;
}

void move_up_column(int * arr){
     bool haveCombined = false;
     
     PushtoTop(arr);
      if(arr[2] == arr[3]&&arr[2]&&arr[3]) {
         CombineValue(arr, 2, 3);
         calculateScore(arr[2]);
         haveCombined = true;
         PushtoTop(arr);
      }
       else if(!haveCombined && arr[1] == arr[2]&&arr[1]&&arr[2]) {
         CombineValue(arr, 1, 2);
         calculateScore(arr[1]);
         haveCombined = true;
         PushtoTop(arr);
      }
       else if(!haveCombined && arr[0] == arr[1]&&arr[0]&&arr[1]){
         CombineValue(arr, 0, 1);
         calculateScore(arr[0]);
         haveCombined = true;
         PushtoTop(arr);
      }
}
void PushtoBottom(int * arr){
  int j = 0;
    int *Occupied_Series;
    int CntNonZero = nonEmptyNumber(arr); 
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
    
    free(Occupied_Series); 
}

void move_down_column(int * arr){
 bool haveCombined = false;
     PushtoBottom(arr);
      if(arr[2] == arr[3]&&arr[2]&&arr[3]) {
         CombineValue(arr, 2, 3);
         haveCombined = true;
         calculateScore(arr[2]);
         PushtoBottom(arr);
      }
       else if(!haveCombined && arr[1] == arr[2]&&arr[1]&&arr[2]) {
         CombineValue(arr, 1, 2);
         haveCombined = true;
         calculateScore(arr[1]);
         PushtoBottom(arr);
      }
       else if(!haveCombined && arr[0] == arr[1]&&arr[0]&&arr[1]){
         CombineValue(arr, 0, 1);
         haveCombined = true;
         calculateScore(arr[0]);
         PushtoBottom(arr);
      }

}




void move_up() {
    int haveCombined[SIZE];
    init_zero(haveCombined);

    
    int column_1[SIZE], column_2[SIZE], column_3[SIZE], column_4[SIZE];
    for (int i = 0; i < SIZE; i++) {
        column_1[i] = board[i][0];
        column_2[i] = board[i][1];
        column_3[i] = board[i][2];
        column_4[i] = board[i][3];
    }

   
    move_up_column(column_1);
    move_up_column(column_2);
    move_up_column(column_3);
    move_up_column(column_4);

    
    for (int i = 0; i < SIZE; i++) {
        board[i][0] = column_1[i];
        board[i][1] = column_2[i];
        board[i][2] = column_3[i];
        board[i][3] = column_4[i];
    }
}
void move_down() {
 
    int haveCombined[SIZE];
    init_zero(haveCombined);

    
    int column_1[SIZE], column_2[SIZE], column_3[SIZE], column_4[SIZE];
    for (int i = SIZE - 1; i >= 0; i--) {
        column_1[i] = board[SIZE - 1 - i][0];
        column_2[i] = board[SIZE - 1 - i][1];
        column_3[i] = board[SIZE - 1 - i][2];
        column_4[i] = board[SIZE - 1 - i][3];
    }

    
    move_down_column(column_1);
    move_down_column(column_2);
    move_down_column(column_3);
    move_down_column(column_4);

    
    for (int i = 0; i < SIZE; i++) {
        board[SIZE - 1 - i][0] = column_1[i];
        board[SIZE - 1 - i][1] = column_2[i];
        board[SIZE - 1 - i][2] = column_3[i];
        board[SIZE - 1 - i][3] = column_4[i];
    }
}

void PushtoLeft(int *arr) {
    int j = 0;
    int *Occupied_Series;
    int CntNonZero = nonEmptyNumber(arr); 
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
    
    free(Occupied_Series); 
}

void move_left_row(int * arr){
    bool haveCombined = false;
     PushtoLeft(arr);
      if(arr[2] == arr[3]&&arr[2]&&arr[3]) {
         CombineValue(arr, 2, 3);
         haveCombined = true;
         calculateScore(arr[2]);
          PushtoLeft(arr);
      }
       else if(!haveCombined && arr[1] == arr[2]&&arr[1]&&arr[2]) {
         CombineValue(arr, 1, 2);
         haveCombined = true;
         calculateScore(arr[1]);
         PushtoLeft(arr);
      }
       else if(!haveCombined && arr[0] == arr[1]&&arr[0]&&arr[1]){
         CombineValue(arr, 0, 1);
         haveCombined = true;
         calculateScore(arr[0]);
          PushtoLeft(arr);
      }

}

void move_left(){
   
    
    int row_1[SIZE], row_2[SIZE], row_3[SIZE], row_4[SIZE];
    for (int i = 0; i < SIZE; i++) {
        row_1[i] = board[0][i];
        row_2[i] = board[1][i];
        row_3[i] = board[2][i];
        row_4[i] = board[3][i];
    }

    
    move_left_row(row_1);
    move_left_row(row_2);
    move_left_row(row_3);
    move_left_row(row_4);

    
    for (int i = 0; i < SIZE; i++) {
        board[0][i] = row_1[i];
        board[1][i] = row_2[i];
        board[2][i] = row_3[i];
        board[3][i] = row_4[i];
    }
}

void PushtoRight(int * arr){
 int j = 0;
    int *Occupied_Series;
    int CntNonZero = nonEmptyNumber(arr); 
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
    
    free(Occupied_Series); 

}

void move_right_row(int * arr){
  bool haveCombined = false;
     PushtoRight(arr);
      if(arr[2] == arr[3]&&arr[2]&&arr[3]) {
         CombineValue(arr, 2, 3);
         haveCombined = true;
         calculateScore(arr[2]);
         PushtoRight(arr);
      }
       else if(!haveCombined && arr[1] == arr[2]&&arr[1]&&arr[2]) {
         CombineValue(arr, 1, 2);
         haveCombined = true;
         calculateScore(arr[1]);
         PushtoRight(arr);
      }
       else if(!haveCombined && arr[0] == arr[1]&&arr[0]&&arr[1]){
         CombineValue(arr, 0, 1);
         haveCombined = true;
         calculateScore(arr[0]);
          PushtoRight(arr);
      }


}

void move_right(){
  
    int row_1[SIZE], row_2[SIZE], row_3[SIZE], row_4[SIZE];
    for (int i = 0; i < SIZE; i++) {
        row_1[i] = board[0][SIZE - i - 1];
        row_2[i] = board[1][SIZE - i - 1];
        row_3[i] = board[2][SIZE - i - 1];
        row_4[i] = board[3][SIZE - i - 1];
    }

  
    move_right_row(row_1);
    move_right_row(row_2);
    move_right_row(row_3);
    move_right_row(row_4);

 
    for (int i = 0; i < SIZE; i++) {
        board[0][SIZE - i - 1] = row_1[i];
        board[1][SIZE - i - 1] = row_2[i];
        board[2][SIZE - i - 1] = row_3[i];
        board[3][SIZE - i - 1] = row_4[i];
    }
}
// game board 

void calculateScore(int valueCombined){

     Score += valueCombined;

}

//initialize the board
void init_board() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

//spawn 2 or 4
void init_spawn_block() {
    int empty_count = 0;
    int empty_index[SIZE * SIZE][2];

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                empty_index[empty_count][0] = i;
                empty_index[empty_count][1] = j;
                empty_count++;
            }
        }
    }

    if (empty_count > 0) {
        int index = rand() % empty_count;
        int value = (rand() % 2 + 1) * 2; //spawn 2 or 4
        board[empty_index[index][0]][empty_index[index][1]] = value;
    }
}


void print_board() {
    system("clear"); // clear the terminal
    printf("2048 Game\n\n");
    for (int i = 0; i < SIZE; i++) {
      
        printf("+------+------+------+------+\n");
        for (int j = 0; j < SIZE; j++) {
            
            print_number(board[i][j]);
            //printf("| %-4d ", board[i][j]);
        }
       
        printf("|\n");
    }
   
    printf("+------+------+------+------+\n");
}


// check if the game ends 
int check_game_over() {
    
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return 0;
            }
        }
    }

    // check if the adjacent blocks can be combined
    for (int i = 0; i < SIZE - 1; i++) {
        for (int j = 0; j < SIZE - 1; j++) {
            if (board[i][j] == board[i+1][j] || board[i][j] == board[i][j+1]) {
                return 0;
            }
        }
    }

    return 1;
}

void spawn_block(char Mode){
   if(Mode == 'h' || Mode == 'H')
    spawn_block_hard();
    else 
    spawn_block_easy();
}


void spawn_block_hard(){
   int pop_value = 2; 
   //pop 2 at each move
   int empty_positions[SIZE * SIZE][2];
    int empty_count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                empty_positions[empty_count][0] = i;
                empty_positions[empty_count][1] = j;
                empty_count++;
            }
        }
    }
    
    if (empty_count > 0) {
        srand(time(NULL)); 
        int index = rand() % empty_count;
        int x = empty_positions[index][0];
        int y = empty_positions[index][1];
        board[x][y] = pop_value;
    }
}
void spawn_block_easy() {
    
    int min_value = min_board();

    
    int empty_positions[SIZE * SIZE][2];
    int empty_count = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                empty_positions[empty_count][0] = i;
                empty_positions[empty_count][1] = j;
                empty_count++;
            }
        }
    }

    
    if (empty_count > 0) {
        srand(time(NULL)); 
        int index = rand() % empty_count;
        int value = (rand() % 2 == 0) ? min_value : min_value * 2; 
        int x = empty_positions[index][0];
        int y = empty_positions[index][1];
        board[x][y] = value;
    }
}

void reset_game(){
   game_over = false;
}

void quit_game(){
   printf("bye bye\n");
   game_over = true;
    if (Score > BestScore) {
        BestScore = Score;
        printf("New best score: %d\n", BestScore);
    }
    else
       printf("you didn't break the record" );
}
bool is_mode_valid = true;
void read_mode();
void read_mode() {
    char Mode;
    bool is_mode_valid = true;

    while (is_mode_valid) {
        printf("Enter the mode (H/h for hard, E/e for easy):\n");
        do {
            Mode = getchar();
        } while (Mode == ' ' || Mode == '\n');
        
        if (Mode == 'h' || Mode == 'H') {
            printf("You chose Hard mode.\n");
            is_mode_valid = false;
        } else if (Mode == 'e' || Mode == 'E') {
            printf("You chose Easy mode.\n");
            is_mode_valid = false;
        } else {
            printf("Invalid option. Please enter 'H' or 'E'.\n");
        }
    }
        printf("game start\n");
}

void reset_entrance() {
    printf("Try again? Y/N\n");
    char opt;
    //ignore
    do {
        opt = getchar();
    } while (opt == ' ' || opt == '\n');

    if (opt == 'Y' || opt == 'y') {
        reset_game();
    } else if (opt == 'N' || opt == 'n') {
        quit_game();
    } else {
        printf("Invalid option.\n");
        while (getchar() != '\n');
        reset_game();
    }
}
//return the minimum in the board
int min_board() {
    int min_value = 4096; // Initialize with maximum possible value
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] != 0 && board[i][j] < min_value) {
                min_value = board[i][j];
            }
        }
    }
    return min_value;
}
void show_score();
void show_score(){
    printf("total Score: %d ",Score);
}
void show_best_score();
void show_best_score(){
  
}
void new_line();
void new_line(){
    printf("\n");
}
int main() {
    while(!game_over){
    bool init_show_score = true;
    srand(time(NULL)); // time seed
    init_board();
    init_spawn_block();
    init_spawn_block();
    print_board();
    if(init_show_score){
        show_score();
        new_line();
        init_show_score = false;
    }
    if(init_show_mode){
        read_mode();
        new_line();
        init_show_mode = false;
    }
    char input;
   getchar();
    while (1) {
        input = getchar();
        while (getchar() != '\n');
        if (input == 'w' || input == 'W') {
            move_up();
           // spawn_block(Mode);
              spawn_block_hard();
            print_board();
            show_score();
            new_line();
            
        } else if (input == 's' || input == 'S') {
            move_down();
            //spawn_block(Mode);
              spawn_block_hard();
            print_board();
             show_score();
            new_line();
        } else if (input == 'a' || input == 'A') {
            move_left();
           // spawn_block(Mode);
           spawn_block_hard();
            print_board();
             show_score();
           new_line();
        } else if (input == 'd' || input == 'D') {
            move_right();
            //spawn_block(Mode);
              spawn_block_hard();
            print_board();
            show_score();
            new_line();
            
        }
          else if (input == 'q' ) {
           quit_game();
        }
        if (check_game_over()) {
            printf("Game Over!\n");
            Score = 0;
            break;
        }
     }
     reset_entrance();
    }
    return 0;
}


//record the round, and the minimum or maximum element of the baord, judge the random number to be generated.