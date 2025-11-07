#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "interpreter.h" // Only need to include the interpreter

using namespace std;

int main(){
    string choice, filename;
    // Use unique_ptr for safe memory management, or stick to raw pointers and delete at end
    CommandInterpreter *interpreter = new CommandInterpreter(); 

    cout << "        ИНВЕНТАР         " << endl;
    cout << "-------------------------" << endl;
    cout << "Унос преко фајла? (Y) (N)" << endl;
    if (!(cin >> choice)) {
        delete interpreter;
        return 0;
    }

    if (choice == "Y" || choice == "y") {
        cout << "Унесите име фајла: " << endl;
        if (!(cin >> filename)) {
            delete interpreter;
            return 0;
        }
        fstream myFile(filename);
        if (!myFile.is_open()) {
            cerr << "Greska pri otvaranju fajla!" << endl;
            delete interpreter;
            return 1;
        }
        string command;
        while (getline(myFile, command)) {
            // Clean up command string
            if (!command.empty() && command.back() == '\r') {
                command.pop_back();
            }
            if (!command.empty()) {
                interpreter->executeCommand(command);
            }
        }
        myFile.close();
    }
    else {
        while (true) {
            cout << "\n-------------------------" << endl;
            cout << "1. V – Куповина плаве и црвене вреће (Иницијализација)." << endl;
            cout << "2. B – Поклањање плаве и црвене вреће (Брисање/Деиницијализација)." << endl;
            cout << "3. D[x] – Проналажење дијаманта чија је вредност x (Max Heap Insert)." << endl;
            cout << "4. M[x] – Проналажење мојсанита чија је вредност x (Min Heap Insert)." << endl;
            cout << "5. T – Наилазак на путујућег трговца оружја (Extract Max)." << endl;
            cout << "6. P – Наилазак на путујућег пекара (Extract Min)." << endl;
            cout << "7. G – Наилазак на гранични прелаз (Print Heaps)." << endl;
            cout << "8. L – Наилазак на лопова (Union u manji tip)." << endl;
            cout << "9. R[k] – Наилазак на ретког пекара који захтева k драгуља (K Min)." << endl;
            cout << "10 K - Kрај игре" << endl;
            string command;
            cout << "Унесите команду: " << endl;
            if (!(cin >> command)) {
                break; // Exit loop on input failure
            }
            interpreter->executeCommand(command);
        }
    }
    
    delete interpreter;
    return 0;
}