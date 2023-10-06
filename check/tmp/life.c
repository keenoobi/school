# include <stdio.h>
# include <stdlib.h>
# define HEIGHT 50
# define WIDTH 50

void copy_matrix(int* matrix_origin, int* matrix_recipient);
//void print_matrix(int matrix_in[3][3]);
void print_matrix2(int* matrix_in);
void random_matrix(int* matrix);
int number_living_neighbors(int* matrix, int i);
unsigned int time();
int is_live(int* matrix, int i);
void generation_next(int* matrix_main, int* matrix_buf);

int main() {
    int matrix_main[HEIGHT][WIDTH];
    int matrix_buf[HEIGHT][WIDTH];
    int stop = 0;
    
    srand(time(NULL));                  //обновляю цепочку псевдослучайных чисел
    random_matrix((int*)matrix_main);   //ицициализирую набор рандомом
    print_matrix2((int*)matrix_main);   //отрисовываю исходную таблицу
    
    while (stop == 0) {
        generation_next((int*)matrix_main, (int*)matrix_buf);
        print_matrix2((int*)matrix_main);
    }
}

//копирование матрицы; на входе матрицы источник и получатель
void copy_matrix(int* matrix_origin, int* matrix_recipient) {
    for (int i = 0; i < HEIGHT * WIDTH; i++) {
        matrix_recipient[i] = matrix_origin[i];
    }
}
/*
//пробежаться по массиву, принять решение: жить или умереть. перенес в функцию generation_next
void god_mode(int* main, int* buf) {
    for (int i = 0; i < HEIGTH * WIDTH; i++) {
        main[i] = is_live(buf, i);
    }
}
*/
//проверяет условия выживания клетке. на входе: матрица и номер элемента. на выходе: новое состояние клетки
int is_live(int* matrix, int i) {
    int living_neighbors = number_living_neighbors(matrix, i);
    int am_i_alive = *(matrix + i);
    
    if (living_neighbors == 3) return 1;
    if (living_neighbors ==2 && am_i_alive == 1) return 1;
    return 0;
}

//определяет количество живых соседей для точки
int number_living_neighbors(int* matrix, int i) {
    int aliveNeighbors = 0;
    for (int x = -1; x <= 1; x++) {
        for (int y = -1; y <= 1; y++) {
            int neighbor_index = ((i / WIDTH + x + HEIGHT) % HEIGHT) * WIDTH + (i % WIDTH + y + WIDTH) % WIDTH;
            if (!(x == 0 && y == 0) && matrix[neighbor_index] == 1) aliveNeighbors++;
        }
    }
    return aliveNeighbors;
}

//отрисовка с передачей указателя ВНИМАНИЕ -
void print_matrix2(int* matrix_in) {
    system("clear");
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
//            printf("%d", matrix_in[i*HIGTH+j]);
            switch (matrix_in[i*WIDTH+j]) {
               case 0: printf(" "); break;
                case 1: printf("#"); break;
                default: printf("?"); break;
            }
        }
        printf("\n");
    }
}

//рандомное заполнение исходного состояния
void random_matrix(int* matrix) {
    for (int i = 0; i < (HEIGHT * WIDTH); i++) {
        matrix[i] = rand()%2;
    }
}

//генерация нового поколения; на входе основная и буферная массивы
void generation_next(int* matrix_main, int* matrix_buf) {
    copy_matrix(matrix_main, matrix_buf);
    for (int i = 0; i < HEIGHT * WIDTH; i++) {
        matrix_main[i] = is_live(matrix_buf, i);
    }
    
}


