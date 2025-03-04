//Ethan Roppel, 41753979

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turnaround_time;
    // I added this for the calculations
    int completion_time;
} Process;

int n; // Number of processes

// Function to find the process with the shortest remaining time
int findNextProcess(Process proc[], int current_time) {

    // Begin with the largest value possible 
    int min_time = INT_MAX;
    int index = -1;

    // Loop through processes
    for (int i = 0; i < n; i++) {

        // Check if next process has arrived and needs to be processed
        if (proc[i].arrival_time <= current_time && proc[i].remaining_time > 0) {

            // "queue up" process with the shortest remaining job
            if (proc[i].remaining_time < min_time) {
                min_time = proc[i].remaining_time;
                index = i;
            }
        }
    }

    // Index of shortest next process
    return index;
}

// Function to perform the SRTF scheduling
void srtf(Process proc[]) {
    int current_time = 0;
    int completed = 0;
    int prev = -1;

    // Initialize remaining times
    for (int i = 0; i < n; i++) {
        proc[i].remaining_time = proc[i].burst_time;
        proc[i].waiting_time = 0;
        proc[i].turnaround_time = 0;
        proc[i].completion_time = 0;
    }

    printf("Execution Order: ");

    // Loop to execute processes
    while (completed != n) {

        // Find next process
        int index = findNextProcess(proc, current_time);

        if (index != -1) {
            // If process has changed, print it for execution order
            if (prev != index) {
                printf("P%d ", proc[index].process_id);
                prev = index;
            }

            // Process found, execute for 1 time unit
            proc[index].remaining_time--;
            current_time++;

            // If process is completed, save its info
            if (proc[index].remaining_time == 0) {
                completed++;
                proc[index].completion_time = current_time; // Store when it finished
                proc[index].turnaround_time = proc[index].completion_time - proc[index].arrival_time;
                proc[index].waiting_time = proc[index].turnaround_time - proc[index].burst_time;
            }
        } else {
            // Increment time
            current_time++;
        }
    }

    printf("\n");
}

// Function to print the processes and their details
void printProcesses(Process proc[]) {
    printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].waiting_time, proc[i].turnaround_time);
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
    }
    printf("\nAverage Waiting Time = %.2f ms\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time = %.2f ms\n", (float)total_turnaround_time / n);
}

int main() {
    // Initialize processes with their IDs, arrival times, and burst times
    Process proc[] = {{1, 0, 8}, {2, 1, 4}, {3, 2, 9}, {4, 3, 5}};
    n = sizeof(proc) / sizeof(proc[0]);

    srtf(proc);
    printProcesses(proc);

    return 0;
}