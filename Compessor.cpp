//
// Created by frak on 06.03.2020.
//

#include <deque>
#include "Compessor.h"
#include "Suffics_array.h"

Compessor::Compessor(int level) : Compres_abstract() {
    WINDOW_SIZE = 1024 + level * 512;
}

static std::vector<char> split_to_chars(unsigned int tmp_int) {
    std::vector<char> tmp_vec;
    for (int i = 0; i < 4; i++) {
        tmp_vec.push_back(static_cast<char>((tmp_int & 0xFF) - 128));
        tmp_int >>= 8;
    }
    reverse(tmp_vec.begin(), tmp_vec.end());
    return tmp_vec;
}

void Compessor::compress(const std::string& file, const char *compressed_file) {
    input_file_reader.open(file, std::ios::in | std::ios::binary);
    ofs.open(compressed_file);
    std::deque<char> deq;
    write_int(WINDOW_SIZE);
    int i = 0;
    while (true)
    {
        char current_c = next_char();
        while (deq.size() < WINDOW_SIZE * 2 && current_c != -1)
        {
            deq.push_back(current_c);
        }
        std::string tmp_str;
        for (char c : deq)
        {
            tmp_str.push_back(c);
        }
        for
    }
}

void Compessor::write_int(unsigned int tmp_int) {
    for (char i : split_to_chars(tmp_int)) {
        ofs<< i;
    }
}

