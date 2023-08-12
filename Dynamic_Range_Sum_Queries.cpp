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

const int N=2e5+5;
int a[N],st[4*N];

void build(int node, int start, int end){
    if(start == end){
        st[node] = a[start];
    }
    else{
        int mid = (start + end) / 2;
        build(2*node, start, mid);
        build(2*node+1, mid+1, end);
        st[node] = st[2*node] + st[2*node+1];
    }
}

void update(int node, int start, int end, int idx, int val){
    if(start == end){
        st[node] = val;
        return;
    }
    int mid = (start + end) / 2;
    if(start <= idx and idx <= mid){
        update(2*node, start, mid, idx, val);
    }
    else{
        update(2*node+1, mid+1, end, idx, val);
    }
    st[node] = st[2*node] + st[2*node+1];
}

int query(int node, int start, int end, int l, int r){
    if(r < start or end < l){
        return 0;
    }
    if(l <= start and end <= r){
        return st[node];
    }
    int mid = (start + end) / 2;
    int p1 = query(2*node, start, mid, l, r);
    int p2 = query(2*node+1, mid+1, end, l, r);
    return (p1 + p2);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n,q;
    cin>>n>>q;
    for(int i=0;i<n;i++) cin>>a[i];
    build(1,0,n-1);
    while(q--)
    {
        int type, l, r;
        cin>>type>>l>>r;
        if(type==1)
        {
            l--;
            update(1,0,n-1,l,r);
        }
        else
        {
            l--,r--;
            cout<<query(1,0,n-1,l,r)<<endl;
        }
    }

    return 0;
}