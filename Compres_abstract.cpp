//
// Created by frak on 06.03.2020.
//

#include <cstring>
#include <iostream>
#include "Compres_abstract.h"

char Compres_abstract::next_char() {
    if (pointer >= BUFFER_SIZE)
    {
        BUFFER_SIZE = input_file_reader.readsome(buffer, BUFFER_SIZE);
        if (BUFFER_SIZE != 0)
        {
            pointer = 0;
        }
        else {
            return -1;
        }
    }
    pointer++;
    return buffer[pointer - 1];
    if (pointer >= 4334) {
        return -1;
    }
    pointer++;
    return 0;
}

Compres_abstract::Compres_abstract() {
    pointer = BUFFER_SIZE;
    buffer = new char(BUFFER_SIZE);
}

Compres_abstract::~Compres_abstract() {
    delete [] buffer;
}

Compres_abstract &Compres_abstract::operator=(const Compres_abstract & tmp) {
    if(this!=&tmp) {
        BUFFER_SIZE = tmp.BUFFER_SIZE;
        char *ss = new char[BUFFER_SIZE];
        delete[] buffer;
        std::strcpy(ss, tmp.buffer);
        buffer = ss;
    }
    return *this;
}




