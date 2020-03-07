//
// Created by frak on 06.03.2020.
//

#ifndef COMPRESSOR_SUFFICS_ARRAY_H
#define COMPRESSOR_SUFFICS_ARRAY_H

#pragma once

#include <string>
#include <vector>
#include <algorithm>

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

    suffix_array() = default;

    suffix_array(std::string & data) {
        int n = data.size() + 1;
        std::vector <lr> c(n);
        std::vector <std::pair <char, int> > words(n);

        for (int i = 0; i < n - 1; i++)
            words[i] = { data[i], i };
        words[n - 1] = { 0, n - 1 };
        std::sort(words.begin(), words.end());

        c[0] = { n - 1, 0, 0 };
        for (int i = 1, k = 0; i < n; i++) {
            if (words[i].first != words[i - 1].first)
                k++;
            c[i].l = c[i].r = k;
            c[i].n = words[i].second;
        }

        int degree = 1;
        while (true) {
            std::vector <int> c_bet(n), place(n);

            int k = 0;
            c_bet[0] = 0;
            place[c[0].n] = 0;
            for (int i = 1; i < n; i++) {
                if (c[i] != c[i - 1])
                    k++;
                c_bet[i] = k;
                place[c[i].n] = i;
            }

            if (k == n - 1) //suffix array is sorted
                break;

            for (int i = 0; i < n; i++) {
                int r = place[c[i].n];
                c[i].n = c[i].n - degree >= 0 ? c[i].n - degree : c[i].n - degree + n;
                int l = place[c[i].n];
                c[i].l = c_bet[l];
                c[i].r = c_bet[r];
            }
            std::stable_sort(c.begin(), c.end());
            degree *= 2;
        }

        suf_arr.resize(n - 1);
        num_arr.resize(n - 1);
        for (int i = 1; i < n; i++) {//first suffix is empty
            suf_arr[i - 1] = c[i].n;
            num_arr[c[i].n] = i - 1;
        }

        //build lcp

        std::string s = data + (char)0;
        lcp.resize(n - 2);

        for (int i = 1, k = 0; i < n; i++) {
            int j = num_arr[i - 1];
            if (j == 0) {
                k = 0;
                continue;
            }
            int prev = suf_arr[j - 1] + k, now = suf_arr[j] + k;
            while (s[prev] == s[now]) {
                k++, prev++, now++;
                if (prev >= n)
                    prev -= n;
                if (now >= n)
                    now -= n;
            }
            lcp[j - 1] = k;
            k = std::max(k - 1, 0);
        }

    }

    std::vector<int> get_suffix_array() {
        return suf_arr;
    }

    std::vector<int> get_lcp_array() {
        return lcp;
    }

    std::pair<int, int> get_max_lcp(int v, int r) {//first - number, second - lcp, r - radius
        std::pair<int, int> max_lcp = { -1, -1 };
        for (int i = num_arr[v] - 1, lcp_now = INT_MAX; i >= 0; i--) {
            lcp_now = std::min(lcp_now, lcp[i]);
            if (suf_arr[i] < v - r) {
                max_lcp = { v - r, lcp_now };
                break;
            }
        }

        for (int i = num_arr[v] + 1, lcp_now = INT_MAX; i <= suf_arr.size(); i++) {
            lcp_now = std::min(lcp_now, lcp[i]);
            if (suf_arr[i] < v - r) {
                if (lcp_now > max_lcp.second)
                    max_lcp = { v - r, lcp_now };
                break;
            }
        }
        return max_lcp;
    }

};


#endif //COMPRESSOR_SUFFICS_ARRAY_H
