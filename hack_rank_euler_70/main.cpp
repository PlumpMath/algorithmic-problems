//
//  main.cpp
//  hack_rank_euler_70
//
//  Created by Igor Makaruks on 28/03/2015.
//  Copyright (c) 2015 Chewmba. All rights reserved.
//

#include <iostream>

#include <algorithm>

#include <set>
#include <vector>

//87109 is a permutation of 79180
bool isPermutation(unsigned a, unsigned b)
{
    using namespace std;
    multiset<unsigned> ma, mb;
    
    auto numToSet = [=](unsigned num, decltype(ma)& numSet)
    {
        while (num > 0) {
            unsigned a0 = num % 10;
            num /= 10;
            //numSet.emplace(a0);
            numSet.insert(a0);
        }
    };
    
    numToSet(a, ma);
    numToSet(b, mb);
    
    //decltype(ma) mc;
    multiset<unsigned> mc;
    std::set_difference(ma.begin(), ma.end(),
                    mb.begin(), mb.end(),
                    std::inserter(mc, mc.begin()));

    return mc.empty();
}

// 2,4,6,8,10,12,14
//  3  /6  9 /12 15 /18 21
// 5 /10 /15 /20 25

std::vector<unsigned> sieve(unsigned N)
{
    std::vector<unsigned> res;
    using namespace std;
    vector<unsigned char> s(N+1, 1);
    
    for (auto i = 2; i <= N; i++)
    {
        if (s[i] == 0)
            continue;
        auto j = i+i;
        while (j <= N)
        {
            s[j] = 0;
            j += i;
        }
    
    }
    
    for (auto i = 2; i <= N; i++)
        if (s[i])
            res.push_back(i);
    
    return move(res);
}

std::vector<unsigned> primesOf(unsigned N, const std::vector<unsigned>& allPrimes)
{
    std::vector<unsigned> res;
    using namespace std;
    
    unsigned i = 0;
    
    while (N > 1 && N >= allPrimes[i])
    {
        if (N % allPrimes[i] == 0)
        {
            res.push_back(allPrimes[i]);
            N /= allPrimes[i];
        }
        i++;
    }
    
    return move(res);
}

unsigned phi(unsigned N, const std::vector<unsigned>& primes)
{
    using namespace std;
    //unsigned res{N};
    double res = N;
    for (auto& x : primes)
        res *= (1. - (1./(double)x));
    
    return res;
    
}

/*
// n/ϕ(n)
double phiRatio(unsigned N, const std::vector<unsigned>& primes)
{
    using namespace std;
    double phi_ = phi(N, primes);
    
    return (double)N / phi_;
}
*/

int main(int argc, const char * argv[])
{
    using namespace std;
    unsigned a, b;
    //cin >> a >> b;
    //cout << endl << isPermutation(a, b) << endl;
    
    cin >> a;
    auto allPrimes = sieve(a);
    
    //std::copy(allPrimes.begin(), allPrimes.end(), std::ostream_iterator<uint32_t>(cout, ", "));
    //cout << endl;
    
    /*
    cin >> b;
    
    auto v2 = primesOf(b, allPrimes);
    std::copy(v2.begin(), v2.end(), std::ostream_iterator<uint32_t>(cout, ", "));
    cout << endl;
    */
    
    vector<pair<int, double>> results;
    
    for (auto i = 2; i < a; i++)
    {
        unsigned phi_ = phi(i, primesOf(i, allPrimes));
        if (isPermutation(i, phi_))
        {
            double ratio = (double)i/(double)phi_;
            //cout << i << " phi= " << phi_ << ";  ratio= " << ratio << endl;
            results.push_back(make_pair(i, ratio));
        
        }
    
    }
    
    sort(results.begin(), results.end(), [](pair<int, double>& x, pair<int, double>& y)
                {
                    return x.second < y.second;
                }
                );
    
    //cout << phi(b, v2) << endl;
    if (results.size() > 0)
        cout << results[0].first;
    else
        cout << 0;
    
    //std::cout << "Hello, World!\n";
    return 0;
}
