#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include "Compessor.h"
#include "Decomressor.h"

using namespace std;

int main() {
    Compessor compessor(100);
    compessor.compress("test.out", "compressed_test.txt");
//    Decomressor decomressor;
//    decomressor.decomress("compressed_test.txt",  "decompressed_test.txt");
    return 0;
}
