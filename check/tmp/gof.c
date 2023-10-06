#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 80
#define HEIGHT 25
#define DELAY 100000 // микросекунды


void draw_board(char board[HEIGHT][WIDTH]) {
    system("clear"); // очистка терминала
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            printf("%c", board[i][j]);
        }
        printf("\n");
    }
}

void update_board(char board[HEIGHT][WIDTH]) {
    char new_board[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            int count = 0;
            // Подсчет количества живых соседей
            for (int x = -1; x <= 1; x++) {
                for (int y = -1; y <= 1; y++) {
                    if (x == 0 && y == 0) continue;
                    int ni = (i + x + HEIGHT) % HEIGHT;
                    int nj = (j + y + WIDTH) % WIDTH;
                    if (board[ni][nj] == '#') count++;
                }
            }
            // Применение правил игры "Жизнь"
            if (board[i][j] == '#') {
                if (count == 2 || count == 3) new_board[i][j] = '#';
                else new_board[i][j] = '.';
            } else {
                if (count == 3) new_board[i][j] = '#';
                else new_board[i][j] = '.';
            }
        }
    }
    // Копирование нового состояния поля в оригинальное поле
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = new_board[i][j];
        }
    }
}

int main() {
    char board[HEIGHT][WIDTH];
    // Инициализация поля через stdin
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            scanf(" %c", &board[i][j]);
        }
    }
    // Основной цикл игры
    while (1) {
        draw_board(board);
        update_board(board);
        usleep(DELAY); // задержка
    }
    return 0;
}