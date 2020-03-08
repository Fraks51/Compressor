#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include "Compessor.h"
#include "Decomressor.h"

using namespace std;

int main() {
    string input_file, output_file;
    cout << "Input and output files:\n";
    cin >> input_file >> output_file;
    cout << "What do compress or decompress:\n";
    string command;
    cin >> command;
    if (command == "compress") {
        cout << "Level:\n";
        int lvl;
        cin >> lvl;
        if (0 <= lvl && lvl <= 100) {
            Compessor compessor(100);
            compessor.compress(input_file, output_file);
        } else {
            cout << "Inccorect Level!!!";
            return 0;
        }
    } else if (command == "decompress") {
        Decomressor decomressor;
        decomressor.decomress(input_file,  output_file);
    }
    return 0;
}
