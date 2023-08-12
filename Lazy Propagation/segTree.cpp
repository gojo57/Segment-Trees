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

int lazy[1000000] = {0};

void buildTree(int *a, int s, int e, int *tree, int index) // O(n)
{
    // leaf node
    if (s == e)
    {
        tree[index] = a[s];
        return;
    }

    int mid = (s + e) / 2;
    buildTree(a, s, mid, tree, 2 * index);
    buildTree(a, mid + 1, e, tree, 2 * index + 1);

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
        tree[index] += increment;
        return;
    }

    //Left and Right
    int mid = (ss+se)/2;
    update(tree, ss, mid, i, increment, 2*index);
    update(tree, mid+1, se, i, increment, 2*index+1);

    tree[index] = min(tree[2*index], tree[2*index+1]);
    return;
}

void rangeUpdate(int *tree, int ss, int se, int l, int r, int inc, int index){  // O(n)
    //Out of bounds
    if(l>se || r<ss){
        return;
    }

    //Leaf Node
    if(ss==se){
        tree[index] += inc;
        return;
    }

    //Left and Right
    int mid = (ss+se)/2;
    rangeUpdate(tree, ss, mid, l, r, inc, 2*index);
    rangeUpdate(tree, mid+1, se, l, r, inc, 2*index+1);

    tree[index] = min(tree[2*index], tree[2*index+1]);
    return;
}

void updateRangeLazy(int *tree, int ss, int se, int l, int r, int inc, int index){  // O(logn)
    //First step - Never go down if you have lazy value at node, first resolve it
    if(lazy[index]!=0){
        tree[index] += lazy[index];
        //if not a leaf node
        if(ss!=se){ // pass the lazy value to children
            lazy[2*index] += lazy[index];
            lazy[2*index+1] += lazy[index];
        }
        lazy[index] = 0;
    }

    //Out of bounds
    if(l>se || r<ss){
        return;
    }

    //Complete Overlap
    if(ss>=l && se<=r){
        tree[index] += inc;
        //Pass the lazy value to children
        if(ss!=se){
            lazy[2*index] += inc;
            lazy[2*index+1] += inc;
        }
        return;
    }

    //Partial Overlap
    int mid = (ss+se)/2;
    updateRangeLazy(tree, ss, mid, l, r, inc, 2*index);
    updateRangeLazy(tree, mid+1, se, l, r, inc, 2*index+1);

    tree[index] = min(tree[2*index], tree[2*index+1]);
    return;
}

int queryLazy(int *tree, int ss, int se, int qs, int qe, int index){  // O(logn)
    //First step - Never go down if you have lazy value at node, first resolve it
    if(lazy[index]!=0){
        tree[index] += lazy[index];
        //if not a leaf node
        if(ss!=se){ // pass the lazy value to children
            lazy[2*index] += lazy[index];
            lazy[2*index+1] += lazy[index];
        }
        lazy[index] = 0;
    }

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
    int left = queryLazy(tree, ss, mid, qs, qe, 2*index);
    int right = queryLazy(tree, mid+1, se, qs, qe, 2*index+1);

    return min(left, right); 
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int a[] = {1, 3, 2, -5, 6, 4};
    int n = sizeof(a) / sizeof(a[0]);

    int tree[4 * n + 1];
    buildTree(a, 0, n - 1, tree, 1);

    updateRangeLazy(tree, 0, n-1, 0, 2, 10, 1);
    updateRangeLazy(tree, 0, n-1, 0, 4, 10, 1);
    cout<<queryLazy(tree, 0, n-1, 1, 1, 1)<<endl;
    updateRangeLazy(tree, 0, n-1, 3, 4, 10, 1);
    cout<<queryLazy(tree, 0, n-1, 3, 5, 1)<<endl;

    // update(tree, 0, n-1, 3, 10, 1);
    // rangeUpdate(tree, 0, n-1, 3, 5, 10, 1);

    // for (int i = 1; i <= 13; i++)
    //     cout << tree[i] << " ";

    // int q; cin>>q;
    // while(q--){
    //     int l, r; cin>>l>>r;
    //     cout<<query(tree, 0, n-1, l, r, 1)<<endl;
    // }

    return 0;
}