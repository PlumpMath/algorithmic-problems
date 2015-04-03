
#include "iostream"
#include <vector>
#include <algorithm>

#include <stdexcept>

#include "regex"

using namespace std;

/*
const char* my_reverse(const char* s)
{
    //auto l = strlen(s);
    //char* ret = new char[l];
    
    auto i = &s[0];
    auto j = i;
    while (*j != '\0')
    {
        ++j;
    }
    auto len = j - i;

    return s;
}
*/

int main(int argc, char **argv)
{
    /*
    regex pat {R"(\w{2}\s*(\d{5}?))"};
    string s;
    while (getline(cin, s))
    {
        smatch matches;
        if (regex_search(s, matches, pat))
        {
            cout << matches[0] << endl;
            if ( 1 < matches.size() && matches[1].matched)
                cout << "\t: " << matches[1] << endl;
        }
    }
    */
    
    string s;
    //cin >> s;
    getline(cin, s);
    string s2 = my_reverse(s.c_str());
    cout << s << endl;
    
    return 0;
}