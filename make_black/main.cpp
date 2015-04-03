//
//  main.cpp
//  make_black
//
//  Created by Igor Makaruks on 13/03/2015.
//  Copyright (c) 2015 Chewmba. All rights reserved.
//

#include <iostream>

#include <stack>

#include <random>
#include <functional>

//using BitMap = std::vector< std::vector<int> >;



template <typename T, T V>
class BitMap
{
    std::vector<T> data;
    int _m, _n;
    int dummy = 0;
    
    static const T kInvalid = V;
public:
    BitMap(int M, int N) : _m(M), _n(N)
    {
    // Random
    std::uniform_int_distribution<uint32_t> unif_100(1, 100);
    std::uniform_int_distribution<uint32_t> unif_10(1, 10);
    std::random_device rd;
    std::mt19937 engine(rd());
    
    auto rnd100 = std::bind(unif_100, engine);
    
    dummy = kInvalid;
    
        data.reserve(M*N);
        //data.resize(M*N, 0);
 
        std::generate_n(std::back_inserter(data), _m*_n, [&]() { return rnd100() > 30 ? 0 : 1; });
        std::cout << *this;

    }
    
    void print(std::ostream& stream) const
    {
        auto i = data.begin();
        int j = 0;
        while ( j < _n && i != data.end() )
        {
            std::copy(i, i+_m, std::ostream_iterator<uint32_t>(stream, ", "));
            stream << std::endl;
            std::advance(i, _m);
        }
        stream << std::flush;
    }
    
    
    
    bool fill(int x, int y)
    {
        if (get(x, y) == 1)
            return false;
        using namespace std;
        using V2 = pair<int, int>;
        stack<V2> s;
        
        s.push(make_pair(x, y));
        
        while (!s.empty())
        {
            auto p = s.top();
            s.pop();
            
            int x1 = p.first;
            int y1 = p.second;
            
            set(x1, y1, 1);
            
            auto checkSiblings = [&](int dx, int dy)
            {
                auto x2 = x1 + dx;
                auto y2 = y1 + dy;
                
                if (this->get(x2, y2) == 0)
                    s.push(make_pair(x2, y2));
            };
            
            checkSiblings(1, 0);
            checkSiblings(0, 1);
            checkSiblings(-1, 0);
            checkSiblings(-1, -1);

        }
        
    
        //if
        return true;
    }

protected:
    T get(int x, int y) { return x >= 0 && y >= 0 && x < _m && y < _n ? data[x + y*_m] : kInvalid; }
    void set(int x, int y, T v) { data[x + y*_m] = v; }
    
    //friend std::ostream& operator<< (std::ostream& s, const BitMap& b);
};


template <typename T, T V>
std::ostream& operator<< (std::ostream& s, const BitMap<T, V>& b)
{
    b.print(s);
    return s;
}



int main(int argc, const char * argv[])
{
    // Random
    std::uniform_int_distribution<uint32_t> unif_100(1, 100);
    std::uniform_int_distribution<uint32_t> unif_10(1, 10);
    std::random_device rd;
    std::mt19937 engine(rd());
    
    auto rnd100 = std::bind(unif_100, engine);
    auto rnd10 = std::bind(unif_10, engine);
    
    //shared_ptr<int> a;
    
    BitMap<int, -1> vec(8, 6);
    
    using namespace std;
    
    int x;
    cin >> x;
    int y;
    cin >> y;
    
    vec.fill(x, y);
    
    cout << endl;
    cout << vec;
    
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
