#include <stdio.h>
#include <stdbool.h>

#define P 5 // Number of processes
#define R 3 // Number of resources

// Function to check if the system is in a safe state
bool isSafe(int processes[], int avail[], int max[][R], int allot[][R]) {
    int need[P][R];
    bool finish[P] = {false};
    int safeSeq[P];
    int work[R];
    int count = 0;

    // Calculate the need matrix
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allot[i][j];
        }
    }

    // Initialize work array to available resources
    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    // Find a safe sequence
    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                int j;
                for (j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        break;
                    }
                }
                if (j == R) {
                    // If all needs can be met
                    for (int k = 0; k < R; k++) {
                        work[k] += allot[p][k];
                    }
                    finish[p] = true;
                    safeSeq[count++] = p;
                    found = true;
                    break;
                }
            }
        }
        if (!found) {
            printf("System is in an unsafe state\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe Sequence: ");
    for (int i = 0; i < P; i++) {
        printf("%d ", safeSeq[i]);
    }
    printf("\n");

    return true;
}

int main() {
    // Number of processes and resources
    int processes[] = {0, 1, 2, 3, 4};

    // Available instances of resources
    int avail[] = {3, 3, 2};

    // Maximum R that can be requested by each process
    int max[][R] = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    // Allocation of resources to processes
    int allot[][R] = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    // Call the Banker's algorithm function to check if the system is in a safe state
    isSafe(processes, avail, max, allot);

    return 0;
}
