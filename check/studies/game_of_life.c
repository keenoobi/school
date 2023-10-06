#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>

#define HEIGHT 25        //высота матрицы
#define WIDTH 80         //ширина матрицы
#define DELAY_MIN 1      //предел задержки итерации
#define DELAY_MAX 10000  //предел задержки итерации
#define DELAY_STEP 10    //шаг регулирования задержки итерации

unsigned int time();  // нужно для обновления последовательности псевдослучайных чисел

void copy_matrix(int* matrix_origin, int* matrix_recipient);
void print_matrix(int* matrix_in, int count_step, int cur_delay);
void random_matrix(int* matrix);
int number_living_neighbors(int* matrix, int i);
int checking_exit(int* matrix_main, int* matrix_buf, int* matrix_history);
int is_live(int* matrix, int i);
void generation_next(int* matrix_main, int* matrix_buf, int* matrix_history);
int have_alive(int* matrix);
int compare_matrix(int* matrix_1, int* matrix_2);
void stdin_matrix(int* matrix);

int main() {
    int matrix_main[HEIGHT][WIDTH];           //матрица текущего состояния
    int matrix_buf[HEIGHT][WIDTH] = {0};      //матрица прошлого состояния
    int matrix_history[HEIGHT][WIDTH] = {0};  //матрица предпрошлого состояния
    int count_step = 1;                       //номер итерации
    int cur_delay = 200;                      //задержка итерации

    stdin_matrix((int*)matrix_main);  //считываю массив

    stdin = freopen("/dev/tty", "r", stdin);  //переключаем поток
    initscr();
    //    cbreak();
    noecho();      //отключить вывод набранного символа
    halfdelay(1);  //автореакция 1млсек

    srand(time(NULL));  //обновляю цепочку псевдослучайных чисел

    //    random_matrix((int*)matrix_main);                         //ицициализирую набор рандомом
    print_matrix((int*)matrix_main, count_step, cur_delay);  //отрисовываю исходную таблицу

    while (checking_exit((int*)matrix_main, (int*)matrix_buf, (int*)matrix_history) == 1) {
        int ch = getch();
        if (ch == 'x') {
            if (cur_delay > DELAY_MIN + DELAY_STEP) cur_delay = cur_delay - DELAY_STEP;
        } else if (ch == 'z') {
            if (cur_delay < DELAY_MAX - DELAY_STEP) cur_delay = cur_delay + DELAY_STEP;
        } else if (ch == 'q')
            return 0;

        generation_next((int*)matrix_main, (int*)matrix_buf, (int*)matrix_history);
        clear();
        print_matrix((int*)matrix_main, count_step, cur_delay);
        count_step++;
        refresh();
        delay_output(cur_delay);
    }
    return 0;
}

//копирование матрицы; на входе матрицы источник и получатель
void copy_matrix(int* matrix_origin, int* matrix_recipient) {
    for (int i = 0; i < HEIGHT * WIDTH; i++) {
        matrix_recipient[i] = matrix_origin[i];
    }
}

//проверяет условия выживания клетке. на входе: матрица и номер элемента. на выходе: новое состояние клетки
int is_live(int* matrix, int i) {
    int living_neighbors = number_living_neighbors(matrix, i);
    int am_i_alive = *(matrix + i);

    if (living_neighbors == 3) return 1;
    if (living_neighbors == 2 && am_i_alive == 1) return 1;
    return 0;
}

//определяет количество живых соседей для точки
int number_living_neighbors(int* matrix, int i) {
    int aliveNeighbors = 0;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            int neighbor_index =
                ((i / WIDTH + x + HEIGHT) % HEIGHT) * WIDTH + (i % WIDTH + y + WIDTH) % WIDTH;
            if (!(x == 0 && y == 0) && matrix[neighbor_index] == 1) aliveNeighbors++;
        }
    }
    return aliveNeighbors;
}

//отрисовка матрицы
void print_matrix(int* matrix_in, int count_step, int cur_delay) {
    //    system("clear");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            switch (matrix_in[i * WIDTH + j]) {
                case 0:
                    printw(" ");
                    break;
                case 1:
                    printw("#");
                    break;
                default:
                    printw("?");
                    break;
            }
        }
        printw("\n");
    }
    printw("\nz - speed down; x - speed up; q - quit\n");
    printw("current delay: %dms\ngeneration number: %d\n", cur_delay, count_step);
}

//рандомное заполнение исходного состояния
void random_matrix(int* matrix) {
    for (int i = 0; i < (HEIGHT * WIDTH); i++) {
        matrix[i] = rand() % 2;
    }
}

//генерация нового поколения; на входе основная и буферная массивы
void generation_next(int* matrix_main, int* matrix_buf, int* matrix_history) {
    copy_matrix(matrix_buf, matrix_history);
    copy_matrix(matrix_main, matrix_buf);
    for (int i = 0; i < HEIGHT * WIDTH; i++) {
        matrix_main[i] = is_live(matrix_buf, i);
    }
}

//проверка на выход
int checking_exit(int* matrix_main, int* matrix_buf, int* matrix_history) {
    if (have_alive(matrix_main) == 0 || compare_matrix(matrix_main, matrix_buf) == 0 ||
        compare_matrix(matrix_main, matrix_history) == 0)
        return 0;
    return 1;
}

//проверка наличия выживших (1 есть выжившие, 0 все мертвы)
int have_alive(int* matrix) {
    for (int i = 0; i < (HEIGHT * WIDTH); i++) {
        if (matrix[i] == 1) return 1;
    }
    return 0;
}

//сравнение матриц (1 есть хотя бы одно расхождение; 0 полное совпадение
int compare_matrix(int* matrix_1, int* matrix_2) {
    for (int i = 0; i < (HEIGHT * WIDTH); i++) {
        if (matrix_1[i] != matrix_2[i]) return 1;
    }
    return 0;
}

//заполнение матрицы стандартным вводом
void stdin_matrix(int* matrix) {
    float in_val;
    for (int i = 0; i < HEIGHT * WIDTH; i++) {
        if (scanf("%f", &in_val) == 1 && ((int)in_val == 1 || (int)in_val == 0)) {
            matrix[i] = (int)in_val;
        }
        if (i % WIDTH == 0) printf("\n");
    }
}
