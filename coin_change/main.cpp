//
//  main.cpp
//  coin_change
//
//  Created by Igor Makaruks on 14/03/2015.
//  Copyright (c) 2015 Chewmba. All rights reserved.
//

#include <iostream>

#include <assert.h>

#include <sstream>

#include <random>
#include <functional>


template <typename T>
class Matrix
{

public:
	using Size = unsigned int;
	Matrix(Size w, Size h) : _w(w), _h(h) 
	{
		_data = new T*[w];
		for (Size i = 0; i < w; i++)
			_data[i] = new T[h];
  	}

	Matrix(Size w, Size h, T value) : Matrix(w,h)
	{
		for (Size i = 0; i < w; i++)
			for (Size j = 0; j < h; j++)
				_data[i][j] = value;
	}

	T& operator() (Size i, Size j)
	{
		assert(i < _w && j < _h);
		return _data[i][j];
	}
    
    T& operator() (Size i, Size j) const
	{
		assert(i < _w && j < _h);
		return _data[i][j];
	}

	friend std::ostream& operator << (std::ostream& s, const Matrix<T>& m)
	{
		for (Size i = 0; i < m._w; i++)
		{
			for (Size j = 0; j < m._h; j++)
			{
				s << m(i,j) << " ";
			}
			s << std::endl;
		}
		return s;
	}

private:
	T** _data = nullptr;
	Size _w = 0;
	Size _h = 0;
};

int numChange(int N, const std::vector<int> S)
{
	// Assume that S is sorted
	//auto t = std::find_if(S.begin(), S.end(), [=](decltype(S)::reference e) { return e > N; });
    auto t = std::find_if(S.begin(), S.end(), [=](int e) { return e > N; });
	std::size_t idx = 0; // index of an element that is larger than N
	if (t == S.end())
		idx = S.size();
	else
		idx = std::distance(S.begin(), t);
	Matrix<int> table(N+1, idx);
	for (int i = 0; i<idx; i++)
		table(0, i) = 1;
	table(0,0) = 0;

	for (int n = 1; n <= N; n++)
	{
		for (int j = 1; j < idx; j++)
		{
			// F(N, m-1)
			int F1 = j > 1 ? table(n, j-1) : 0;
			// F(N-m, m)
			int F2 = n >= S[j-1]	? table(n-S[j-1], j) : 0;
			table(n, j) = F1 + F2;
		}
	}

	return table(N, idx-1);
}

int main(int argc, const char * argv[])
{
    using namespace std;
    // Random
    std::uniform_int_distribution<uint32_t> unif{1, 100};
    std::random_device rd;
    std::mt19937 engine(rd());
    //std::function<uint32_t()> rnd = std::bind(unif, engine);
    auto rnd = std::bind(unif, engine);
   
	int m, n;
    m = n = 10;
	//cin >> m >> n;

	Matrix<int> mat(m, n, 0);
	for (int i=0; i<m; i++)
		for (int j=0; j<n; j++)
			mat(i,j) = rnd();

	cout << mat;
    
    vector<int> change {1, 2, 5, 10, 20, 50};
    auto res = numChange(10, change);
    cout << res << endl;


    int z = 2 - 5 % 7;
    cout << z;
    

    std::cout << "Hello, World!\n";
    return 0;
}
