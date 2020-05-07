//
// Created by frak on 05.03.2020.
//

#include <fstream>
#include <iostream>
#include "Decomressor.h"

Decomressor::Decomressor() {
    pointer = BUFFER_SIZE;
    buffer = new char(BUFFER_SIZE);
}

void Decomressor::decomress(const std::string& input_file, std::string output_file) {
    input_file_reader.open(input_file, std::ios::in | std::ios::binary);
    WINDOW_SIZE = next_int();
    ofs.open(output_file);
    while (next_char() != -1) {
        pointer--;
        size_t offset = window.size() - next_int(), distance = next_int();
        for (size_t j = 0; j < distance; j++) {
            char current = window[offset];
            if (add_in_window(current)) {
                offset++;
            }
        }
        add_in_window(next_char());
    }
    input_file_reader.close();
    ofs.close();
}


unsigned int Decomressor::next_int() {
    unsigned int tmp_int = 0;
    for (int i = 0; i < 4; i++)
    {
        tmp_int += static_cast<int>(next_char()) + 128;
        if (i != 3) {
            tmp_int <<= 8;
        }
    }
    return tmp_int;
}

bool Decomressor::add_in_window(char added) {
    window.push_back(added);
    ofs << added;
    if (window.size() == WINDOW_SIZE)
    {
        window.pop_front();
        return false;
    }
    return true;
}

Decomressor::~Decomressor() {
    delete [] buffer;
}

char Decomressor::next_char() {
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
}
