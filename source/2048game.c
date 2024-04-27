#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "colorfulNumber.h"
#include <unistd.h>
#include <termios.h>
#include "clear.h"
#include "input_ctrl.h"
void set_input_mode() {
    struct termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~(ICANON | ECHO);  // Disable canonical mode and echoing
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
}//set input mode as raw input;

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
bool is_force = false;

/*---------------------------MACRO---------------------------*/
/*---------------------------FUNCTION---------------------------*/
void calculateScore(int valueCombined);
void move_up_column(int * arr);
void move_down_column(int * arr);
void move_left_row(int * arr);
void move_right_row(int * arr);

void force_quit_game();
bool isEmptyBound(Board board,char Direction); 
int nonEmptyNumber(int * arr);

void PushtoTop(int * arr);
void PushtoLeft(int *arr);
void PushtoRight(int * arr);
void PushtoBottom(int * arr);

void CombineValue(int * arr,int index_1,int index_2);

//OccupiedSeries getNumberBlock(Board board); //return a series of non-empty block in the board
void init_zero(int *arr);
void move_left();
int min_board();
void spawn_block_easy();
void reset_game();
void move_right();
void reset_entrance();
void quit_game();
void spawn_block_hard();
void spawn_block(char Mode);
void delay_250ms();
/*---------------------------FUNCTION---------------------------*/
 void delay_250ms(){
    usleep(250000); // 休眠 0.25 秒
}

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
void move_up_column(int * arr){
     //bool haveCombined = false;
     
    if(nonEmptyNumber(arr) == SIZE){
     PushtoTop(arr);
      if(arr[2] == arr[3]&&arr[2]&&arr[3]) {
         CombineValue(arr, 2, 3);
         calculateScore(arr[3]);
        // haveCombined = true;
         PushtoTop(arr);
      }
     if(/*!haveCombined &&*/ arr[1] == arr[2]&&arr[1]&&arr[2]) {
         CombineValue(arr, 1, 2);
         calculateScore(arr[2]);
        // haveCombined = true;
         PushtoTop(arr);
      }
      if(/*!haveCombined &&*/ arr[0] == arr[1]&&arr[0]&&arr[1]){
         CombineValue(arr, 0, 1);
         calculateScore(arr[1]);
         //haveCombined = true;
         PushtoTop(arr);
      }
    }
    else{
        bool haveCombined = false; 

    
    PushtoTop(arr);

    
    for (int i = 1; i < SIZE; i++) {
        if (arr[i] == arr[i - 1] && arr[i] != 0 && !haveCombined) { 
            CombineValue(arr, i, i - 1); 
             calculateScore(arr[i]);
            haveCombined = true; 
            PushtoTop(arr); 
        } else {
            haveCombined = false;
        }
    }
    }
}  
/*fix log:My roommate finds that for case that[2,2,4,4] then oush left should have [4,8,0,0] instead of [2,2,8,8]*/
/*multiple combinations should be allowed*/
/*case like [4,2,2,0] and slides left. [4,4,0,0] instead of [8,0,0,0]*/
void CombineValue(int * arr,int index_1,int index_2){
    arr[index_1] = 2 * arr[index_1] ;
    arr[index_2] = 0;
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
 //bool haveCombined = false;
 if(nonEmptyNumber(arr) == SIZE){
     PushtoBottom(arr);
      if(arr[2] == arr[3]&&arr[2]&&arr[3]) {
         CombineValue(arr, 2, 3);
         /*haveCombined = true;*/
         calculateScore(arr[2]);
         PushtoBottom(arr);
      }
        if(/*!haveCombined &&*/ arr[1] == arr[2]&&arr[1]&&arr[2]) {
         CombineValue(arr, 1, 2);
        /*haveCombined = true;*/
         calculateScore(arr[1]);
         PushtoBottom(arr);
      }
        if(/*!haveCombined && */arr[0] == arr[1]&&arr[0]&&arr[1]){
         CombineValue(arr, 0, 1);
        /*haveCombined = true;*/
         calculateScore(arr[0]);
         PushtoBottom(arr);
      }
   }
else{
     bool haveCombined = false; 


    PushtoTop(arr);

   
    for (int i = 1; i < SIZE; i++) {
        if (arr[i] == arr[i - 1] && arr[i] != 0 && !haveCombined) { 
            CombineValue(arr, i, i - 1); 
            haveCombined = true; 
            calculateScore(arr[i]);
            PushtoTop(arr); 
        } else {
            haveCombined = false; 
        }
    }
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
    if(nonEmptyNumber(arr) == SIZE){
        /* bool haveCombined = false;*/
     PushtoLeft(arr);
      if(arr[2] == arr[3]&&arr[2]&&arr[3]) {
         CombineValue(arr, 2, 3);
        /* bool haveCombined = false;*/
         calculateScore(arr[2]);
          PushtoLeft(arr);
      }
       if(/*!haveCombined &&*/ arr[1] == arr[2]&&arr[1]&&arr[2]) {
         CombineValue(arr, 1, 2);
         /* bool haveCombined = false;*/
         calculateScore(arr[1]);
         PushtoLeft(arr);
      }
        if(/*!haveCombined &&*/ arr[0] == arr[1]&&arr[0]&&arr[1]){
         CombineValue(arr, 0, 1);
        /* bool haveCombined = false;*/
         calculateScore(arr[0]);
          PushtoLeft(arr);
      }
    }
    else{
     bool haveCombined = false; 


    PushtoTop(arr);

    
    for (int i = 1; i < SIZE; i++) {
        if (arr[i] == arr[i - 1] && arr[i] != 0 && !haveCombined) { 
            CombineValue(arr, i, i - 1); 
            haveCombined = true; 
            calculateScore(arr[i]);
            PushtoTop(arr); 
        } else {
            haveCombined = false; 
        }
    }
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
    if(nonEmptyNumber(arr) == SIZE){
  /* haveCombined = true;*/
     PushtoRight(arr);
      if(arr[2] == arr[3]&&arr[2]&&arr[3]) {
         CombineValue(arr, 2, 3);
        /* haveCombined = true;*/
         calculateScore(arr[2]);
         PushtoRight(arr);
      }
     if(/* haveCombined = true;*/arr[1] == arr[2]&&arr[1]&&arr[2]) {
         CombineValue(arr, 1, 2);
        /* haveCombined = true;*/
         calculateScore(arr[1]);
         PushtoRight(arr);
      }
     if(/* haveCombined = true;*/ arr[0] == arr[1]&&arr[0]&&arr[1]){
         CombineValue(arr, 0, 1);
         /* haveCombined = true;*/
         calculateScore(arr[0]);
          PushtoRight(arr);
      }

    }
    else{
         bool haveCombined = false; 
    
    PushtoTop(arr);

    
    for (int i = 1; i < SIZE; i++) {
        if (arr[i] == arr[i - 1] && arr[i] != 0 && !haveCombined) { 
            CombineValue(arr, i, i - 1); 
            haveCombined = true; 
            calculateScore(arr[i]);
            PushtoTop(arr);
        } else {
            haveCombined = false; 
        }
    }
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
    clear_screen(); // clear the terminal
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
        print_board();
        printf("New best score: %d\n", BestScore);
    }
    else
       print_board();
       printf("you didn't break the record" );
}
void force_quit_game(){
    print_board();
    printf("\nYou quit the game\n");
    usleep(2500000);
    game_over = true;
    is_force = true;
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
    char opt;
    do {
        printf("Try again? Y/N\n");
        // Ignore whitespace and newline characters
        do {
            opt = getchar();
        } while (opt == ' ' || opt == '\n');

        if (opt == 'Y' || opt == 'y') {
            reset_game();
            break; // Break out of the loop if the input is valid
        } else if (opt == 'N' || opt == 'n') {
            quit_game();
            break; // Break out of the loop if the input is valid
        } else {
            printf("Invalid option.\n");
            // Clear input buffer
            while (getchar() != '\n');
        }
    } while (1); // Continue looping until a valid input is provided
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
    set_input_mode();
    bool init_show_score = true;
    bool init_show_mode = true;
    is_force = false;
    srand(time(NULL)); // time seed
    init_board();
    init_spawn_block();
    init_spawn_block();
    print_board();

    if (init_show_score) {
        show_score();
        new_line();
        init_show_score = false;
    }

    if (init_show_mode) {
        read_mode(); 
        new_line();
        init_show_mode = false;
    }

    char input;

    do {

        if (read(STDIN_FILENO, &input, 1) == 1) {
            if (input == 'q') {
               force_quit_game();

            } else if (input == 'w' || input == 'W') {
                move_up();
            } else if (input == 's' || input == 'S') {
                move_down();
            } else if (input == 'a' || input == 'A') {
                move_left();
            } else if (input == 'd' || input == 'D') {
                move_right();
            }

            delay_250ms();
            spawn_block_hard();
            print_board();
            if(!is_force)
            show_score();
            new_line();

            if (check_game_over()) {
                printf("Game Over!\n");
                Score = 0;
                break;
            }
        }

    }while (!game_over);
    if(!is_force)
    reset_entrance();
    /*if(is_force){
       usleep(250000000);
    }*/
    clear_screen();
    return 0;
}


//record the round, and the minimum or maximum element of the baord, judge the random number to be generated.
//fix_log_2