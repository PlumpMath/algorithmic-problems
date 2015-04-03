//
//  main.cpp
//  candies
//
//  Created by Igor Makaruks on 20/03/2015.
//  Copyright (c) 2015 Chewmba. All rights reserved.
//

#include <iostream>

#include <vector>

using namespace std;

class Solution {
public:
    int candy(vector<int>& ratings)
    {
        auto size = ratings.size();
        if (size == 0)
            return 0;
        if (size == 1)
            return 1;
        
        vector<int> candies(size, 1);
        vector<int> candies2(size, 1);
            
        for (auto i = 1; i < size; i++)
            candies[i] = (ratings[i] > ratings[i-1]) ? (candies[i-1] + 1) : candies[i];
        
        for (auto i = size-2; i >= 0; i--)
        {
            candies2[i] = (ratings[i] > ratings[i+1]) ? (candies2[i+1]+1) : candies2[i];
        }
        
        int ret = 0;
        for (auto i = 0; i < size; i++)
            ret += max(candies[i], candies2[i]);
            
        return ret;
    }
};


int main(int argc, const char * argv[])
{
    Solution s;
    vector<int> v{2,2};
    std::cout << s.candy(v);
    return 0;
}


