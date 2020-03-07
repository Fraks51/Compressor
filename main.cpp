#include <iostream>
#include <fstream>
#include <deque>
#include <vector>

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

    void setBuffer(char * buffer, int buffer_size)
    {
        int pointer = 0;
        while (true)
        {
            while (next_buffer.size() != BUFFER_MAX_SIZE && buffer_size != pointer)
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

int main() {
    ifstream file_reader;
    file_reader.open("Loren_ipsem.txt");
    cout << "Lvl: ";
    short level;
    cin >> level;
    const unsigned short BUFFER_SIZE = UINT16_MAX; //todo
    char *reader_buffer = nullptr;
    Compressor compressor(BUFFER_SIZE);
    int read_len;
    while ((read_len = file_reader.readsome(reader_buffer, BUFFER_SIZE)) != 0)
    {

    }

    return 0;
}
