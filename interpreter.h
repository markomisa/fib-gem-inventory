#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <string>
#include <sstream>
#include <iostream>

// Forward declarations
class MinFibHeap;
class MaxFibHeap;

class CommandInterpreter {
public:
    CommandInterpreter() : minHeap(nullptr), maxHeap(nullptr) {}
    ~CommandInterpreter();

    void executeCommand(const std::string& command);

protected:
    void V(); // Generisanje (Initialization)
    void B(); // Brisanje (Deletion/Cleanup)
    void D(int x); // Ubacivanje u max heap
    void M(int x); // Ubacivanje u min heap
    void T(); // Extract Max (Max Heap)
    void P(); // Extract Min (Min Heap)
    void G(); // Print Heaps
    void L(); // Prebacivanje (Union into the smaller heap type)
    void R(int k); // K smallest elements (Min Heap)

private:
    MinFibHeap* minHeap;
    MaxFibHeap* maxHeap;
};

#endif // INTERPRETER_H