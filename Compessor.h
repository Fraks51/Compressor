//
// Created by frak on 06.03.2020.
//

#ifndef COMPRESSOR_COMPESSOR_H
#define COMPRESSOR_COMPESSOR_H


#include <string>
#include "Compres_abstract.h"

class Compessor : public Compres_abstract {
private:
    unsigned int WINDOW_SIZE;
    std::ofstream ofs;

    void write_int(unsigned int tmp_int);

public:
    Compessor(int level);

    void compress(const std::string& file, const char *compressed_file);
};


#endif //COMPRESSOR_COMPESSOR_H
