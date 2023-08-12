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

void build(int s, int e, int index) // O(n)
{
    // leaf node
    if (s == e)
    {
        segTree[index] = a[s];
        return;
    }

    int mid = (s + e) / 2;
    build(s, mid, 2 * index);
    build(mid + 1, e, 2 * index + 1);

    segTree[index] = max(segTree[2 * index], segTree[2 * index + 1]);
    return;
}

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
    // build(0, n-1, 0);
    cin>>q;
    while(q--){
        int l, r, k;
        cin>>l>>r>>k;
        l--, r--;
        int ans = 0;
        
    }

    return 0;
}