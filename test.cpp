#include <bits/stdc++.h>
/*
#ifdef debug
#endif
#ifndef debug
#endif
*/
using namespace std;

struct seg{
	int first;
	int second;
	bool operator<(const seg &other) const {
		if (this -> first != other.first) {
			return this -> first < other.first;
		} else {
			return this -> second > other.second;
		}
	}
};

set <seg> mp1;
set <seg> mp2;
vector <int> prefixSum1;
vector <int> prefixSum2;


signed main()    //    https://oj.ntucpc.org/contests/18/problems/852
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
	int n;
	cin >> n;
	prefixSum1.resize(n + 1);
	prefixSum2.resize(n + 1);
	int tmp;
	for (int i = 1; i <= n; i++) {
		cin >> tmp;
		prefixSum1[i] = prefixSum1[i - 1] + tmp;
	}
	for (int i = 1; i <= n; i++) {
		cin >> tmp;
		prefixSum2[i] = prefixSum2[i - 1] + tmp;
	}
	//prefixSum2[1, i] + prefixSum1[i + 1, n]
	//prefixSum2[0...n]
	int maxL = -1, maxR = -1;
	int maxV = prefixSum1[n] > prefixSum2[n] ? prefixSum1[n] : prefixSum2[n];

	for (int i = 0; i <= n; i++) {
		mp1.insert({prefixSum2[i] + prefixSum1[n] - prefixSum1[i], i});
		mp2.insert({prefixSum1[i] + prefixSum2[n] - prefixSum2[i], i});
	}	
	mp1.erase({prefixSum2[0] + prefixSum1[n] - prefixSum1[0], 0});
	mp2.erase({prefixSum1[0] + prefixSum2[n] - prefixSum2[0], 0});
	for (int i = 0; i < n; i++) {
		auto it1 = mp1.rbegin();
		auto it2 = mp2.rbegin();
		while (it1->second <= i) {
			mp1.erase({it1->first, it1->second});
			it1 = mp1.rbegin();
		}
		while (it2->second <= i) {
			mp2.erase({it2->first, it2->second});
			it2 = mp2.rbegin();
		}
		int sum1 = prefixSum1[i] + it1 -> first - prefixSum2[i];
		int sum2 = prefixSum2[i] + it2 -> first - prefixSum1[i];
		if (sum1 > maxV) {
			maxV = sum1;
			maxL = i + 1;
			maxR = it1 -> second;
		}
		if (sum2 > maxV) {
			maxV = sum2;
			maxL = i + 1;
			maxR = it2 -> second;

		}
	}	
	cout << maxV << " " << maxL << " " << maxR;
	return 0;
}
