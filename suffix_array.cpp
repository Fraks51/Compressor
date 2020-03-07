//
// Created by frak on 07.03.2020.
//

#include "suffix_array.h"

#include <string>
#include <vector>
#include <algorithm>

suffix_array::suffix_array() = default;

suffix_array::suffix_array(std::string & data) {
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

        if (degree > n) //suffix array is sorted
            break;

        for (int i = 0; i < n; i++) {
            int r = place[c[i].n];
            while (c[i].n - degree < 0) {
                c[i].n += n;
            }
            c[i].n -= degree;
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

std::vector<int> suffix_array::get_suffix_array() {
    return suf_arr;
}

std::vector<int> suffix_array::get_lcp_array() {
    return lcp;
}

std::pair<int, int> suffix_array::get_max_lcp(int v, int r) {//first - offset , second - distance
    std::pair<int, int> max_lcp = { 0, 0 };
    for (int i = num_arr[v] - 1, lcp_now = INT_MAX; i >= 0; i--) {
        lcp_now = std::min(lcp_now, lcp[i]);
        if (suf_arr[i] < v && r > abs(suf_arr[i] - v) && lcp_now != 0) {
            max_lcp = { v - suf_arr[i], lcp_now };
            break;
        }
    }

    for (int i = num_arr[v] + 1, lcp_now = INT_MAX; i <= suf_arr.size(); i++) {
        lcp_now = std::min(lcp_now, lcp[i - 1]);
        if (suf_arr[i] < v && r > abs(suf_arr[i] - v) && lcp_now != 0) {
            if (lcp_now >= max_lcp.second)
                max_lcp = { v - suf_arr[i], lcp_now };
            break;
        }
    }
    return max_lcp;
}

