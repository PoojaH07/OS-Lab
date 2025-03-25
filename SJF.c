

#include <stdio.h>

struct Process {
    int id, burst_time, remaining_time, waiting_time, turnaround_time, arrival_time, completion_time, response_time;
};

void sortByBurstTime(struct Process p[], int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (p[i].burst_time > p[j].burst_time) {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
}

void calculateTimes(struct Process p[], int n, int preemptive) {
    int total_time = 0, completed = 0;

    while (completed < n) {
        int min_remaining_time = 9999;
        int shortest = -1;

        for (int i = 0; i < n; i++) {
            if (p[i].arrival_time <= total_time && p[i].remaining_time > 0 && p[i].remaining_time < min_remaining_time) {
                min_remaining_time = p[i].remaining_time;
                shortest = i;
            }
        }

        if (shortest == -1) {
            total_time++;
            continue;
        }

        if (p[shortest].remaining_time == p[shortest].burst_time) {
            p[shortest].response_time = total_time - p[shortest].arrival_time;
        }

        p[shortest].remaining_time--;

        if (p[shortest].remaining_time == 0) {
            completed++;
            p[shortest].completion_time = total_time + 1;
            p[shortest].turnaround_time = p[shortest].completion_time - p[shortest].arrival_time;
            p[shortest].waiting_time = p[shortest].turnaround_time - p[shortest].burst_time;
        }

        total_time++;
    }
}

void sjfNonPreemptive(struct Process p[], int n) {
    sortByBurstTime(p, n);
    for (int i = 0; i < n; i++) p[i].remaining_time = p[i].burst_time;
    calculateTimes(p, n, 0);
}

void printResults(struct Process p[], int n) {
    printf("ID | AT  | BT  | CT  | TAT  | WT  | RT\n");
    for (int i = 0; i < n; i++) {
        printf("%2d | %3d | %3d | %3d | %4d | %3d | %2d\n", p[i].id, p[i].arrival_time, p[i].burst_time, p[i].completion_time,
               p[i].turnaround_time, p[i].waiting_time, p[i].response_time);
    }
}

int main() {
    int n, choice;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].id = i+1;
        printf("Burst & Arrival for process %d: ", i+1);
        scanf("%d %d", &p[i].burst_time, &p[i].arrival_time);
        p[i].remaining_time = p[i].burst_time;
    }

    printf("1. Non-preemptive SJF\n2. Preemptive SJF\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) sjfNonPreemptive(p, n);
    else calculateTimes(p, n, 1);

    printResults(p, n);
    return 0;
}
