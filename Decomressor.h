//
// Created by frak on 05.03.2020.
//

#ifndef COMPRESSOR_DECOMRESSOR_H
#define COMPRESSOR_DECOMRESSOR_H


#include <deque>
#include <string>

class Decomressor {
private:
    std::deque<char> window;
    unsigned int WINDOW_SIZE;
    std::ofstream ofs;
    std::ifstream input_file_reader;
    unsigned int pointer;
    char *buffer;
    unsigned int BUFFER_SIZE = 20; //todo

    bool add_in_window(char added);

    unsigned int next_int();

    char next_char();

public:
    ~Decomressor();

    explicit Decomressor();

    void decomress(const std::string& input_file, std::string output_file);

};


#endif //COMPRESSOR_DECOMRESSOR_H
