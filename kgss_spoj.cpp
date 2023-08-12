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
pii segTree[4*N];

void build(int node, int start, int end)
{
    if(start==end)
    {
        segTree[node] = pii (a[start], start);
        return;
    }

    int mid = (start+end)/2;
    build(2*node+1, start, mid);
    build(2*node+2, mid+1, end);

    segTree[node] = max(segTree[2*node+1], segTree[2*node+2]);
}

pii query(int node, int start, int end, int l, int r)
{
    if(start>r || end<l) return pii(-1, -1);
    if(start>=l && end<=r) return segTree[node];

    int mid = (start+end)/2;
    pii left = query(2*node+1, start, mid, l, r);
    pii right = query(2*node+2, mid+1, end, l, r);

    return max(left, right);
}

void update(int node, int start, int end, int idx, int val)
{
    if(start==end)
    {
        segTree[node] = pii(val, idx);
        return;
    }

    int mid = (start+end)/2;
    if(idx<=mid) update(2*node+1, start, mid, idx, val);
    else update(2*node+2, mid+1, end, idx, val);

    segTree[node] = max(segTree[2*node+1], segTree[2*node+2]);
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n; cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];

    build(0, 0, n-1);

    int q; cin>>q;
    while(q--)
    {
        char c; cin>>c;
        if(c=='U')
        {
            int idx, val; cin>>idx>>val;
            update(0, 0, n-1, idx-1, val);
        }
        else
        {
            int l, r; cin>>l>>r;
            pii ans = query(0, 0, n-1, l-1, r-1);
            int x = ans.first;
            update(0, 0, n-1, ans.second, -100);
            pii ans2 = query(0, 0, n-1, l-1, r-1);
            cout<<x+ans2.first<<"\n";
            update(0, 0, n-1, ans.second, x);
        }
    }

    return 0;
}