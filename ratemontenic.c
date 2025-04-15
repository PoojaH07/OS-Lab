#include <stdio.h>
#include <stdlib.h>

#define MAX 10

typedef struct {
    int id;
    int exec_time;
    int period;
    int deadline;
    int remaining_time;
    int instance;
    int share;
} Task;

void rate_monotonic(Task tasks[], int n, int simulation_time) {
    printf("\n--- Rate Monotonic Scheduling ---\n");
    for (int time = 0; time < simulation_time; time++) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (time % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].exec_time;
            }
            if (tasks[i].remaining_time > 0 &&
                (idx == -1 || tasks[i].period < tasks[idx].period)) {
                idx = i;
            }
        }
        if (idx != -1) {
            printf("Time %2d: Task %d\n", time, tasks[idx].id);
            tasks[idx].remaining_time--;
        } else {
            printf("Time %2d: Idle\n", time);
        }
    }
}

void earliest_deadline_first(Task tasks[], int n, int simulation_time) {
    printf("\n--- Earliest Deadline First Scheduling ---\n");
    for (int time = 0; time < simulation_time; time++) {
        int idx = -1;
        for (int i = 0; i < n; i++) {
            if (time % tasks[i].period == 0) {
                tasks[i].remaining_time = tasks[i].exec_time;
                tasks[i].deadline = time + tasks[i].period;
            }
            if (tasks[i].remaining_time > 0 &&
                (idx == -1 || tasks[i].deadline < tasks[idx].deadline)) {
                idx = i;
            }
        }
        if (idx != -1) {
            printf("Time %2d: Task %d\n", time, tasks[idx].id);
            tasks[idx].remaining_time--;
        } else {
            printf("Time %2d: Idle\n", time);
        }
    }
}

void proportional_scheduling(Task tasks[], int n, int simulation_time) {
    printf("\n--- Proportional Scheduling (Weighted Round Robin) ---\n");
    int time = 0;
    int i = 0;
    while (time < simulation_time) {
        if (tasks[i].remaining_time <= 0) {
            tasks[i].remaining_time = tasks[i].share;
        }

        int run_time = tasks[i].remaining_time < 1 ? 0 : 1;
        for (int j = 0; j < run_time && time < simulation_time; j++) {
            printf("Time %2d: Task %d\n", time, tasks[i].id);
            tasks[i].remaining_time--;
            time++;
        }
        i = (i + 1) % n;
    }
}

int main() {
    Task tasks[MAX];
    int n, simulation_time;

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    printf("Enter simulation time: ");
    scanf("%d", &simulation_time);

    for (int i = 0; i < n; i++) {
        tasks[i].id = i + 1;
        printf("\nTask %d\n", i + 1);
        printf("Enter execution time: ");
        scanf("%d", &tasks[i].exec_time);
        printf("Enter period (for RMS/EDF): ");
        scanf("%d", &tasks[i].period);
        printf("Enter share (for Proportional): ");
        scanf("%d", &tasks[i].share);

        tasks[i].remaining_time = 0;
        tasks[i].deadline = 0;
    }

    rate_monotonic(tasks, n, simulation_time);
    earliest_deadline_first(tasks, n, simulation_time);
    proportional_scheduling(tasks, n, simulation_time);

    return 0;
}
