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

struct segTree{
    vi st[N*4];

    void build(int start, int end, int node){
        if(start==end){
            st[node].pb(a[start]);
            return;
        }
        int mid = (start+end)/2;
        build(start, mid, 2*node+1);
        build(mid+1, end, 2*node+2);
        merge(st[2*node+1].begin(), st[2*node+1].end(), st[2*node+2].begin(), st[2*node+2].end(), back_inserter(st[node]));
    }

    int query(int start, int end, int l, int r, int k, int node){
        // No overlap
        if(start>r || end<l){
            return 0;
        }
        // Complete overlap
        if(start>=l && end<=r){
            return st[node].size() - (upper_bound(st[node].begin(), st[node].end(), k) - st[node].begin());
        }
        // Partial overlap
        int mid = (start+end)/2;
        int p1 = query(start, mid, l, r, k, 2*node+1);
        int p2 = query(mid+1, end, l, r, k, 2*node+2);
        return p1+p2;
    }

} tree;

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, q;
    cin>>n;
    for(int i=0; i<n; i++){
        cin>>a[i];
    }
    tree.build(0, n-1, 0);
    cin>>q;
    int ans = 0;
    while(q--){
        int l, r, k;
        cin>>l>>r>>k;
        l = l^ans;
        r = r^ans;
        k = k^ans;        
        ans = tree.query(0, n-1, l-1, r-1, k, 0);
        cout<<ans<<endl;
    }

    return 0;
}