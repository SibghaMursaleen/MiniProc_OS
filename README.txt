
MiniProc OS - Scheduling and Memory Management Simulation
This project, named MiniProc OS, simulates the scheduling and memory management aspects of an operating system. It demonstrates process creation, scheduling, execution, and memory allocation.


Features
1. Simulates process creation based on program files.
2. Priority-based scheduling (lower file size = higher priority).
3. Threaded process execution using `pthread` (POSIX threads).
4. Memory management with allocation and deallocation.
5. Cross-platform compatibility (Windows, Linux).


How It Works
1. Command-line input specifies the programs to run.
2. Processes are created with calculated priority and memory allocation.
3. A scheduler selects and executes the highest-priority process.
4. Processes are executed in threads, ensuring efficient multitasking.
5. Memory is deallocated upon process termination.

---

Compiling and Running

For Windows:
1. Install MinGW and ensure `gcc`, `make`, and `pthread` are available.
2. Use the provided Makefile:
   make
   
3. Run the program with executable file names as arguments:
  
   ./MiniProc_OS.exe program1.exe program2.exe

For Linux:
1. Ensure `gcc`, `make`, and `pthread` are installed.
2. Use the provided Makefile:
   ```
   make
   
3. Run the program with executable file names as arguments:
   
   ./MiniProc_OS program1 program2
   

Example Programs
1. number_printer: Prints numbers from 1 to 100.
2. multiplication_table: Prints a multiplication table.
3. sum_calculator: Calculates the sum of numbers from 1 to N.
4. string_reverser: Reverses and prints a string.
5. factorial_calculator: Computes factorials recursively.
6. prime_checker: Checks if a number is prime.



Memory Management
- Total memory pool: 1000 MB.
- Allocates memory dynamically based on file size.
- Ensures memory is released after process termination.


Threading and Process Execution
- Utilizes POSIX threads (`pthread` library).
- Windows execution uses `CreateProcess` API.
- Linux execution uses `system` call.
- Threads run independently for each process.


Contributing
We welcome contributions! Fork the repository, make changes, and submit a pull request.


License
This project is licensed under the MIT License.
