//
// Created by frak on 05.03.2020.
//

#ifndef COMPRESSOR_DECOMRESSOR_H
#define COMPRESSOR_DECOMRESSOR_H


#include <deque>
#include <string>
#include "Compres_abstract.h"

class Decomressor : public Compres_abstract {
private:
    std::deque<char> window;
    unsigned int WINDOW_SIZE;
    std::ofstream ofs;

    bool add_in_window(char added);

    unsigned int next_int();
public:
    explicit Decomressor();

    void decomress(const std::string& input_file, const char * output_file);

};


#endif //COMPRESSOR_DECOMRESSOR_H
