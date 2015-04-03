//
//  main.cpp
//  levenshtein
//
//  Created by Igor Makaruks on 21/03/2015.
//  Copyright (c) 2015 Chewmba. All rights reserved.
//

#include <iostream>
#include <vector>
#include <numeric>

unsigned levenshtein(const std::string& a, const std::string& b)
{
    if (a == b)
        return 0;
    
    std::string A{a};
    std::string B{b};
    if (a.size() < b.size())
        std::swap(A, B);
    
    std::vector<int> D(B.size()+1);
    
    std::iota(D.begin(), D.end(), 0); // D = [0, 1, 2, 3,..., B.size()]
    
    for (int i = 1; i <= A.size(); i++)
    {
        int pre_i1_j1 = D[0]; // D[i-1][j-1]
        D[0] = i; // D[i, 0] = i;
        for (int j = 0; j <= B.size(); j++)
        {
        
        }
    }
    
    return 0;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
