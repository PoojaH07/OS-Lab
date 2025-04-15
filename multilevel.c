#include <stdio.h>

#define MAX 10

typedef struct {
    int pid, arrival, burst;
} Process;

// Function to sort processes by arrival time
void sort_by_arrival(Process queue[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (queue[j].arrival > queue[j + 1].arrival) {
                Process temp = queue[j];
                queue[j] = queue[j + 1];
                queue[j + 1] = temp;
            }
        }
    }
}

// Function to execute FCFS scheduling
void fcfs(Process queue[], int n) {
    int time = 0;
    printf("PID\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n");

    for (int i = 0; i < n; i++) {
        if (time < queue[i].arrival)
            time = queue[i].arrival;
        int completion = time + queue[i].burst;
        int turnaround = completion - queue[i].arrival;
        int waiting = turnaround - queue[i].burst;
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", queue[i].pid, queue[i].arrival, queue[i].burst, completion, turnaround, waiting);
        time = completion;
    }
}

int main() {
    int n, sys_count = 0, user_count = 0;
    Process sys_queue[MAX], user_queue[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Process p;
        int type;
        printf("Enter PID, Arrival Time, Burst Time, Type (0=System, 1=User): ");
        scanf("%d %d %d %d", &p.pid, &p.arrival, &p.burst, &type);

        if (type == 0)
            sys_queue[sys_count++] = p;
        else
            user_queue[user_count++] = p;
    }

    // Sort both queues by arrival time
    sort_by_arrival(sys_queue, sys_count);
    sort_by_arrival(user_queue, user_count);

    // Execute system processes first
    printf("\nSystem Processes (Higher Priority)\n");
    fcfs(sys_queue, sys_count);

    // Execute user processes next
    printf("\nUser Processes (Lower Priority)\n");
    fcfs(user_queue, user_count);

    return 0;
}


