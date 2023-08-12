#include<bits/stdc++.h>
#define pb push_back
#define all(x) x.begin(),x.end()
#define rall(x) x.rbegin(),x.rend()
#define ones(x) __builtin_popcountll(x)
#define int long long
#define pii pair<int,int>
#define mii map<int,int>
#define vi vector<int>
#define vvi vector<vector<int>>
#define vpii vector<pair<int, int>>
using namespace std;

const int mod = 1e9+7;
int segTree[10000006];
int lazy[10000006];

int powmod(int a,int b){
	int ans=1;
	while(b>0){
		if(b&1) ans=(ans*a)%mod;
		a=(a*a)%mod;
		b>>=1;
	}
	return ans%mod;
}

void build(int start, int end, int node){
    if(start==end){
        segTree[node] = 0;
        lazy[node] = -1;
        return;
    }
    int mid = (start+end)/2;
    build(start, mid, 2*node+1);
    build(mid+1, end, 2*node+2);
    segTree[node] = 0;
    lazy[node] = -1;
}

void update(int start, int end, int l, int r, int val, int node){
    if(lazy[node]!=-1){
        segTree[node] = lazy[node];
        if(start!=end){
            lazy[2*node+1] = lazy[node];
            lazy[2*node+2] = lazy[node];
        }
    }
    // No overlap
    if(start>r || end<l){
        return;
    }
    // Complete overlap
    if(start>=l && end<=r){
        lazy[node] = val;
        if(start!=end){
            lazy[2*node+1] = val;
            lazy[2*node+2] = val;
        }
        return;
    }
    // Partial overlap
    int mid = (start+end)/2;
    update(start, mid, l, r, val, 2*node+1);
    update(mid+1, end, l, r, val, 2*node+2);
    lazy[node] = -1;
}

int query(int start, int end, int l, int r, int node){
    if(lazy[node]!=-1){
        segTree[node] = lazy[node];
        if(start!=end){
            lazy[2*node+1] = lazy[node];
            lazy[2*node+2] = lazy[node];
        }
    }
    // No overlap
    if(start>r || end<l){
        return 0;
    }
    // Complete overlap
    if(start>=l && end<=r && lazy[node]!=-1){
        if(lazy[node]==0){
            return 0;
        }
        int res = (powmod(2, end-start+1)-1)%mod;
        res = (res*powmod(2, r-end))%mod;
        return res%mod;
    }
    // Partial overlap
    int mid = (start+end)/2;
    int p1 = query(start, mid, l, r, 2*node+1);
    int p2 = query(mid+1, end, l, r, 2*node+2);
    return (p1+p2)%mod;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, q;
    cin>>n;
    build(0, n-1, 0);
    cin>>q;
    while(q--){
        int l, r, k;
        cin>>k>>l>>r;
        if(k<=1){
            update(0, n-1, l, r, k, 0);
            continue;
        }
        cout<<query(0, n-1, l, r, 0)<<endl;
    }
    return 0;
}