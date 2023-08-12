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

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n,q;
    cin>>n>>q;
    vi a(n);
    for(int i=0;i<n;i++) cin>>a[i];
    vi pre(n+1,0);
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+a[i-1];
    while(q--){
        int l,r;
        cin>>l>>r;
        cout<<pre[r]-pre[l-1]<<endl;
    }

    return 0;
}