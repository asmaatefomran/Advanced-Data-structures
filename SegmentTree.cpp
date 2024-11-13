#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#define Asma ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#define testcase  while(t--)
#define ll long long
#define endl "\n"

using namespace std;

ll merge(ll a,ll b){
    return min(a,b);
}

struct SegmentTree{
#define L node*2+1
#define R node*2+2
#define mid (l+r>>1)
private:
    int sz,skip=1e9+5,n;
    vector<ll>sg;
    void build(int l,int r,int node,const vector<ll>&v){
        if(l==r){
            if(l<v.size())sg[node]=v[l];
            return;
        }
        build(l,mid,L,v);
        build(mid+1,r,R,v);
        sg[node]= merge(sg[L],sg[R]);
    }
 
    void update(int l,int r,int node,int indx,ll val){
        if(l==r&&l==indx){
            sg[node]=val;
            return;
        }
        if(indx<=mid)update(l,mid,L,indx,val);
        else update(mid+1,r,R,indx,val);
        sg[node]=merge(sg[L],sg[R]);
    }
 
    ll get(int l,int r,int node,int lx,int rx ){
        if(lx>r||rx<l)return skip;
        if(lx<=l&&rx>=r)return sg[node];
        ll left=get(l,mid,L,lx,rx);
        ll right=get(mid+1,r,R,lx,rx);
        return merge(left,right);
    }
 
public:
    SegmentTree (const vector<ll>&v){
        n=v.size();
        sz=1;
        while(sz<n){
            sz<<=1;
        }
        sg.resize(sz<<1,skip);
        build(0,n-1,0,v);
    }
    void update(int indx,ll val){
        update(0,n-1,0,indx,val);
    }
    ll get(int start,int end){
        return get(0,n-1,0,start,end);
    }
 #undef L
 #undef R
 #undef mid
};
 
