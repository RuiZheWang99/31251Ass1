//***************************************************** //MyGraph.h
//Header for test project of learning graph //It contains:
//	1.how to create a graph
//	2.Depth First Traversal
//	3.Breadth First Traversal //Author:binfeihan //Time:2011.08.15 //***************************************************** #ifndef __MYGRAPH_H_

#define __MYGRAPH_H_ #include <iostream> #include <fstream> #include <queue> #include <list> using namespace std; //***************************************************** //class:MyList //***************************************************** template <class vType>

class MyList:public list<vType>{ public:
void getAdjacentVertices(vType [],int &);
};
template <class vType>
void MyList<vType>::getAdjacentVertices(vType adjacencyList[], int &length){ length = 0;

for(list<vType>::iterator it = begin();it != end();++ it){ adjacencyList[length ++] = *it;

}
}
//***************************************************** //class:MyGraphType
//***************************************************** template <class vType,int size> class MyGraphType{

public:

//constructor
MyGraphType();
//destructor
~MyGraphType();
//if the graph is empty return false

//otherwise,return true
bool isEmpty();
//the graph is created using the adjacency list representation void createGraph();

//the memory occupied by each vertex is deallocated void clearGraph();
//the graph is printed
void printGraph();
//Depth First Traversal
void dft(int v,bool visited[]);

void depthFirstTraversal();
void dftAtVertex(int v);
//Breadth First Traversal
void breadthFirstTraversal();
 
private:

int maxSize;
int gSize;

MyList<vType>*graph;
};
template <class vType,int size> MyGraphType<vType,size>::MyGraphType(){

//constructor

//initialize and occupy the memory
maxSize = size;
gSize = 0;
graph = new MyList<vType>[maxSize];
}

template <class vType,int size> MyGraphType<vType,size>::~MyGraphType(){
//deallocate the memory
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
//if graph is not empty and
//clear it firstly
if(0 != gSize){
clearGraph();

}
//input the file name
cout<<"Enter the input file name:";
cin>>fileName;
//open the file with only read model

infile.open(fileName);
//if it's failed to open the file
//Post: error information and return
if(infile.fail()){
cout<<infile.fail()<<endl;

cout<<"Can't open the file!"<<endl;
return;
}
//read the data from file
//and assign to the list of graph

infile>>gSize;
for(int i(0);i < gSize;++ i){
//the vertex
infile>>vertex;
//the adjacency vertex

infile>>adjacencyVertex;
//-999 is the end of data in the line
while(adjacencyVertex != -999){
graph[i].push_back(adjacencyVertex);
 
infile>>adjacencyVertex;

}
}

//close the file
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
//print the graph
//Post:vertex->every adjacency vertex

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

//array to retrieve the adjacency vertices vType *adjacencyList;

//occupy memory to adjacency list

adjacencyList = new vType[gSize];
int alLength = 0;
visited[v] = true;
//v is visited
//Post: v

cout<<" "<<v<<" ";
//depth
graph[v].getAdjacentVertices(adjacencyList,alLength);
for(int i(0);i <alLength;++ i){
w = adjacencyList[i];

if(!visited[w]){
//recursion
dft(w,visited);
}
}

//deallocate
delete [] adjacencyList;
}
//Depth First Traversal
template <class vType,int size>

void MyGraphType<vType,size>::depthFirstTraversal(){ bool *visited;
visited = new bool[gSize];
//initialize boolean array of visited
 
for(int i(0);i < gSize;++ i){

visited[i] = false;
}

//visit all vertex
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

//depth first traversal from vertex v
dft(v,visited);
delete [] visited;
}
//Breadth First Traversal

template <class vType,int size>
void MyGraphType<vType,size>::breadthFirstTraversal(){ queue<vType> Queue;
int u;
bool *visited;

//occupy memory to visited
visited = new bool[gSize];
for(int i(0);i < gSize;++ i){
visited[i] = false;
}

//array to retrieve the adjacency vertices vType *adjacencyList;

//occupy memory to adjacency list
adjacencyList = new vType[gSize];
int alLength = 0;

for(int i(0);i < gSize;++ i){
//if the vertex is not visied and goto its depth //otherwise,it will continue if(!visited[i]){

Queue.push(i);

visited[i] = true;
cout<<" "<<i<<" ";
while(Queue.size() != 0){
//assign the top of queue to u
u = Queue.front();

//pop the top of queue
Queue.pop();
//the adjacency vertices of u graph[u].getAdjacentVertices(adjacencyList,alLength); //breadth
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

