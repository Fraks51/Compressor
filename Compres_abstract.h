//
// Created by frak on 06.03.2020.
//

#ifndef COMPRESSOR_COMPRES_ABSTRACT_H
#define COMPRESSOR_COMPRES_ABSTRACT_H


#include <fstream>
#include "suffix_array.h"

class Compres_abstract {
protected:
    std::ifstream input_file_reader;
    unsigned int pointer;
    char *buffer;
    unsigned int BUFFER_SIZE = 1024;

    virtual char next_char();

public:
    Compres_abstract();

    Compres_abstract &operator=(const Compres_abstract & tmp);

    ~Compres_abstract();
};


#endif //COMPRESSOR_COMPRES_ABSTRACT_H
