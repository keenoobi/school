#include <stdio.h>
#include <unistd.h>

#define ROWS 25
#define COLS 80

void updateGrid(int grid[ROWS][COLS]) {
    int newGrid[ROWS][COLS];
    int i, j, liveNeighbors;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            liveNeighbors = 0;

            // Count live neighbors
            if (i > 0 && j > 0 && grid[i - 1][j - 1] == 1)
                liveNeighbors++;
            // Check other neighbors...

            // Apply rules of Game of Life
            if (grid[i][j] == 1 && (liveNeighbors < 2 || liveNeighbors > 3))
                newGrid[i][j] = 0;
            else if (grid[i][j] == 0 && liveNeighbors == 3)
                newGrid[i][j] = 1;
            else
                newGrid[i][j] = grid[i][j];
        }
    }

    // Update the grid
    for (i = 0; i < ROWS; i++)
        for (j = 0; j < COLS; j++)
            grid[i][j] = newGrid[i][j];
}

void printGrid(int grid[ROWS][COLS]) {
    int i, j;

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            if (grid[i][j] == 1)
                printf("*");
            else
                printf(".");
        }
        printf("\n");
    }
}

int main() {
    int grid[ROWS][COLS] = {0}; // Initialize grid with all dead cells

    // Set initial live cells...
    
    // Game loop
    while (1) {
        printGrid(grid);
        updateGrid(grid);
        usleep(500000); // Delay for 0.5 seconds
    }

    return 0;
}
