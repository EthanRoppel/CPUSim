//Ethan Roppel, 41753979

#include <stdio.h>
#include <stdlib.h>

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

// Function to calculate waiting times and execution order for all processes
void calculateWaitingTimeAndExecutionOrder(Process proc[], int n, int quantum) {
    // Array to store remaining burst times
    int remaining[n]; 
    
    //Initialize wait time and burst time
    for (int i = 0; i < n; i++) {
        remaining[i] = proc[i].burst_time; 
        proc[i].waiting_time = 0; 
    }

    int current_time = 0; // Initialize Current time
    int completed = 0; // Initialize number of completed processes

    printf("Execution Order: ");
    
    //repeat until all processes are completed 
    while (completed < n) {

        // Initialize done (empty input case)
        int done = 1;

        // For each process
        for (int i = 0; i < n; i++) {

            // Checks if there are still other processes to execute
            if (remaining[i] > 0) {
                
                //There still is processes
                done = 0;
                
                // Print the execution order as they occur
                printf("P%d ", proc[i].process_id);
                
                // Attempt to "run" the process in the quantum if it has a full remaining
                if (remaining[i] > quantum) {

                    // Execute for time quantum
                    current_time += quantum;
                    remaining[i] -= quantum;
                } else {

                    // Finish execution not requiring full quantum
                    current_time += remaining[i];
                    remaining[i] = 0;
                    completed++;

                    // Store process completion time
                    proc[i].completion_time = current_time;
                    
                    // Calculate its turnaround and waiting times
                    proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
                    proc[i].waiting_time = proc[i].turnaround_time - proc[i].burst_time;
                }
            }
        }

        if (done == 1) break; // If all processes are done, exit loop
    }

    printf("\n");
}

// Function to calculate turnaround times for all processes
void calculateTurnaroundTime(Process proc[], int n) {
    for (int i = 0; i < n; i++) {
        // Turnaround = completion - arrival
        proc[i].turnaround_time = proc[i].completion_time - proc[i].arrival_time;
    }
}

// RR Scheduler
void roundRobin(Process proc[], int n, int quantum) {
    calculateWaitingTimeAndExecutionOrder(proc, n, quantum);
    calculateTurnaroundTime(proc, n);
}

// Function to print processes and their details
void printProcesses(Process proc[], int n) {
    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n");
    int total_waiting_time = 0, total_turnaround_time = 0;
    
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",
               proc[i].process_id, proc[i].arrival_time, proc[i].burst_time,
               proc[i].completion_time, proc[i].waiting_time, proc[i].turnaround_time);
        
        total_waiting_time += proc[i].waiting_time;
        total_turnaround_time += proc[i].turnaround_time;
    }

    printf("\nAverage Waiting Time: %.2f ms\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f ms\n", (float)total_turnaround_time / n);
}

int main() {
    Process proc[] = {{1, 0, 24}, {2, 0, 3}, {3, 0, 3}};
    int n = sizeof(proc) / sizeof(proc[0]); // Number of processes
    int quantum = 4; // Time quantum for Round Robin scheduling

    roundRobin(proc, n, quantum);
    printProcesses(proc, n);

    return 0;
}