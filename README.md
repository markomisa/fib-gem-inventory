# 💎 fib-jewel-inventory

**A C++ project implementing a dual-priority inventory system using Min and Max Fibonacci Heaps.**

This simulation manages two types of items—Moissanite (Min Heap) and Diamond (Max Heap)—demonstrating efficient dynamic inventory operations typical of adventure games.

---

## ✨ Key Features

* **Dual Heap Management:** Simultaneous use of **Min Fibonacci Heap** and **Max Fibonacci Heap**.
* **Core Heap Operations:** Efficient $\mathcal{O}(1)$ insertion and $\mathcal{O}(\log n)$ extraction (`T`, `P`).
* **Inventory Logic:** Commands simulate events like trading (`T`, `P`), thievery (`L`), and rare requests (`R[k]`).
* **Modular C++:** Clean structure using modular files and **CMake** for building.

---

## 🛠️ Build & Run

### Prerequisites

* C++ Compiler (supporting C++11 or later)
* CMake (3.10+)

### Steps

1.  **Build:**
    ```bash
    mkdir build
    cd build
    cmake ..
    cmake --build .
    ```
2.  **Run:**
    ```bash
    ./fib_inventory
    ```
    (Follow prompts for interactive or file-based input.)

---

## ▶️ Command Summary

| Command | Action | Heap Operation |
| :---: | :--- | :--- |
| **V** | Initialize inventory sacks. | Initialization |
| **D[x]** | Insert item $x$ (Diamond). | Max Heap `insert` |
| **M[x]** | Insert item $x$ (Moissanite). | Min Heap `insert` |
| **T** | Meet Trader. | `extractMax` |
| **P** | Meet Baker. | `extractMin` |
| **G** | Border Crossing. | Print Heaps |
| **L** | Encounter Thief. | `heapUnion` (Smaller $\to$ Larger) |
| **R[k]** | Rare Request. | $k \times$ `extractMin` |
| **B** | Clean up/Delete inventory. | Deletion |
| **K** | End Program. | Exit |