//
// Created by frak on 06.03.2020.
//

#include "Compres_abstract.h"

char Compres_abstract::next_char() {
    if (pointer >= BUFFER_SIZE)
    {
        if (input_file_reader.get(buffer, 1024))
        {
            BUFFER_SIZE = input_file_reader.gcount();
            pointer = 0;
        }
        else {
            return -1;
        }
    }
    pointer++;
    return buffer[pointer - 1];
}

Compres_abstract::Compres_abstract() {
    pointer = 0;
}
