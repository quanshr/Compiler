#include <bits/stdc++.h>
using namespace std;

int main() {
    map<int,int> mp;
    mp[4]=mp[4];
    for(auto it:mp)
    {
		printf("%d %d\n",it.first,it.second);
	}
    return 0;
}

