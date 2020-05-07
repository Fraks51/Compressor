#include <iostream>
#include "Compessor.h"
#include "Decomressor.h"

using namespace std;

int main() {
    string input_file, output_file;
    cout << "Input and output files:\n";
    cin >> input_file >> output_file;
    cout << "What do compress or decompress (or default test: input nothing):\n";
    string command;
    cin >> command;
    if (command == "compress") {
        cout << "Level:\n";
        int lvl = 0;
        cin >> lvl;
        if (0 <= lvl && lvl <= 100) {
            cout << "Start compress...\n";
            Compessor compessor(lvl);
            compessor.compress(input_file, output_file);
        } else {
            cout << "Incorrect Level!!!";
            return 0;
        }
    } else if (command == "decompress") {
        cout << "Start decompress...\n";
        Decomressor decomressor;
        decomressor.decomress(input_file, output_file);
    } else { // defalt bible test
        cout << "Start defalt test...\n";
        Compessor compessor(10);
        compessor.compress("files/bible.txt", "files/cf.txt");
        Decomressor decomressor;
        decomressor.decomress("files/cf.txt", "files/final.txt");
    }
    return 0;
}
