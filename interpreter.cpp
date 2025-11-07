#include "interpreter.h"
#include "minfibheap.h"
#include "maxfibheap.h"
#include "converter.h"

CommandInterpreter::~CommandInterpreter() {
    B(); // Ensure heaps are cleaned up
}

void CommandInterpreter::executeCommand(const std::string& command) {
    int x = 0;
    char commandType = command.empty() ? '\0' : command.front();
    std::stringstream s(command.substr(1)); // Start reading after the command letter

    if (commandType == 'D' || commandType == 'M' || commandType == 'R') {
        char bracket;
        if (s >> bracket && bracket == '[') {
            s >> x;
        } else {
            // Handle error or simple insertion without brackets if that's expected input
            // For now, assume format D[x] or D x is handled by original logic
            if (command.size() > 1) { // Fallback if bracket reading fails
                 std::stringstream s_fallback(command.substr(1));
                 s_fallback >> x;
            }
        }
    }

    switch (commandType) {
        case 'V':
            V();
            break;
        case 'B':
            B();
            break;
        case 'D':
            D(x);
            break;
        case 'M':
            M(x);
            break;
        case 'T':
            T();
            break;
        case 'P':
            P();
            break;
        case 'G':
            G();
            break;
        case 'L':
            L();
            break;
        case 'R':
            R(x);
            break;
        case 'K':
            B();
            exit(0);
        default:
            std::cout << "Nepoznata komanda: " << command << std::endl;
            break;
    }
}

void CommandInterpreter::V() {
    B(); 
    minHeap = new MinFibHeap();
    maxHeap = new MaxFibHeap();
    std::cout << "Kupovina plave i crvene vrece (Generisani novi min i max hipovi)." << std::endl;
}

void CommandInterpreter::B() {
    if (minHeap) {
        delete minHeap;
        minHeap = nullptr;
    }
    if (maxHeap) {
        delete maxHeap;
        maxHeap = nullptr;
    }
    std::cout << "Poklanjanje (Brisanje) hipova izvrseno." << std::endl;
}

void CommandInterpreter::D(int x) {
    if (maxHeap) {
        maxHeap->insert(x);
        std::cout << "Dijamant vrednosti " << x << " pronadjen (Ubaci u Max Heap)." << std::endl;
    } else {
        std::cout << "Max Heap nije inicijalizovan (Vrednost " << x << " nije ubacena)." << std::endl;
    }
}

void CommandInterpreter::M(int x) {
    if (minHeap) {
        minHeap->insert(x);
        std::cout << "Mojsanit vrednosti " << x << " pronadjen (Ubaci u Min Heap)." << std::endl;
    } else {
        std::cout << "Min Heap nije inicijalizovan (Vrednost " << x << " nije ubacena)." << std::endl;
    }
}

void CommandInterpreter::T() {
    if (maxHeap && maxHeap->getNodeCount() > 0) {
        Node *node = maxHeap->extractMax();
        std::cout << "Nailazak na trgovca: Izdvojen Max element: " << node->key << std::endl;
        delete node;
    } else {
        std::cout << "Max Heap je prazan ili nije inicijalizovan." << std::endl;
    }
}

void CommandInterpreter::P() {
    if (minHeap && minHeap->getNodeCount() > 0) {
        Node *node = minHeap->extractMin();
        std::cout << "Nailazak na pekara: Izdvojen Min element: " << node->key << std::endl;
        delete node;
    } else {
        std::cout << "Min Heap je prazan ili nije inicijalizovan." << std::endl;
    }
}

void CommandInterpreter::G() {
    if (!minHeap || !maxHeap) {
        std::cout << "Jedan ili oba hipa nisu inicijalizovani." << std::endl;
        return;
    }
    std::cout << "\n=== GRANICNI PRELAZ (Print Heaps) ===" << std::endl;
    std::cout << "--- Mojsaniti (Min Fib Heap) ---" << std::endl;
    minHeap->printHeap();
    std::cout << "--- Dijamanti (Max Fib Heap) ---" << std::endl;
    maxHeap->printHeap();
    std::cout << "====================================\n" << std::endl;
}

void CommandInterpreter::L() {
    if (!maxHeap || !minHeap) {
        std::cout << "Operacija nemoguca. Jedan ili oba hipa nisu inicijalizovani." << std::endl;
        return;
    }
    if (maxHeap->getNodeCount() == 0 && minHeap->getNodeCount() == 0) {
        std::cout << "Operacija nemoguca. Oba hipa su prazna." << std::endl;
        return;
    }
    
    // Determine the smaller heap *type* based on node count
    if (maxHeap->getNodeCount() >= minHeap->getNodeCount()) {
        std::cout << "Lopov: Min Heap (" << minHeap->getNodeCount() << " el.) se prebacuje u Max Heap (" << maxHeap->getNodeCount() << " el.)." << std::endl;
        
        MinFibHeap *temp_min = minHeap;
        minHeap = new MinFibHeap(); // Empty object placeholder

        MaxFibHeap *converted_max = minToMaxHeap(temp_min);
        maxHeap = MaxFibHeap::heapUnion(maxHeap, converted_max);
        
        delete temp_min; // Delete the original (now empty) MinFibHeap object
        delete converted_max; // Delete the temporary (now empty) MaxFibHeap object from conversion
    } else {
        std::cout << "Lopov: Max Heap (" << maxHeap->getNodeCount() << " el.) se prebacuje u Min Heap (" << minHeap->getNodeCount() << " el.)." << std::endl;
        
        MaxFibHeap *temp_max = maxHeap;
        maxHeap = new MaxFibHeap(); // Empty object placeholder

        MinFibHeap *converted_min = maxToMinHeap(temp_max);
        minHeap = MinFibHeap::heapUnion(minHeap, converted_min);
        
        delete temp_max; // Delete the original (now empty) MaxFibHeap object
        delete converted_min; // Delete the temporary (now empty) MinFibHeap object from conversion
    }
    std::cout << "Operacija zavrsena." << std::endl;
}

void CommandInterpreter::R(int k) {
    if (minHeap) {
        std::cout << "Nailazak na retkog pekara: Izdvajanje " << k << " najmanjih elemenata." << std::endl;
        minHeap->kSmallestElements(k);
    } else {
        std::cout << "Min Heap nije inicijalizovan." << std::endl;
    }
}