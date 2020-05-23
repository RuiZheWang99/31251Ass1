#include <iostream>
#include "MyGraph.h"
using namespace std;
int main(){
MyGraphType<int,100>myGraph;

myGraph.createGraph();
cout<<"The Adjacency List:"<<endl;
myGraph.printGraph();
cout<<"Depth First Traversal:"<<endl;
myGraph.depthFirstTraversal();

cout<<endl;
cout<<"Breadth First Traversal:"<<endl; myGraph.breadthFirstTraversal(); return 0;

}

