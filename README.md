# MINIPROC OS – A Mini Process Scheduling Operating System

MINIPROC OS is a simulation of a basic operating system designed to demonstrate process scheduling using a **priority-based algorithm**, where the priority is determined by **file size**. The larger the file, the higher the priority, and the earlier it gets executed.

---

## 🎯 Objective

To simulate a simplified operating system scheduler that selects processes based on file size priority, offering a hands-on understanding of how scheduling strategies can impact execution order and system efficiency.

---

## 🔍 Key Features

- ✅ Priority-based process scheduling
- ✅ Dynamic process creation and queue management
- ✅ File size-based priority assignment
- ✅ Process execution in descending order of file size
- ✅ Console output for process scheduling steps

---

## ⚙️ How It Works

1. The user selects multiple files to act as "processes".
2. Each file is treated as a process and its size is extracted.
3. Processes are prioritized by size (larger → higher priority).
4. The scheduler executes processes in descending order of size.
5. Execution steps are printed for visualization.
