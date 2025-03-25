#include <stdio.h>

struct Process{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};

void sortByArrivalTime(struct Process p[], int n){
    struct Process temp;
    for(int i=0;i<n-1;i++){
        for(int j=0; j<n-i-1; j++){
            if(p[j].at>p[j+1].at){
                temp=p[j];
                p[j]=p[j+1];
                p[j+1]=temp;
            }
        }
    }
}

void calculateTime(struct Process p[], int n) {
    int time = 0;

    for (int i = 0; i < n; i++) {
        if (time < p[i].at) {
            time = p[i].at;  // If CPU is idle, move time forward
        }

        p[i].ct = time + p[i].bt;  // Completion Time
        time = p[i].ct;  // Update current time

        p[i].tat = p[i].ct - p[i].at;  // Turnaround Time
        p[i].wt = p[i].tat - p[i].bt;  // Waiting Time
    }
}

void printGaantChart(struct Process p[], int n) {
    printf("\nGaant Chart:\n");
    printf(" ");

    for (int i = 0; i < n; i++) {
        printf("-------");
    }
    printf("\n|");

    for (int i = 0; i < n; i++) {
        printf(" P%d |", p[i].pid);
    }
    printf("\n ");

    for (int i = 0; i < n; i++) {
        printf("-------");
    }
    printf("\n0");

    for (int i = 0; i < n; i++) {
        printf("      %d", p[i].ct);
    }
    printf("\n");
}

void printProcessTable(struct Process p[], int n) {
    printf("\nProcesses  AT  BT  CT  TAT  WT\n");
    for (int i = 0; i < n; i++) {
        printf("   P%d      %d   %d   %d   %d   %d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    float avgTAT;
    float sumTAT;

    float avgWT;
    float sumWT;

    for(int i=0; i<n; i++){
        sumTAT+=p[i].tat;
    }
    avgTAT=sumTAT/n;

    for(int i=0; i<n; i++){
        sumWT+=p[i].wt;
    }
    avgWT=sumWT/n;

    printf("Average Turn Around Time: %f\n", avgTAT);
    printf("Average Waiting Time: %f\n", avgWT);
}

int main() {
    int n;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    // Input Process details
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for Process P%d: ", i + 1);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }

    // Sort processes based on Arrival Time
    sortByArrivalTime(p, n);

    // Calculate Completion Time, Turnaround Time, and Waiting Time
    calculateTime(p, n);

    // Print Process Table
    printProcessTable(p, n);

    // Print Gantt Chart
    printGaantChart(p, n);

    return 0;
}
