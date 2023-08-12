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

const int N = 1e5+5;
int a[N];
int segTree[4*N];

void build(int start, int end, int node){
    if(start==end){
        segTree[node] = a[start];
        return;
    }
    int mid = (start+end)/2;
    build(start, mid, 2*node+1);
    build(mid+1, end, 2*node+2);
    segTree[node] = segTree[2*node+1] + segTree[2*node+2];
}

int query(int start, int end, int l, int r, int node){
    // No overlap
    if(start>r || end<l){
        return 0;
    }
    // Complete overlap
    if(start>=l && end<=r){
        return segTree[node];
    }
    // Partial overlap
    int mid = (start+end)/2;
    int p1 = query(start, mid, l, r, 2*node+1);
    int p2 = query(mid+1, end, l, r, 2*node+2);
    return p1+p2;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n; cin>>n;
    for(int i=0; i<n; i++){
        cin>>a[i];
    }
    build(0, n-1, 0);
    int q; cin>>q;
    while(q--){
        int l, r; cin>>l>>r;
        l--; r--;
        cout<<query(0, n-1, l, r, 0)<<endl;
    }

    return 0;
}