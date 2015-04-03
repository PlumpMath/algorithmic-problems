//
//  main.cpp
//  max_sum
//
//  Created by Igor Makaruks on 16/03/2015.
//  Copyright (c) 2015 Chewmba. All rights reserved.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

unsigned int res(const vector<unsigned int>& v, int m)
{
    int sz = v.size();
    vector<unsigned int> pref(sz);
    for (int i = 0; i < sz; i++)
    {
        pref[i] = i > 0 ? (v[i] + pref[i-1]) % m : v[i] % m;    
    }
    
    int max_ = numeric_limits<int>::min();
    
    for (int i = 0; i < sz - 1; i++ )
    {
        for (int j = sz-i; j > 0; j-- )
        {
            int prev = i == 0 ? 0 : pref[i-1];
            int x = pref[j-1] - prev % m;
            x = x < 0 ? m + x : x;
            pref[j-1] >= prev ?  (pref[j-1] - prev) % m :
            
            max_ = std::max(max_, x);
        }
    }
    
    return max_;
}

int main() {
    int t;
    
    vector<int> vec0(10, 1);
    
    cin >> t; // num test cases
    for (int i = 0; i < t; i++)
    {
        int n, m;
        cin >> n >> m;
        vector<unsigned int> v(n);
        for (int j = 0; j < n; j++)
        {
            unsigned int val;
            cin >> val;
            v[j] = val;
        }
        cout << res(v, m);
    }
    return 0;
}
