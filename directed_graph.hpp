#ifndef DIRECTED_GRAPH_H
#define DIRECTED_GRAPH_H

#include <fstream> 
#include <queue> 
#include <list> using namespace std; 

class MyList:public list<vType>{ public:
void getAdjacentVertices(vType [],int &);
};
template <class vType>
void MyList<vType>::getAdjacentVertices(vType adjacencyList[], int &length){ length = 0;

for(list<vType>::iterator it = begin();it != end();++ it){ adjacencyList[length ++] = *it;

}
}

public:


MyGraphType();

~MyGraphType();



bool isEmpty();

void printGraph();

void dft(int v,bool visited[]);

void depthFirstTraversal();
void dftAtVertex(int v);

void breadthFirstTraversal();
 
private:

int maxSize;
int gSize;

MyList<vType>*graph;
};
template <class vType,int size> MyGraphType<vType,size>::MyGraphType(){


maxSize = size;
gSize = 0;
graph = new MyList<vType>[maxSize];
}

template <class vType,int size> MyGraphType<vType,size>::~MyGraphType(){

clearGraph();
delete []graph;

}
template <class vType,int size>
bool MyGraphType<vType,size>::isEmpty(){ return (0 == gSize);

}

template <class vType,int size>
void MyGraphType<vType,size>::createGraph(){ ifstream infile;
char fileName[50];
vType vertex;

vType adjacencyVertex;

if(0 != gSize){
clearGraph();

}

cout<<"Enter the input file name:";
cin>>fileName;


infile.open(fileName);

if(infile.fail()){
cout<<infile.fail()<<endl;

cout<<"Can't open the file!"<<endl;
return;
}


infile>>gSize;
for(int i(0);i < gSize;++ i){

infile>>vertex;


infile>>adjacencyVertex;

while(adjacencyVertex != -999){
graph[i].push_back(adjacencyVertex);
 
infile>>adjacencyVertex;

}
}


infile.close();
}
template <class vType,int size>
void MyGraphType<vType,size>::clearGraph(){ //clear all the graph lists for(int i = 0;i < gSize;++ i){
graph[i].clear();
}
gSize = 0;

}
template <class vType,int size>
void MyGraphType<vType,size>::printGraph(){


for(int i = 0;i < gSize;++ i){
cout<<i<<"->";
for(list<vType>::iterator it = graph[i].begin();it != graph[i].end();++ it){

cout<<*it<<" ";

}
cout<<endl;
}
}
template <class vType,int size>

void MyGraphType<vType,size>::dft(int v, bool visited[]){ vType w;



adjacencyList = new vType[gSize];
int alLength = 0;
visited[v] = true;


cout<<" "<<v<<" ";

graph[v].getAdjacentVertices(adjacencyList,alLength);
for(int i(0);i <alLength;++ i){
w = adjacencyList[i];

if(!visited[w]){

dft(w,visited);
}
}


delete [] adjacencyList;
}

template <class vType,int size>

void MyGraphType<vType,size>::depthFirstTraversal(){ bool *visited;
visited = new bool[gSize];

 
for(int i(0);i < gSize;++ i){

visited[i] = false;
}


for(int i(0);i < gSize;++ i){
if(!visited[i]){
dft(i,visited);
}

}
delete [] visited;
}
template <class vType,int size>
void MyGraphType<vType,size>::dftAtVertex(int v){ bool *visited;
visited = new bool[gSize];
for(int i(0);i < gSize;++ i){
visited[i] = false;
}


dft(v,visited);
delete [] visited;
}


template <class vType,int size>
void MyGraphType<vType,size>::breadthFirstTraversal(){ queue<vType> Queue;
int u;
bool *visited;


visited = new bool[gSize];
for(int i(0);i < gSize;++ i){
visited[i] = false;
}


adjacencyList = new vType[gSize];
int alLength = 0;

for(int i(0);i < gSize;++ i){


Queue.push(i);

visited[i] = true;
cout<<" "<<i<<" ";
while(Queue.size() != 0){

u = Queue.front();

Queue.pop();

for(int j(0);j < alLength;++ j){
if(!visited[adjacencyList[j]]){
Queue.push(adjacencyList[j]);
visited[adjacencyList[j]] = true;
 
cout<<" "<<adjacencyList[j]<<" ";

}
}

}
}
}
//deallocate
delete []visited;

delete []adjacencyList;
}

#endif

