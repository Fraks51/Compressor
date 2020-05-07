//
// Created by frak on 07.03.2020.
//

#ifndef COMPRESSOR_SUFFIX_ARRAY_H
#define COMPRESSOR_SUFFIX_ARRAY_H

#include <string>
#include <vector>

class suffix_array {
private:
    const int INT_MAX = INT32_MAX;
    std::vector <int> suf_arr;
    std::vector <int> lcp;
    std::vector <int> num_arr; //number in suffix array

    struct lr {//structure for sorting
        int n; //number
        int l; //left
        int r; //right

        bool operator<(const lr& a) const { //for comparator
            return l < a.l;
        }

        bool operator!=(const lr& a) const {
            return l != a.l || r != a.r;
        }

        bool operator==(const lr& a) const {
            return l == a.l && r == a.r;
        }
    };

public:

    suffix_array();

    suffix_array(std::string & data);

    std::vector<int> get_suffix_array();

    std::vector<int> get_lcp_array();

    std::pair<int, int> get_max_lcp(int v, int r);

};


#endif //COMPRESSOR_SUFFIX_ARRAY_H
