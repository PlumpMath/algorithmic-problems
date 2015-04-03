//
//  main.cpp
//  min_path_sum
//
//  Created by Igor Makaruks on 27/03/2015.
//  Copyright (c) 2015 Chewmba. All rights reserved.
//

// https://leetcode.com/problems/minimum-path-sum/

/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.
*/

#include <iostream>

#include <vector>

using namespace std;


template <typename T>
class Grid2
{
public:
    Grid2(unsigned m, unsigned n)
    {
        data_.reserve(m);
        for (int j = 0; j < m; j++)
            data_.push_back(std::vector<int>(n,0));
 
    }
    
    T& at(unsigned i, unsigned j) { return data_[i][j]; }
    
    const T& at(unsigned i, unsigned j) const { return data_[i][j]; }
    
private:
    vector<vector<T>> data_;
};

class Solution {
public:
    int minPathSum(vector<vector<int> > &grid)
    {
        // m[i, j] = min( m[i-1,j], m[i, j-1]  ) + V[i,j]
        auto m = grid.size();
        auto n = grid[0].size();
        if (m == 1 && n == 1)
            return grid[0][0];
            
        Grid2<int> mem(m,n);
        mem.at(0,0) = grid[0][0];
        
        for (int j = 1; j < n; j++)
            mem.at(0, j) = mem.at(0, j-1) + grid[0][j];
        
        for (int i = 1; i < m; i++)
            mem.at(i, 0) = mem.at(i-1, 0) + grid[i][0];
            
        for (int i = 1; i < m; i++)
            for (int j = 1; j < n; j++)
                mem.at(i,j) = std::min( mem.at(i-1,j), mem.at(i, j-1) ) + grid[i][j];
        
        return mem.at(m-1,n-1);
    }
};


int main(int argc, const char * argv[])
{
    Solution sln;
    
    vector<vector<int>> vec{{1,2},{1,1}};
    auto res = sln.minPathSum(vec);
    
    std::cout << "Hello, World!\n";
    return 0;
}
