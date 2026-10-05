# Linux User-Space Application Programming

> Embedded System Project — Linux system programming in user space

## Overview

This project studies fundamental **Linux User-Space Application Programming** concepts through theoretical analysis and practical implementation.

The project focuses on process and thread management, inter-process communication (IPC), synchronization, CPU architecture, and performance. The practical demonstrations are implemented in **C/C++ on Ubuntu Linux** so that the theoretical concepts can be observed directly through program execution.

## Main Topics

### 1. Process & Thread Management

The project covers:

- Process and Thread
- User Space and Kernel Space
- Context Switching
- `fork()`
- `exec()`
- `wait()` / `waitpid()`
- POSIX Threads
- `pthread_create()`
- `pthread_join()`

A representative execution flow is:

```text
pthread_create()
      ↓
pthread_join()
      ↓
fork()
      ↓
exec()
      ↓
wait()
```

### 2. Inter-Process Communication (IPC)

IPC is divided into three main groups.

#### Local IPC

- Signal
- Pipe
- FIFO / Named Pipe
- Message Queue
- Unix Domain Socket

#### Shared IPC

- System V Shared Memory
- Memory Mapping (`mmap()`)

#### Network IPC

- TCP Socket
- UDP Socket

The project also introduces higher-level communication technologies such as:

- ZeroMQ
- gRPC
- HTTP/REST
- MQTT

### 3. Synchronization

The project studies the problems and mechanisms involved in concurrent programming:

- Race Condition
- Critical Section
- Mutex
- Semaphore
- Condition Variable
- Deadlock
- Coffman Conditions

Practical demonstrations include:

- Mutex-protected counter
- Producer–Consumer using Condition Variable
- Counting Semaphore
- Reader–Writer synchronization
- Intentional Deadlock demonstration

### 4. CPU Architecture & Performance

Topics include:

- Multi-core CPU
- Physical and Logical Processors
- Context Switching
- CPU Affinity
- L1 / L2 / L3 Cache
- Cache Hit / Cache Miss
- Temporal and Spatial Locality
- Memory Bandwidth
- SIMD
- Vectorization
- NUMA

Two practical experiments are implemented:

1. **CPU Affinity** — assigning threads to selected CPU cores.
2. **Cache Locality** — comparing sequential and pseudo-random memory access.

## Practical Implementation

The demonstrations are developed on Ubuntu Linux using C/C++.

### Compilation

#### C

```bash
gcc <source_file>.c -o <output_file> -O2
./<output_file>
```

#### C++

```bash
g++ <source_file>.cpp -o <output_file> -O2
./<output_file>
```

#### POSIX Threads

```bash
gcc <source_file>.c -o <output_file> -pthread -O2
./<output_file>
```

## Demonstration Programs

| Area | Demonstration |
|---|---|
| Process / Thread | `pthread_create()`, `pthread_join()`, `fork()`, `exec()`, `wait()` |
| Local IPC | Signal, Pipe, FIFO, Message Queue |
| Shared IPC | Shared Memory, `mmap()` |
| Network IPC | TCP Client/Server, UDP Client/Server |
| Synchronization | Mutex, Condition Variable, Semaphore, RW Lock |
| Deadlock | Two-thread circular resource waiting |
| CPU Performance | CPU Affinity, Cache Locality |

## Example Results

### Process & Thread

```text
Main Process
    │
    ├── Create Thread
    │       ↓
    │   Thread executes
    │       ↓
    │   pthread_join()
    │
    ├── fork()
    │     ├── Parent → wait()
    │     └── Child  → exec("ls -l")
    │
    └── Finish
```

### IPC

The Local IPC demonstration exchanges information using:

```text
Signal → Pipe → FIFO → Message Queue
```

Shared IPC demonstrates:

```text
System V Shared Memory
        +
      mmap()
```

Network IPC demonstrates:

```text
TCP: Client ←── connection ──→ Server
UDP: Client ── datagram ──→ Server
```

### Synchronization

```text
Mutex
Condition Variable
Semaphore
Reader-Writer Lock
        +
    Deadlock Demo
```

### CPU Performance

CPU Affinity assigns threads to selected CPU cores and measures execution time.

Cache Locality compares:

```text
Sequential Access    → better locality
Pseudo-Random Access → poorer locality
```

## Learning Objectives

- Understand the execution model of Linux applications.
- Understand User Space and Kernel Space.
- Practice process and thread management.
- Implement IPC mechanisms.
- Identify Race Conditions and Critical Sections.
- Apply synchronization mechanisms.
- Understand how Deadlock occurs.
- Explore CPU architecture and performance factors.
- Observe CPU affinity and cache locality in practice.

## Environment

| Component | Environment |
|---|---|
| Operating System | Ubuntu Linux |
| Programming Languages | C / C++ |
| Compiler | GCC / G++ |
| Thread Library | POSIX Threads |
| Focus | Linux User-Space Programming |

## Report Organization

The report is organized into five chapters:

1. **Introduction** — background, problem statement, objectives, scope, and report organization.
2. **Technical Background** — Process, Thread, IPC, Synchronization, CPU Architecture, and Performance.
3. **Implementation** — practical C/C++ programs and execution.
4. **Results and Discussion** — observed experimental results.
5. **Conclusion** — summary and conclusions.

## Purpose

The project connects **Linux system-level theory with practical programming**.

Instead of studying Process, Thread, IPC, Synchronization, CPU Architecture, and Performance only conceptually, representative programs are implemented and their behavior is observed directly in Ubuntu Linux.

This provides a foundation for further work with **embedded Linux and system-level applications**.
