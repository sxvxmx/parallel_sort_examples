#include <bits/stdc++.h>

using namespace std;

template<typename T>
void print_vec(vector<T>& vec){
    cout<<"[ ";
    for(auto i = vec.begin();i != vec.end();i++)
        cout<<*i<<" ";
    cout<<"]";
}

vector<int> create_vec(int size, int seed){
    std::minstd_rand simple_rand;
    simple_rand.seed(seed);
    vector<int> v(size);
    for(int i = 1;i<=size;i++){
        int a = abs(int(simple_rand() % 10));
        v[i-1] = a;
    }
    return v;
}
