#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <pthread.h>

#define READY 1
#define RUNNING 2
#define TERMINATED 3

typedef struct Process {
    int id;                 // Process ID
    int state;              // Process state
    int priority;           // Process priority (lower value = higher priority)
    char name[256];         // Program name
    int memory_allocated;   // Simulated memory allocation
    pthread_t thread_id;    // Thread ID for execution
} Process;

Process *processes[10];
int process_count = 0;
int total_memory = 1200; // Simulated memory pool (in MB)
int used_memory = 0;

// Function to calculate program file size
int get_file_size(const char *file_name) {
    struct stat st;
    if (stat(file_name, &st) == 0) {
        return (int)st.st_size;
    }
    return -1; // File not found or error
}

// Memory Manager: Allocate memory for a process
int allocate_memory(int size) {
    if (used_memory + size > total_memory) {
        printf("Error: Not enough memory to allocate %d MB.\n", size);
        return -1;
    }
    used_memory += size;
    return size;
}

// Memory Manager: Deallocate memory for a process
void deallocate_memory(int size) {
    used_memory -= size;
    if (used_memory < 0) used_memory = 0;
}

// File System: Read a file
void read_file(const char *file_name) {
    FILE *file = fopen(file_name, "r");
    if (file) {
        char buffer[256];
        printf("Reading file: %s\n", file_name);
        while (fgets(buffer, sizeof(buffer), file)) {
            printf("%s", buffer);
        }
        fclose(file);
    } else {
        printf("Error: Unable to read file %s.\n", file_name);
    }
}

// Thread function to execute the program
void *execute_program(void *arg) {
    Process *current = (Process *)arg;
    printf("Starting process %s with priority (file size): %d, memory allocated: %d MB...\n", 
           current->name, current->priority, current->memory_allocated);

    int status = system(current->name);  // Use system() to execute the program
    if (status == -1) {
        perror("Error executing program");
    }

    printf("Process %s terminated.\n", current->name);
    // Deallocate memory for the process
    deallocate_memory(current->memory_allocated);
    current->state = TERMINATED;

    return NULL;
}

// Function to create a new process with dynamic priority
void create_process(const char *program_name) {
    if (process_count >= 10) {
        printf("Maximum process limit reached!\n");
        return;
    }

    int file_size = get_file_size(program_name);
    if (file_size == -1) {
        printf("Error: Program file %s not found.\n", program_name);
        return;
    }

    Process *new_process = (Process *)malloc(sizeof(Process));
    new_process->id = process_count + 1;
    new_process->state = READY;
    new_process->priority = file_size; // Smaller file size = higher priority
    strcpy(new_process->name, program_name);
    new_process->memory_allocated = allocate_memory(file_size / 1024); // Simulate memory allocation

    if (new_process->memory_allocated == -1) {
        free(new_process);
        return;
    }

    processes[process_count++] = new_process;
    printf("Process %s created with ID %d, priority based on file size: %d bytes, memory allocated: %d MB\n", 
           program_name, new_process->id, new_process->priority, new_process->memory_allocated);
}

// Scheduler to execute processes using threads
void scheduler() {
    while (1) {
        Process *highest_priority_process = NULL;

        // Find the highest-priority READY process
        for (int i = 0; i < process_count; i++) {
            if (processes[i]->state == READY) {
                if (highest_priority_process == NULL || 
                    processes[i]->priority < highest_priority_process->priority) {
                    highest_priority_process = processes[i];
                }
            }
        }

        // If no READY process is found, exit the scheduler
        if (highest_priority_process == NULL) {
            break;
        }

        Process *current = highest_priority_process;

        printf("Starting thread for process %s with priority (file size): %d, memory allocated: %d MB...\n", 
               current->name, current->priority, current->memory_allocated);

        // Create a thread to execute the program
        pthread_create(&current->thread_id, NULL, execute_program, (void *)current);
        current->state = RUNNING;

        // Wait for the thread to finish
        pthread_join(current->thread_id, NULL);
    }
}

// Main function (Kernel)
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <program1> <program2> ...\n", argv[0]);
        return 1;
    }

    // Create processes for each input program
    for (int i = 1; i < argc; i++) {
        create_process(argv[i]);
    }

    // Run the scheduler
    scheduler();

    // Free allocated memory for process structures
    for (int i = 0; i < process_count; i++) {
        free(processes[i]);
    }

    return 0;
}
