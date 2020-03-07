//
// Created by frak on 06.03.2020.
//

#ifndef COMPRESSOR_COMPRES_ABSTRACT_H
#define COMPRESSOR_COMPRES_ABSTRACT_H


#include <fstream>

class Compres_abstract {
protected:
    std::ifstream input_file_reader;
    short pointer;
    char buffer[1024];
    int BUFFER_SIZE = 1024;

    char next_char();

public:
    Compres_abstract();
};


#endif //COMPRESSOR_COMPRES_ABSTRACT_H
