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
    std::ifstream input_file_reader;
    unsigned int pointer;
    char *buffer;
    unsigned int BUFFER_SIZE = 20;

    void end_write(unsigned int i);

    char next_char();

    void write_int(unsigned int tmp_int);

public:
    ~Compessor();

    Compessor(int level);

    void compress(const std::string& file, std::string compressed_file);
};


#endif //COMPRESSOR_COMPESSOR_H
