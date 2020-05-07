//
// Created by frak on 06.03.2020.
//

#include <deque>
#include <algorithm>
#include <iostream>
#include "Compessor.h"
#include "suffix_array.h"

Compessor::Compessor(int level) {
    WINDOW_SIZE = 1024 + level * level * 128;
    pointer = BUFFER_SIZE;
    buffer = new char(BUFFER_SIZE);
}

static std::vector<char> split_to_chars(unsigned int tmp_int) {
    std::vector<char> tmp_vec;
    for (int i = 0; i < 4; i++) {
        tmp_vec.push_back(static_cast<char>((tmp_int & 0xFF) - 128));
        tmp_int >>= 8;
    }
    std::reverse(tmp_vec.begin(), tmp_vec.end());
    return tmp_vec;
}

std::string make_string(std::deque<char> & deq) {
    std::string tmp_str;
    for (char c : deq) {
        tmp_str.push_back(c);
    }
    return tmp_str;
}

void Compessor::end_write(unsigned int i) {
    std::string tmp_str = make_string(deq);
    suffix_array array(tmp_str);
    while (i < tmp_str.size()) {
        auto max_lcp = array.get_max_lcp(static_cast<int>(i), static_cast<int>(WINDOW_SIZE));
        i += max_lcp.second;
        if (i == tmp_str.size()) {
            max_lcp.second--;
            i--;
        }
        write_int(max_lcp.first);
        write_int(max_lcp.second);
        ofs << tmp_str[i];
        if (i == tmp_str.size() - 1)
            break;
        i++;
    }
}

void Compessor::compress(const std::string& file, std::string compressed_file) {
    input_file_reader.open(file, std::ios::in | std::ios::binary);
    ofs.open(compressed_file);
    write_int(WINDOW_SIZE);
    unsigned int i = 0;
    while (true)
    {
        char current_c = next_char();
        while (deq.size() < WINDOW_SIZE * 3 && current_c != -1) {
            deq.push_back(current_c);
            current_c = next_char();
        }
        std::string tmp_str = make_string(deq);
        suffix_array array(tmp_str);
        int j = 0;
        while (j < tmp_str.size() / 3 || (WINDOW_SIZE + 1 > i && i < tmp_str.size()))
        {
            auto max_lcp = array.get_max_lcp(static_cast<int>(i), static_cast<int>(WINDOW_SIZE));
            i += max_lcp.second;
            if (i == tmp_str.size()) {
                max_lcp.second--;
                i--;
            }
            j += max_lcp.second + 1;
            write_int(max_lcp.first);
            write_int(max_lcp.second);
            ofs << tmp_str[i];
            i++;
        }
        if (current_c == -1) {
            break;
        } else {
            deq.pop_front();
            deq.push_back(current_c);
            for (int c = 0; c < (i - WINDOW_SIZE) - 1; c++) {
                deq.pop_front();
            }
        }
        i = std::min(i, WINDOW_SIZE);
    }

    end_write(i);

    input_file_reader.close();
    ofs.close();
}



void Compessor::write_int(unsigned int tmp_int) {
    for (char i : split_to_chars(tmp_int)) {
        ofs<< i;
    }
}

Compessor::~Compessor() {
    delete [] buffer;
}

char Compessor::next_char() {
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
