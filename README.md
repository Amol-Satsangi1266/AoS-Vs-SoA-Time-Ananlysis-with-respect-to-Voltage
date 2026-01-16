# AoS vs SoA Time Analysis (C++)

This project explores how **memory layout** impacts performance in C++ by comparing:

- **Array of Structures (AoS)**
- **Structure of Arrays (SoA)**

The same computation (average voltage calculation) is performed on both layouts to observe differences caused purely by **cache locality and memory access patterns**.

## Motivation
In performance-critical software such as **EDA tools, simulators, and instrumentation software**, runtime is often limited by **memory bandwidth**, not algorithmic complexity.  
This experiment demonstrates why **data-oriented design** is commonly preferred in such systems.

## What the program does
- Generates millions of voltage samples
- Stores data in AoS and SoA formats
- Computes average voltage
- Measures execution time using `std::chrono`

## Key Learning
- Memory layout can significantly affect performance
- SoA becomes advantageous when working on a single attribute across large datasets
- Cache behavior plays a critical role in real-world engineering software

## Build & Run
```bash
g++ -O2 memory_layout.cpp -o memory_layout
./memory_layout
<img width="718" height="431" alt="Screenshot 2026-01-16 233204" src="https://github.com/user-attachments/assets/ff92b5cc-5445-4d89-9bce-f4e7d1dd6715" />

