#include <stdio.h>

struct Process {
    int id;
    int burst_time;
    int priority;
    int arrival_time;
    int remaining_time;
    int start_time;
    int end_time;
    int waiting_time;
    int turnaround_time;
};

// Function to find the process with the highest priority (lowest number) and that is ready to execute
int find_highest_priority_process(struct Process p[], int n, int current_time) {
    int highest_priority = 9999;
    int index = -1;

    for (int i = 0; i < n; i++) {
        if (p[i].arrival_time <= current_time && p[i].remaining_time > 0 && p[i].priority < highest_priority) {
            highest_priority = p[i].priority;
            index = i;
        }
    }

    return index;
}

void priority_scheduling(struct Process p[], int n) {
    int current_time = 0;
    int completed = 0;

    // Execute processes until all are completed
    while (completed < n) {
        int index = find_highest_priority_process(p, n, current_time);
        if (index == -1) {  // No process is ready to execute
            current_time++;
            continue;
        }

        // Process execution
        if (p[index].remaining_time == p[index].burst_time) {
            p[index].start_time = current_time;
        }

        // Execute the process for one unit of time
        current_time++;
        p[index].remaining_time--;

        // If the process is completed
        if (p[index].remaining_time == 0) {
            p[index].end_time = current_time;
            p[index].turnaround_time = p[index].end_time - p[index].arrival_time;
            p[index].waiting_time = p[index].turnaround_time - p[index].burst_time;
            completed++;
        }
    }
}

void print_results(struct Process p[], int n) {
    printf("Process ID | Arrival Time | Burst Time | Priority | Waiting Time | Turnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
            p[i].id, p[i].arrival_time, p[i].burst_time, p[i].priority, p[i].waiting_time, p[i].turnaround_time);
    }
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input for processes
    for (int i = 0; i < n; i++) {
        p[i].id = i + 1;
        printf("\nEnter Arrival Time, Burst Time, and Priority for Process P%d:\n", i + 1);
        printf("Arrival Time: ");
        scanf("%d", &p[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &p[i].burst_time);
        printf("Priority: ");
        scanf("%d", &p[i].priority);

        p[i].remaining_time = p[i].burst_time;
    }

    // Perform priority scheduling
    priority_scheduling(p, n);

    // Print the results
    print_results(p, n);

    return 0;
}

