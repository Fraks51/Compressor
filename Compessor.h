//
// Created by frak on 06.03.2020.
//

#ifndef COMPRESSOR_COMPESSOR_H
#define COMPRESSOR_COMPESSOR_H


#include <string>
#include "Compres_abstract.h"

class Compessor {
private:
    unsigned int WINDOW_SIZE;
    std::ofstream ofs;
    std::deque<char> deq;

    void write_int(unsigned int tmp_int);
    std::ifstream input_file_reader;
    unsigned int pointer;
    char *buffer;
    unsigned int BUFFER_SIZE = 10;

    char next_char();

public:
    ~Compessor();

    Compessor(int level);

    void compress(const std::string& file, const char *compressed_file);
};


#endif //COMPRESSOR_COMPESSOR_H
