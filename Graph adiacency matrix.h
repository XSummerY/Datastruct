#pragma once
#include<iostream>
#include<vector>
#include<queue>
#include<assert.h>
#include<limits.h>
#include"Graph ADT.h"
class Graphm :public Graph {
private:
	int numVertex, numEdge;
	int** matrix;
	int* mark;
public:
	Graphm(int numVert) {
		Init(numVert);
	}

	~Graphm() {
		delete[] mark;
		for (int i = 0; i < numVertex; i++) {
			delete[]matrix[i];
		}
		delete[]matrix;
	}

	void Init(int n) {
		int i;
		numVertex = n;
		numEdge = 0;
		mark = new int[n];
		for (i = 0; i < numVertex; i++) {
			matrix[i] = 0;//0 represent Vertex[i] is unvisited
		}
		matrix = (int**)new int* [numVertex];
		for (i = 0; i < numVertex; i++) {
			matrix[i] = new int[numVertex];
		}
		for (i = 0; i < numVertex; i++) {
			for (int j = 0; i < numVertex; j++) {
				matrix[i][j] = 0;
			}
		}
	}

	int n() { return numVertex; }
	int e() { return numEdge; }

	//Return first neighbor of "v"
	int first(int v) {
		for (int i = 0; i < numVertex; i++) {
			if (matrix[v][i] != 0) { return i; }
		}
		return numVertex;
	}

	//Return v's next neighbor after w
	int newxt(int v, int w) {
		for (int i = 1; i < numVertex; i++) {
			if (matrix[v][i] != 0) {
				return i;
			}
		}
		return numVertex;
	}

	//set edge (v1,v2) to wt
	void setEdge(int v1, int v2, int wt) {
		assert(wt > 0, "Illegal weight value");
		if (matrix[v1][v2] == 0)numEdge++;
		matrix[v1][v2] = wt;
	}
	
	void delEdge(int v1, int v2) {
		if (matrix[v1][v2] != 0)numEdge--;
		matrix[v1][v2] = 0;
	}

	bool isEdge(int i, int j) {
		return matrix[i][j] != 0;
	}

	int weight(int v1, int v2) {
		return matrix[v1][v2];
	}

	int getMark(int v) {
		return mark[v];
	}

	void setMark(int v, int val) {
		mark[v] = val;
	}

	void DFS(int v) {
		if (!this->getMark(v)) {
			this->setMark(v,1);//assume that the value of the mark is 1
			std::cout << " " << v;
		}

		for (int w = this->first(v); w < this->numVertex; w = this->next(v, w)) {
			if (w == -1) {
				break;
			}
			else {
				DFS(w);
			}

		}
		return;
	}
	void allDFS() {
		bool FLAG = false;
		for (int i = 0; i < this->numVertex; i++) {
			if (!this->getMark(i)) {
				if (FLAG) {
					std::cout << std::endl;
				}
				FLAG = true;
				std::cout << "{";
				DFS(i);
				std::cout << " }";
			}
		}
	}

	void BFS(int start, std::queue<int>* Q, bool FLAG) {
		int v, w;
		Q->push(start);
		this->setMark(start,1);
		if (FLAG) {
			std::cout << std::endl;
			FLAG = false;
		}
		while (!Q->empty()) {
			v = Q->front();
			if (!FLAG) {
				std::cout << "{";
				FLAG = true;
			}
			std::cout << " " << v;
			Q->pop();
			for (w = this->first(v); w != -1; w = this->next(v, w)) {
				if (!this->getMark(w)) {
					this->setMark(w,1);
					Q->push(w);
				}
			}
		}
		std::cout << " }";
		int next = -1;
		for (int i = 0; i < numVertex; i++) {
			if (!mark[i]) {
				next = i;
				break;
			}
		}
		if (next != -1) {
			BFS(next, Q, true);
		}
	}
	int Prim() {
		std::vector<int> Prims;
		std::vector<int> weight;
		int sum = 0;
		Prims.push_back(0);
		weight.push_back(0);
		for (int i = 1; i < numVertex; i++) {
			weight.push_back(matrix[0][i]);
		}
		for (int i = 1; i < numVertex; i++) {
			int j = 1, min = INT_MAX,t = 0;
			while (j < numVertex) {
				if (!weight[j] && weight[j] < min) {
					min = weight[j];
					t = j;
				}
				j++;
			}
			if (t) {
				Prims.push_back(t);
				sum += weight[t];
				weight[t] = 0;
				for (int i = 1; i < numVertex; i++) {
					if (weight[i] && weight[i] > matrix[t][i]) {
						weight[i] = matrix[t][i];
					}
				}
			}
		}
		return sum;
	}
};

