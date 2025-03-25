#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int remaining_time;
    int arrival_time;
    int waiting_time;
    int turnaround_time;
    int completion_time;
};

void round_robin(struct Process p[], int n, int quantum) {
    int current_time = 0;
    int completed = 0;
    int process_in_queue = 0; // Counter to track how many processes are waiting

    // Initialize remaining time for each process
    for (int i = 0; i < n; i++) {
        p[i].remaining_time = p[i].burst_time;
    }

    // Continue until all processes are completed
    while (completed < n) {
        int all_done = 1; // Flag to check if all processes are done
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_time > 0) {
                all_done = 0;
                // Check if the process can run
                int time_to_run = (p[i].remaining_time > quantum) ? quantum : p[i].remaining_time;
                p[i].remaining_time -= time_to_run;
                current_time += time_to_run;

                if (p[i].remaining_time == 0) {
                    p[i].completion_time = current_time;
                    p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
                    p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
                    completed++;
                }
            }
        }

        // If all processes are done, break out of the loop
        if (all_done) break;
    }
}

void print_results(struct Process p[], int n) {
    printf("Process ID | Arrival Time | Burst Time | Waiting Time | Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            p[i].id, p[i].arrival_time, p[i].burst_time, p[i].waiting_time, p[i].turnaround_time);
    }
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input process details
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nEnter Arrival Time and Burst Time for Process P%d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst_time);
    }

    // Set time quantum to 4
    int quantum = 4;

    // Perform Round Robin scheduling
    round_robin(p, n, quantum);

    // Print the results
    print_results(p, n);

    return 0;
}

