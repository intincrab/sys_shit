#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_PROCESSES 10
#define MAX_FILES 10
#define MAX_FILENAME 20

typedef struct {
    int pid;
    int burst_time;
    int arrival_time;
    int remaining_time;
    int completed;
} Process;

typedef struct {
    char name[MAX_FILENAME];
    int size;
} File;

Process processes[MAX_PROCESSES];
File files[MAX_FILES];
int process_count = 0;
int file_count = 0;

void init_system() {
    // Initialize some files
    strcpy(files[0].name, "file1.txt");
    files[0].size = 100;
    strcpy(files[1].name, "file2.txt");
    files[1].size = 200;
    file_count = 2;
}

int fork_process(int burst_time) {
    if (process_count >= MAX_PROCESSES) {
        printf("Error: Maximum number of processes reached.\n");
        return -1;
    }
    
    Process new_process = {
        .pid = process_count + 1,
        .burst_time = burst_time,
        .arrival_time = process_count,  // Simple arrival time assignment
        .remaining_time = burst_time,
        .completed = 0
    };
    
    processes[process_count++] = new_process;
    printf("Process created with PID: %d\n", new_process.pid);
    return new_process.pid;
}

void list_files() {
    printf("Files in the system:\n");
    for (int i = 0; i < file_count; i++) {
        printf("%s (Size: %d bytes)\n", files[i].name, files[i].size);
    }
}

void execute_command(const char* command) {
    printf("Executing command: %s\n", command);
    // Simulating command execution
    sleep(1);
    printf("Command executed.\n");
}

void fcfs_scheduling() {
    printf("FCFS Scheduling:\n");
    for (int i = 0; i < process_count; i++) {
        printf("Executing Process %d for %d units\n", processes[i].pid, processes[i].burst_time);
        sleep(processes[i].burst_time);
        processes[i].completed = 1;
    }
}

void sjf_scheduling() {
    printf("SJF Scheduling:\n");
    int completed = 0;
    while (completed < process_count) {
        int shortest_job = -1;
        int shortest_time = 9999;
        
        for (int i = 0; i < process_count; i++) {
            if (!processes[i].completed && processes[i].burst_time < shortest_time) {
                shortest_job = i;
                shortest_time = processes[i].burst_time;
            }
        }
        
        if (shortest_job != -1) {
            printf("Executing Process %d for %d units\n", processes[shortest_job].pid, processes[shortest_job].burst_time);
            sleep(processes[shortest_job].burst_time);
            processes[shortest_job].completed = 1;
            completed++;
        }
    }
}

int main() {
    init_system();
    
    while (1) {
        char command[50];
        printf("\nEnter command (fork, list, exec, fcfs, sjf, exit): ");
        scanf("%s", command);
        
        if (strcmp(command, "fork") == 0) {
            int burst_time;
            printf("Enter burst time for new process: ");
            scanf("%d", &burst_time);
            fork_process(burst_time);
        } else if (strcmp(command, "list") == 0) {
            list_files();
        } else if (strcmp(command, "exec") == 0) {
            char cmd[50];
            printf("Enter command to execute: ");
            scanf("%s", cmd);
            execute_command(cmd);
        } else if (strcmp(command, "fcfs") == 0) {
            fcfs_scheduling();
        } else if (strcmp(command, "sjf") == 0) {
            sjf_scheduling();
        } else if (strcmp(command, "exit") == 0) {
            printf("Exiting the system.\n");
            break;
        } else {
            printf("Unknown command.\n");
        }
    }
    
    return 0;
}