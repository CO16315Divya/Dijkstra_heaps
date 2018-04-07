#include <iostream>
#include<climits>
#include<stdlib.h>
using namespace std;
#define MAX 100
int flag=0,count=1;

struct node
{
    bool includeset;
    int finaldist;
    int pred;
    int number;

};
struct node temp;
struct node nodearray[MAX];
struct node newset[MAX];


void display(struct node newset[MAX], int n)
{
    cout<<"\nvertex"<<"\t\t\t"<<"Minimum distance"<<endl;

    for(int i=1; i<=n; i++)
    {
        cout<<i<<"\t\t\t";
        cout<<newset[i].finaldist<<endl;

    }


}
int min_heapify(struct node nodearray[],int r)
{


    int  ptr=1;
    int left = 2;

    while(left < r)
    {

        int  ptr=1;
        int left = 2;
        int right = 3;

        if(nodearray[ptr].finaldist <= nodearray[left].finaldist && nodearray[ptr].finaldist <= nodearray[right].finaldist) return r;

        if(nodearray[right].finaldist >= nodearray[left].finaldist)
        {

            swap(nodearray[ptr], nodearray[left]);
            ptr = left;
        }
        else
        {

            swap(nodearray[ptr], nodearray[right]);
            ptr = right;
        }
        left = 2*ptr;
        right = left + 1;
    }
    /*if(left==r)
    {
        if(nodearray[ptr].finaldist < nodearray[left].finaldist ) return r;
        if(nodearray[ptr].finaldist >= nodearray[left].finaldist)
        {

            swap(nodearray[ptr], nodearray[left]);
            ptr = left;
            return r;
        }
    }*/
    return r;
}
int  extract_min(struct node nodearray[MAX],int q)
{

    struct node p;

    if(q<1)
    {
        cout<<"heap underflow";
    }
    nodearray[1].includeset=true;
    p=nodearray[1];
    temp=p;
    nodearray[1]=nodearray[q];
    q=q-1;

    q=min_heapify(nodearray,q);

    return q;

}
int  decreasekey(struct node nodearray[MAX],int arrk[MAX][MAX],int p,int x,int v)
{
    int g,h;
    cout<<"p="<<p<<"\n";
    cout<<"\n x="<<x<<endl;
    for(int j=1; j<=v+1; j++)
    {
       // cout<<"j= "<<j<<endl;;

        if(arrk[x][j]!=0)
        {
            int k=1;
            //cout<<"\n v= "<<v<<endl;
            while(k < v+2)
            {
                 //cout<<"\nk= "<<k<<endl;
                if(nodearray[k].number==j)
                {
                    h=k;
                    g=nodearray[k].number;
                    cout<<"\ng="<<g<<"\n";
                    break;
                }
                else k++;

            }

            cout<<"g="<<g<<"\n";
            cout<<" arr[x][g]= "<<arrk[x][g];
            if(nodearray[h].finaldist > p + arrk[x][j])
            {

                nodearray[h].finaldist = p + arrk[x][j];
                nodearray[h].pred = x;
            }
            else
            {
                cout<<"newkey is greater than older key";
            }
        }
    }
    //cout<<"\nafter decrease key\n";
    //display(nodearray,v);
    return v;
}

void insert_in_heap(struct node nodearray[MAX],int i)
{



    nodearray[i].finaldist=INT_MAX;
    nodearray[i].pred=INT_MIN;
    nodearray[i].includeset=false;
    nodearray[i].number=i;



}

void dijkstra(int arrk[MAX][MAX],int source,int vertices )
{
    int nn = vertices;

    int i;
    for(i=1; i<=vertices; i++)
    {
        insert_in_heap(nodearray,i);
    }

    nodearray[source].finaldist=0;
    nodearray[source].pred=-1;
    nn= min_heapify(nodearray,nn);

    flag=vertices;
    while(flag!=0)
    {

        nn = extract_min(nodearray,nn);
        int index = temp.number;
        int sdist=temp.finaldist;
        temp.includeset=true;
        newset[count]=temp;
        //cout<<"\n minimum extracted ka finaldist "<<temp.finaldist<<endl;
        //cout<<"\nminimum extracted ka index "<<temp.number<<endl;
        nn=decreasekey(nodearray,arrk,sdist,index,nn);

        nn=min_heapify(nodearray,nn);

        count++;

        flag--;

    }
    display(newset, vertices);
}





int main()
{
    int i=0;



    int vp;

    int arrk[MAX][MAX], e;
    cout<<"enter the number of vertices(undirected graph)"<<endl;
    cin>>vp;
    cout<<"enter the number of edges"<<endl;
    cin>>e;
    if(vp<=0 || e<=0)
    {
        cout<<"\ninvalid input";
        return 0;
    }
    for(int i=1; i<=vp; i++)
    {
        for(int j=1; j<=vp; j++)
        {
            if(i!=j)
            {
                cout<<"Enter the edge length between "<<i<<" and "<<j<<" ";
                cin>>arrk[i][j];
            }
            else arrk[i][j]=0;

        }
    }

    cout<<"output matrix is ---->"<<endl;
    for(i=1; i<=vp; i++)
    {
        for(int j=1; j<=vp; j++)
        {

            cout<<"\t"<<arrk[i][j];

        }
        cout<<endl;
    }

    dijkstra(arrk,1,vp);






    return 0;
}
