# **Priority Scheduler Implementation**

## **Project Overview**
This project implements a priority-based scheduler for an operating system, including two new system calls: `setpriority(int)` and `getpinfo(struct pstat*)`. Additionally, a user-level `ps` command is provided to display process information.

## **Implemented Features**
- **System Calls:**
  - `int setpriority(int x)`: Sets the priority of the current process.
  - `int getpinfo(struct pstat* statuses)`: Retrieves information about active processes.
- **User-Level Command:**
  - `ps.c`: Demonstrates the functionality of the new system calls.
- **Priority Scheduler:**
  - Schedules processes based on their priority (1-20, default 10).
  - Ensures race condition safety.

---

## **Repository Structure & Modifications**
The repository structure remains largely unchanged, with necessary modifications to integrate the new system calls. The changes include:

### **Kernel-Level Changes**
- **`defs.h`**: Added system calls definitions in the `proc.c` section.
- **`user.h`**: Declared system calls.
- **`sysproc.c`**:
  - Implemented `sys_setpriority(int)` and `sys_getpinfo()`.
- **`syscall.h`**:
  - Defined the two new system calls.
- **`proc.c`**:
  - Implemented `setpriority(int x)` logic.
  - Updated `procinit()` to ensure the default priority of each process is `10`.
- **`usys.pl`**:
  - Added user-level syscall wrappers.

### **User-Level Changes**
- **`ps.c`**:
  - Calls `setpriority(14)` to adjust process priority.
  - Uses `getpinfo` to retrieve and print information about active processes.

---

## **System Call Details**
### **`int setpriority(int x)`**
- Implemented in `proc.c`.
- Accepts an integer `x` (validated via `argaddr` in `sys_setpriority`).
- If `x` is within the range `[1, 20]`, the process priority is updated; otherwise, returns `-1`.

### **`int getpinfo(struct pstat* statuses)`**
- `pstat` structure defined in `proc.h` to store process details.
- Iterates over processes:
  - If active, copies relevant attributes to a local `struct pstat`.
  - Uses `copyout()` to transfer the data to user space.

---

## **Priority Scheduler**
- Identifies the process with the highest priority.
- Stores the selected process in a `struct proc*` variable.
- Implements race condition prevention with:
  - `&high_priority_process->lock`
  - Condition to check if `state == RUNNABLE`
- Executes the process similarly to the default scheduler.

---

## **Usage**
1. **Set Priority:**
   ```c
   setpriority(14); // Sets priority to 14
   ```
2. **Retrieve Process Information:**
   ```c
   struct pstat statuses;
   getpinfo(&statuses);
   ```
3. **Run `ps.c` to View Process Details:**
   ```sh
   make ps
   ./ps
   ```

---


