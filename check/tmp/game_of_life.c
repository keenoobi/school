#include <stdio.h>

#define WIDTH 80
#define HEIGHT 25

void drawBoard(char board[HEIGHT][WIDTH]) {
    // Очистка экрана
   // system("clear");
    
    // Отрисовка игрового поля
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (board[i][j] == 1) {
                printf("*");
            } else {
                printf(" ");
            }
        }
        printf("\n");
    }
}

int main(){
    char board[HEIGHT][WIDTH];
}
















































// int main() {
//     char pole [HEIGHT][WIDTH];
// }
// void initializing_space(char pole [HEIGHT][WIDTH]) {
//     for (int i = 0; i < HEIGHT; i++) {
//         for (int j = 0; j < WIDTH; j++) {
//             scanf(" %c", &pole[i][j]);
//         }
//     }
// }
// void printing_space (char pole [HEIGHT][WIDTH]){
//         for (int i = 0; i < HEIGHT; i++) {
//         for (int j = 0; j < WIDTH; j++) {
//             printf(" %c", &pole[i][j]);
//         }
//     }
// }

// main 