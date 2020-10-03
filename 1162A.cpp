#include <math.h>
#include <time.h>
#include <ctype.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <set>
#include <deque>
#include <queue>
#include <stack>
#include <bitset>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

#define sp system("pause")
#define FOR(i,a,b) for(int i=a;i<=b;++i)
#define FORD(i,a,b) for(int i=a;i>=b;--i)
#define REP(i,n) FOR(i,0,(int)n-1)
#define pb(x) push_back(x)
#define mp(a,b) make_pair(a,b)
#define MS0(x) memset(x,0,sizeof(x))
#define MS1(x) memset(x,1,sizeof(x))
#define SORT(a,n) sort(begin(a),begin(a)+n)
#define REV(a,n) reverse(begin(a),begin(a)+n)
#define ll long long
#define pii pair<int,int>
#define MOD 1000000007

int main(){

	int n,h,m;
	cin>>n>>h>>m;
	int arr[n];
	fill_n(arr, n, h);
	int sum=0;
	REP(i,m){
		int l,r,x;
		cin>>l>>r>>x;
		FOR(j,l,r){
			arr[j-1]=min(arr[j-1],x);
		}
	}
	for(int j=0; j< sizeof(arr)/sizeof(*arr); j++){
        sum += arr[j]*arr[j];
    }
    cout << sum;
	return 0;
}
