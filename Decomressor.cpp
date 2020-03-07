//
// Created by frak on 05.03.2020.
//

#include <fstream>
#include <iostream>
#include "Decomressor.h"

Decomressor::Decomressor() : Compres_abstract() {}

void Decomressor::decomress(const std::string& input_file, const char *output_file) {
    input_file_reader.open(input_file, std::ios::in | std::ios::binary);
    WINDOW_SIZE = next_int();
    std::freopen(output_file, "w+", stdout);
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
    std::cout << added;
    if (window.size() == WINDOW_SIZE)
    {
        window.pop_front();
        return false;
    }
    return true;
}
