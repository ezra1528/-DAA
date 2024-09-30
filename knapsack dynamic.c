#include <iostream>
using namespace std;
int max(int a,int b){
    if (a>b){
        return a;
    }
    else{
        return b;
    }
}
void knapsack(int p[],int wt[],int k[][],int n,int m){
    int i,j,w;
    for(i=0;i<=n;i++){
        for(w=0;w<=m;w++){
            if(i==0||w==0){
                k[i][w]=0;
            }
            else if(wt[i]<=w){
                k[i][w]=max(p[i]+k[i-1][w-wt[i],k[i-1][w]);
            }
            else{
                k[i][w]=k[i-1][w];
            }
        }
    }
    cout << k[n][w];
    i=n;
    j=m;
    while (i>0 && j>0){
        if(k[i][j]==k[i-1][j]){
            cout<< i << "=0 not included"<<endl;
            i--;
        }
        else{
            cout << i <<"=1 included"<<endl;
            i--;
            j=j-wt[i];
        }
    }
}
int main(){
    int n,m,i;
    cout <<"Enter the number of items :";
    cin >>n;
    int p[n],wt[n];
    cout<<"Enter the profit and weight of each items"<<endl;
    for(i=0;i<n;i++){
        cout << "item" << i << ": ";
        cin>> p[i] >>wt[i];
    }
    cout << "values inserted"<<endl;
    cout << "Enter the weight of the kanpsack :";
    cin >> m;
    int k[n+1][m+1];
    knapsack(p,wt,k,n,m);
    return 0;
}
