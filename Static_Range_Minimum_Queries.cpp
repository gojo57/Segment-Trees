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

void build(int si,int ss,int se)
{
    if(ss==se)
    {
        st[si]=a[ss];
        return;
    }
    int mid=(ss+se)/2;
    build(2*si,ss,mid);
    build(2*si+1,mid+1,se);
    st[si]=min(st[2*si],st[2*si+1]);
}

int query(int si,int ss,int se,int qs,int qe)
{
    if(qs>se || qe<ss) return INT_MAX;
    if(ss>=qs && se<=qe) return st[si];
    int mid=(ss+se)/2;
    int l=query(2*si,ss,mid,qs,qe);
    int r=query(2*si+1,mid+1,se,qs,qe);
    return min(l,r);
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
        int l,r;
        cin>>l>>r;
        cout<<query(1,0,n-1,l-1,r-1)<<endl;
    }

    return 0;
}