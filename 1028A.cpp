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

char a[116][116];

int main(){

	int n,m;
	cin>>n>>m;
	FOR(i,1,n){
		FOR(j,1,m){
			cin>>a[i][j];
		}
	}
	int length=0;
	int br=-1, bc=-1;
	FOR(i,1,n){
		FOR(j,1,m)
		if(a[i][j]=='B'){
			if(br==-1 && bc==-1){
				br=i;
				bc=j;
			}
			length++;
		}
		if(br!=-1 and bc!= -1){
			break;
		}
	}
	br+=length/2 ;
	bc+=length/2 ;
	cout<<br<<" "<<bc<<endl;

	return 0;
}
