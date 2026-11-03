#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>
using namespace std;

int p(int st,int end,vector<int>&arr){
    int idx=st-1;
    int ele=arr[end];
    for(int i=st;i<end;i++){
        if(arr[i]<=ele){
            idx++;
            swap(arr[i],arr[idx]);
        }
    }

    idx++;
    swap(arr[idx],arr[end]);
    return idx;
}
int pc(int st,int end,vector<int>&arr){
    int r=st+rand()%(end-st+1);
    swap(arr[r],arr[end]);
    return p(st,end,arr); 
}
void solve(int st,int end,vector<int>&arr){
    if(st<end){
          int part=pc(st,end,arr);
    solve(st,part-1,arr);
    solve(part+1,end,arr);
    }
  
}
int main()
{
    int n;
    cin >> n;
    vector<int>arr;
    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        arr.push_back(x);
    }
    solve(0,n-1,arr);
    for(int i=0;i<n;i++){
        cout<<arr[i]<<"" ;
    }


}
