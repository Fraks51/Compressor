#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
#include <algorithm>
#include "Decomressor.h";

using namespace std;

struct Node {
    int offset;
    int length;
    int next;
};

class Compressor {
private:
    deque<char> prev_buffer;
    deque<char> next_buffer;
    unsigned short BUFFER_MAX_SIZE;
    char buffer[1024];
public:
    Compressor(unsigned short BUFFER_SIZE) : BUFFER_MAX_SIZE(BUFFER_SIZE) {}

    void countNode()
    {
        vector<int> z(prev_buffer.size() + next_buffer.size() + 1);
        for (int i = 0, l = 0, r = 0; i < prev_buffer.size(); i++)
        {
            if (i <= r)
                z[i] = min (r-i+1, z[i-l]);
            while (i+z[i] < prev_buffer.size() && prev_buffer[z[i]] == prev_buffer[i+z[i]])
                ++z[i];
            if (i+z[i]-1 > r)
                l = i,  r = i+z[i]-1;
        }

    }

    void setBuffer(char * buffer, int BUFFER_SIZE)
    {
        int pointer = 0;
        while (true)
        {
            while (next_buffer.size() != BUFFER_MAX_SIZE && BUFFER_SIZE != pointer)
            {
                next_buffer.push_back(buffer[pointer]);
                pointer++;
            }
            if (next_buffer.size() != BUFFER_MAX_SIZE)
            {
                return;
            }
            countNode();
        }
    }
};

vector<char> split_to_chars(unsigned int tmp_int) {
    vector<char> tmp_vec;
    for (int i = 0; i < 4; i++) {
        tmp_vec.push_back(static_cast<char>((tmp_int & 0xFF) - 128));
        tmp_int >>= 8;
    }
    reverse(tmp_vec.begin(), tmp_vec.end());
    return tmp_vec;
}

int main() {
    ofstream ofs;
    ofs.open("test.in");
    for (char i : split_to_chars(10)) {
        ofs<< i;
    }
    for (char i : split_to_chars(0)) {
        ofs<< i;
    }
    for (char i : split_to_chars(0)) {
        ofs<< i;
    }
    ofs<< "a";
    for (char i : split_to_chars(0)) {
        ofs<< i;
    }
    for (char i : split_to_chars(0)) {
        ofs<< i;
    }
    ofs<< "b";

    for (char i : split_to_chars(0)) {
        ofs<< i;
    }
    for (char i : split_to_chars(0)) {
        ofs<< i;
    }
    ofs<< "c";

    for (char i : split_to_chars(2)) {
        ofs<< i;
    }
    for (char i : split_to_chars(1)) {
        ofs<< i;
    }
    ofs<< "f";

    for (char i : split_to_chars(5)) {
        ofs<< i;
    }
    for (char i : split_to_chars(3)) {
        ofs<< i;
    }
    ofs<< "f";
    ofs.close();
    Decomressor decomressor(1024);
    decomressor.decomress("test.in", "test.out");
    return 0;
}
