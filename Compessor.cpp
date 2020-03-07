//
// Created by frak on 06.03.2020.
//

#include <deque>
#include <algorithm>
#include <iostream>
#include "Compessor.h"
#include "suffix_array.h"

Compessor::Compessor(int level) : Compres_abstract() {
    WINDOW_SIZE = 1024 + level * 512;
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


void Compessor::compress(const std::string& file, const char *compressed_file) {
    input_file_reader.open(file, std::ios::in | std::ios::binary);
    ////debug
    ofs.open(compressed_file);
    write_int(WINDOW_SIZE);
    unsigned int i = 0;
    while (true)
    {
        char current_c = next_char();
        while (deq.size() < WINDOW_SIZE * 2 && current_c != -1)
        {
            deq.push_back(current_c);
            current_c = next_char();
        }
        std::string tmp_str;
        for (char c : deq)
        {
            tmp_str.push_back(c);
        }
        suffix_array array(tmp_str);
        int j = 0;
        while (j < (tmp_str.size() / 16) || (WINDOW_SIZE + 1 > i && i < tmp_str.size()))
        {
            auto max_lcp = array.get_max_lcp(static_cast<int>(i), static_cast<int>(WINDOW_SIZE));
            i += max_lcp.second;
            if (i == tmp_str.size()) {
                max_lcp.second--;
                i--;
                if (max_lcp.second < 0) {
                    throw std::runtime_error("-1 write in file");
                }
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

    std::string tmp_str;
    for (char c : deq) {
        tmp_str.push_back(c);
    }
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
    input_file_reader.close();
    ofs.close();
}



void Compessor::write_int(unsigned int tmp_int) {
    for (char i : split_to_chars(tmp_int)) {
        ofs<< i;
    }
}


