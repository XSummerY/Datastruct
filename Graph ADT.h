#pragma once
#include<queue>
class Graph {
private:
	void operator=(const Graph&){}
	Graph(const Graph&){}
public:
	Graph(){}
	virtual ~Graph(){}

	//Initialize a graph of n vertices
	virtual void Init(int n) = 0;

	//Return: the number of vertices and edges
	virtual int n() = 0;
	virtual int e() = 0;

	//Return v's first neighbor
	virtual int first(int v) = 0;

	//Return v's next neighbor
	virtual int next(int v, int w) = 0;

	//Set the weight for an edge
	//i,j:the vertices
	//wgt:Edge weight
	virtual void setEdge(int v1, int v2, int wght) = 0;

	//Delete an edge
	virtual void delEdge(int v1, int v2) = 0;

	//Determine if an edge is in the graph
	//Return:true if edge i,j has non-zero weight
	virtual bool isEdge(int i, int j) = 0;

	//Return an edge's weight
	//Return:The weight of edge i,j, or zero
	virtual int weight(int v1, int v2) = 0;

	//Get and Set the mark value for a vertex
	//val:The value to set
	virtual int getMark(int v) = 0;
	virtual void setMark(int v, int val) = 0;

	//Two kinds of Search
	virtual void DFS(int v) = 0;
	virtual void BFS(int v,std::queue<int>*Q,bool FLAG) = 0;
};

