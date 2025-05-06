#include <stdio.h>
#include <stdbool.h>

#define P 4  // Number of processes
#define R 3  // Number of resources

int main() {
    int alloc[P][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 3},
        {2, 1, 1}
    };

    int request[P][R] = {
        {0, 0, 0},
        {1, 0, 2},
        {0, 0, 0},
        {0, 0, 2}
    };

    int avail[R] = {1, 1, 0};  // Available resources

    bool finish[P] = {false};
    for (int i = 0; i < P; i++) {
        bool canFinish = true;
        for (int j = 0; j < R; j++) {
            if (request[i][j] > avail[j]) {
                canFinish = false;
                break;
            }
        }

        if (canFinish) {
            finish[i] = true;
            for (int j = 0; j < R; j++) {
                avail[j] += alloc[i][j];  // Simulate releasing
            }
            i = -1;  // Restart check from beginning
        }
    }

    bool deadlock = false;
    for (int i = 0; i < P; i++) {
        if (!finish[i]) {
            printf("Process %d is in deadlock.\n", i);
            deadlock = true;
        }
    }

    if (!deadlock)
        printf("No deadlock detected.\n");

    return 0;
}
