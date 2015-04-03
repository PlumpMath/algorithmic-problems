//
//  main.cpp
//  reverse_string
//
//  Created by Igor Makaruks on 21/03/2015.
//  Copyright (c) 2015 Chewmba. All rights reserved.
//

#include <iostream>
#include <string>

using namespace std;

class Solution {
public:
    void reverseWords(string &s) {
        auto sz = s.size();
        if (s == " ")
            s = "";

        
        // remove whitespaces
        if (s[0] == ' ')
        {
            int wIdx = 0;
            while (s[++wIdx] == ' ') {}
            s.erase(0, wIdx);
        }
        
        sz = s.size();
        if (sz <= 1)
            return;
            
        if (s[sz-1] == ' ')
        {
            int wIdx = sz-1;
            while (wIdx > 0 && s[--wIdx] == ' ') {}
            s.erase(wIdx+1);
        }
        
        sz = s.size();
        if (sz <= 1)
            return;
            
        auto reverseLetters = [=, &s] (int l, int r)
        {
            int i = l;
            int j = r;
            while (i < j)
            {
                std::swap(s[i], s[j]);
                i++;
                j--;
            }
        };
        // 1 reverse letters
        int i = 0;
        int j = sz - 1;
        reverseLetters(i, j);
        
        int prevIdx = 0;
        //for (int k = 1; k < sz; k++)
        int k = 1;
        while (k < s.size())
        {
            if (s[k] != 0 && s[k] == ' ')
            {
                if (s[k-1] == ' ')
                {
                    s.erase(k-1, 1);
                    continue;
                }
                reverseLetters(prevIdx, k-1);
                prevIdx = k+1;
                k++;
            }
            else
            {
                if (k == s.size()-1)
                {
                    reverseLetters(prevIdx, k);
                    k++;
                }
            }
        }
    }
};


int main(int argc, const char * argv[])
{
    Solution sln;
    string s = "   a   b  c d   e  ";
    sln.reverseWords(s);
    cout << s << endl;
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
