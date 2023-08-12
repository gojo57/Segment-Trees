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
int segTree[4*N];
int a[N];

void build(int *a, int s, int e, int *tree, int index) // O(n)
{
    // leaf node
    if (s == e)
    {
        tree[index] = a[s];
        return;
    }

    int mid = (s + e) / 2;
    build(a, s, mid, tree, 2 * index);
    build(a, mid + 1, e, tree, 2 * index + 1);

    tree[index] = min(tree[2 * index], tree[2 * index + 1]);
    return;
}

int query(int *tree, int ss, int se, int qs, int qe, int index){  // O(logn)
    //Complete Overlap
    if(ss>=qs && se<=qe){
        return tree[index];
    }

    //No Overlap
    if(qe<ss || qs>se){
        return INT_MAX;
    }

    //Partial Overlap
    int mid = (ss+se)/2;
    int left = query(tree, ss, mid, qs, qe, 2*index);
    int right = query(tree, mid+1, se, qs, qe, 2*index+1);

    return min(left, right); 
}

void update(int *tree, int ss, int se, int i, int increment, int index){  // O(logn)
    //Out of bounds
    if(i>se || i<ss){
        return;
    }

    //Leaf Node
    if(ss==se){
        tree[index] = increment;
        return;
    }

    //Left and Right
    int mid = (ss+se)/2;
    update(tree, ss, mid, i, increment, 2*index);
    update(tree, mid+1, se, i, increment, 2*index+1);

    tree[index] = min(tree[2*index], tree[2*index+1]);
    return;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n, q; cin>>n>>q;
    for(int i=0; i<n; i++){
        cin>>a[i];
    }
    // Build
    build(a, 0, n-1, segTree, 1);
    while(q--){
        int type,l,r;
        cin>>type>>l>>r;
        if(type==1){
            // Print
            cout<<query(segTree, 0, n-1, l-1, r-1, 1)<<"\n";
        }
        else{
            // Update
            update(segTree, 0, n-1, l-1, r, 1);
        }
    }
    
    return 0;
}