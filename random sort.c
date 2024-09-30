#include<iostream>
#include<cstdlib>
using namespace std;
void swap(int *a,int *b){
    int temp = a;
    a=b;
    b=temp;
}
void randomq(int arr[],int beg,int end){
    int mid = (beg+end)/2;
    if(beg==end){
        return;
    }
    else{
        int p = rand()%(end-beg+1);
        randomq()
    }
}
